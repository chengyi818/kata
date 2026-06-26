#include "../extended/allocator.h"
#include "../extended/strategy_factory.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int tests_run = 0;
static int tests_passed = 0;

#define TEST(name) do { \
    printf("  [TEST %2d] %s... ", ++tests_run, name); \
} while(0)

#define PASS() do { \
    printf("PASS\n"); tests_passed++; \
} while(0)

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        printf("FAIL: %s (line %d)\n", msg, __LINE__); \
        return; \
    } \
} while(0)

/* ---- Test: factory creates all strategies ---- */
static void test_factory(void) {
    TEST("factory creates all strategy types");
    for (int t = 0; t < STRATEGY_COUNT; t++) {
        alloc_strategy_t *s = strategy_factory_create((strategy_type_t)t);
        CHECK(s != NULL, "factory returned NULL");
        CHECK(s->name != NULL, "strategy name is NULL");
        CHECK(s->allocate != NULL, "allocate is NULL");
        CHECK(s->deallocate != NULL, "deallocate is NULL");
        strategy_factory_destroy(s);
    }
    PASS();
}

/* ---- Test: each strategy can allocate and free ---- */
static void test_strategy_basic(strategy_type_t type) {
    char buf[128];
    snprintf(buf, sizeof(buf), "%s - basic alloc/free",
             strategy_type_name(type));

    TEST(buf);
    alloc_strategy_t *s = strategy_factory_create(type);
    allocator_t *alloc = allocator_create(s);
    CHECK(alloc != NULL, "allocator_create failed");

    size_t sizes[] = {100, 500, 1000, 2000, 5000};
    void *ptrs[5];
    for (int i = 0; i < 5; i++) {
        ptrs[i] = my_malloc(alloc, sizes[i]);
        CHECK(ptrs[i] != NULL, "allocation failed");
        CHECK(((uintptr_t)ptrs[i] & 7) == 0, "alignment fail");
    }

    for (int i = 0; i < 5; i++) {
        my_free(alloc, ptrs[i]);
    }

    allocator_destroy(alloc);
    strategy_factory_destroy(s);
    PASS();
}

/* ---- Test: all strategies work ---- */
static void test_all_strategies(void) {
    for (int t = 0; t < STRATEGY_COUNT; t++) {
        test_strategy_basic((strategy_type_t)t);
    }
}

/* ---- Test: strategies produce different layouts ---- */
static void test_different_layouts(void) {
    TEST("strategies produce different block layouts");
    int first_count = -1;
    int all_same = 1;

    for (int t = 0; t < STRATEGY_COUNT; t++) {
        alloc_strategy_t *s = strategy_factory_create((strategy_type_t)t);
        allocator_t *alloc = allocator_create(s);

        /* Allocate interleaved sizes */
        my_malloc(alloc, 300);
        my_malloc(alloc, 1000);
        my_malloc(alloc, 50);
        my_malloc(alloc, 2000);

        /* Count blocks */
        int block_count = 0;
        block_header_t *curr = alloc->free_list;
        while (curr) { block_count++; curr = curr->next; }

        if (first_count < 0) {
            first_count = block_count;
        } else if (block_count != first_count) {
            all_same = 0;
        }

        allocator_destroy(alloc);
        strategy_factory_destroy(s);
    }

    /*
     * At least Buddy System should produce different count
     * (due to power-of-2 rounding). FF/BF/WF may also differ
     * in how they split blocks.
     */
    CHECK(all_same == 0 || STRATEGY_COUNT <= 1,
          "all strategies produced identical layout (suspicious)");
    PASS();
}

/* ---- Test: buddy system power-of-2 ---- */
static void test_buddy_pow2(void) {
    TEST("buddy system - power-of-2 sizing");
    alloc_strategy_t *s = strategy_factory_create(STRATEGY_BUDDY_SYSTEM);
    allocator_t *alloc = allocator_create(s);

    /* Request 100 bytes -> buddy should allocate 128 */
    void *p = my_malloc(alloc, 100);
    CHECK(p != NULL, "allocation failed");

    block_header_t *header = (block_header_t*)p - 1;
    /* Total block size (usable + header) should be power of 2 */
    size_t total = header->size + HEADER_SIZE;
    CHECK((total & (total - 1)) == 0,
          "buddy block total size not a power of 2");

    /* Request 500 -> buddy should allocate 512 */
    void *p2 = my_malloc(alloc, 500);
    CHECK(p2 != NULL, "allocation 2 failed");
    block_header_t *h2 = (block_header_t*)p2 - 1;
    total = h2->size + HEADER_SIZE;
    CHECK((total & (total - 1)) == 0,
          "buddy block 2 total size not a power of 2");

    my_free(alloc, p);
    my_free(alloc, p2);
    allocator_destroy(alloc);
    strategy_factory_destroy(s);
    PASS();
}

