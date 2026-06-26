#include "../basic/allocator.h"
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

static void test_create_destroy(void) {
    TEST("create and destroy allocator");
    allocator_t *alloc = allocator_create();
    CHECK(alloc != NULL, "allocator_create returned NULL");
    CHECK(alloc->pool != NULL, "pool is NULL");
    CHECK(alloc->free_list != NULL, "free_list is NULL");
    CHECK(alloc->free_list->is_free == 1, "initial block not free");
    allocator_destroy(alloc);
    PASS();
}

static void test_single_alloc(void) {
    TEST("single allocation");
    allocator_t *alloc = allocator_create();
    CHECK(alloc != NULL, "allocator_create failed");

    void *p = my_malloc(alloc, 1024);
    CHECK(p != NULL, "allocation returned NULL");
    CHECK(((uintptr_t)p & 7) == 0, "pointer not 8-byte aligned");

    block_header_t *header = (block_header_t*)p - 1;
    CHECK(header->is_free == 0, "block not marked allocated");
    CHECK(header->size >= 1024, "allocated size too small");

    allocator_destroy(alloc);
    PASS();
}

static void test_multiple_allocs(void) {
    TEST("multiple allocations");
    allocator_t *alloc = allocator_create();

    void *ptrs[5];
    size_t sizes[] = {128, 256, 512, 1024, 2048};

    for (int i = 0; i < 5; i++) {
        ptrs[i] = my_malloc(alloc, sizes[i]);
        CHECK(ptrs[i] != NULL, "allocation returned NULL");
        CHECK(((uintptr_t)ptrs[i] & 7) == 0, "pointer not aligned");
    }

    /* Verify each block is distinct */
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            CHECK(ptrs[i] != ptrs[j], "duplicate pointer returned");
        }
    }

    allocator_destroy(alloc);
    PASS();
}

static void test_free_and_reuse(void) {
    TEST("free and reuse memory");
    allocator_t *alloc = allocator_create();

    void *p1 = my_malloc(alloc, 1024);
    void *p2 = my_malloc(alloc, 2048);
    void *p3 = my_malloc(alloc, 512);

    CHECK(p1 && p2 && p3, "allocation failed");

    /* Free p2 and reallocate -- should get same or similar address */
    my_free(alloc, p2);
    void *p4 = my_malloc(alloc, 2000);
    CHECK(p4 != NULL, "reallocation failed");
    /* p4 should be near p2 (reuses freed space via first-fit) */

    /* Free p1 and p3, then allocate large block */
    my_free(alloc, p1);
    my_free(alloc, p3);
    void *p5 = my_malloc(alloc, 3000);
    CHECK(p5 != NULL, "large reallocation failed");

    my_free(alloc, p4);
    my_free(alloc, p5);
    allocator_destroy(alloc);
    PASS();
}

static void test_coalesce(void) {
    TEST("coalescing adjacent free blocks");
    allocator_t *alloc = allocator_create();

    void *p1 = my_malloc(alloc, 1024);
    void *p2 = my_malloc(alloc, 2048);
    void *p3 = my_malloc(alloc, 512);

    CHECK(p1 && p2 && p3, "allocation failed");

    /* Free all three in forward order */
    my_free(alloc, p1);
    my_free(alloc, p2);
    my_free(alloc, p3);

    /* After coalescing, all three consecutive blocks should merge */
    size_t free_blocks = 0;
    block_header_t *curr = alloc->free_list;
    while (curr) {
        if (curr->is_free) free_blocks++;
        curr = curr->next;
    }
    CHECK(free_blocks <= 2, "blocks did not coalesce properly");

    allocator_destroy(alloc);
    PASS();
}

static void test_edge_cases(void) {
    TEST("edge cases");
    allocator_t *alloc = allocator_create();

    /* malloc(0) */
    void *p0 = my_malloc(alloc, 0);
    CHECK(p0 == NULL, "malloc(0) should return NULL");

    /* free(NULL) should not crash */
    my_free(alloc, NULL);
    CHECK(1, "free(NULL) didn't crash");

    /* Overallocation */
    void *big = my_malloc(alloc, alloc->pool_size + 1);
    CHECK(big == NULL, "overallocation should return NULL");

    /* Exhaust memory to ensure proper NULL returns */
    int count = 0;
    void *ptrs[1000];
    while (count < 1000) {
        ptrs[count] = my_malloc(alloc, 1024);
        if (!ptrs[count]) break;
        count++;
    }
    CHECK(count > 0, "could not make any allocations");
    CHECK(count < 1100, "unexpected: allocated 1100+ blocks in 1MB pool");

    /* Free all */
    for (int i = 0; i < count; i++) {
        my_free(alloc, ptrs[i]);
    }

    allocator_destroy(alloc);
    PASS();
}

static void test_alignment(void) {
    TEST("8-byte alignment");
    allocator_t *alloc = allocator_create();

    for (size_t s = 1; s <= 128; s++) {
        void *p = my_malloc(alloc, s);
        CHECK(p != NULL, "allocation failed");
        CHECK(((uintptr_t)p & 7) == 0, "misaligned pointer");
        my_free(alloc, p);
    }

    allocator_destroy(alloc);
    PASS();
}

int main(void) {
    printf("===== Basic Unit Tests =====\n\n");

    test_create_destroy();
    test_single_alloc();
    test_multiple_allocs();
    test_free_and_reuse();
    test_coalesce();
    test_edge_cases();
    test_alignment();

    printf("\n===== Results: %d/%d passed =====\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