/* ---- Test: free NULL ptr ---- */
static void test_free_null(void) {
    TEST("free(NULL) across all strategies");
    for (int t = 0; t < STRATEGY_COUNT; t++) {
        alloc_strategy_t *s = strategy_factory_create((strategy_type_t)t);
        allocator_t *alloc = allocator_create(s);
        my_free(alloc, NULL);  /* should not crash */
        allocator_destroy(alloc);
        strategy_factory_destroy(s);
    }
    PASS();
}

/* ---- Test: edge cases across all strategies ---- */
static void test_edge_cases_all(void) {
    TEST("edge cases - all strategies");
    for (int t = 0; t < STRATEGY_COUNT; t++) {
        alloc_strategy_t *s = strategy_factory_create((strategy_type_t)t);
        allocator_t *alloc = allocator_create(s);

        /* malloc(0) -> NULL */
        CHECK(my_malloc(alloc, 0) == NULL, "malloc(0) not NULL");

        /* Overallocate */
        CHECK(my_malloc(alloc, alloc->pool_size + 1) == NULL,
              "overallocate not NULL");

        allocator_destroy(alloc);
        strategy_factory_destroy(s);
    }
    PASS();
}

/* ---- Test: reuse after free ---- */
static void test_reuse_after_free(void) {
    TEST("memory reuse after free");
    alloc_strategy_t *s = strategy_factory_create(STRATEGY_FIRST_FIT);
    allocator_t *alloc = allocator_create(s);

    void *p1 = my_malloc(alloc, 4000);
    void *p2 = my_malloc(alloc, 4000);
    CHECK(p1 && p2, "allocations failed");

    my_free(alloc, p1);
    void *p3 = my_malloc(alloc, 3900);

    /* With First-Fit, p3 should end up where p1 was */
    CHECK(p3 != NULL, "reallocation failed");
    block_header_t *h1 = (block_header_t*)p1 - 1;
    block_header_t *h3 = (block_header_t*)p3 - 1;
    CHECK(h1 == h3, "did not reuse freed block with First-Fit");

    my_free(alloc, p2);
    my_free(alloc, p3);
    allocator_destroy(alloc);
    strategy_factory_destroy(s);
    PASS();
}

/* ---- Test: SOLID - no modification needed for new strategy ---- */
static void test_solid_ocp(void) {
    TEST("SOLID OCP - factory registry");
    /*
     * Verify that STRATEGY_COUNT and the factory creator/destroyer
     * arrays can be extended by adding new entries without modifying
     * existing strategy_*.c files.
     *
     * This is verified by design: adding a new strategy only requires:
     *   1. New strategy_xxx.c file
     *   2. New entry in STRATEGY_COUNT enum
     *   3. New entry in creator/destroyer array
     *
     * Existing strategy files remain untouched.
     */
    CHECK(STRATEGY_COUNT >= 4, "expected at least 4 strategies");
    CHECK(strategy_type_name(STRATEGY_FIRST_FIT) != NULL, "name missing");
    CHECK(strategy_type_name(STRATEGY_BEST_FIT) != NULL, "name missing");
    CHECK(strategy_type_name(STRATEGY_WORST_FIT) != NULL, "name missing");
    CHECK(strategy_type_name(STRATEGY_BUDDY_SYSTEM) != NULL, "name missing");

    /* Factory handles invalid types gracefully */
    CHECK(strategy_factory_create((strategy_type_t)999) == NULL,
          "factory should return NULL for invalid type");

    PASS();
}

/* ---- Test: statistics ---- */
static void test_stats(void) {
    TEST("statistics output");
    alloc_strategy_t *s = strategy_factory_create(STRATEGY_FIRST_FIT);
    allocator_t *alloc = allocator_create(s);

    void *p1 = my_malloc(alloc, 1024);
    void *p2 = my_malloc(alloc, 2048);

    /* Stats should not crash */
    print_stats(alloc);
    print_blocks(alloc);

    my_free(alloc, p1);
    my_free(alloc, p2);

    /* Verify full pool is free after freeing everything */
    block_header_t *initial = alloc->free_list;
    size_t total_free = 0;
    while (initial) {
        if (initial->is_free) total_free += initial->size;
        initial = initial->next;
    }
    CHECK(total_free == POOL_SIZE - HEADER_SIZE,
          "not all memory freed after cleanup");

    allocator_destroy(alloc);
    strategy_factory_destroy(s);
    PASS();
}

int main(void) {
    printf("===== Extended Unit Tests =====\n\n");

    test_factory();
    test_all_strategies();
    test_different_layouts();
    test_buddy_pow2();
    test_free_null();
    test_edge_cases_all();
    test_reuse_after_free();
    test_solid_ocp();
    test_stats();

    printf("\n===== Results: %d/%d passed =====\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
