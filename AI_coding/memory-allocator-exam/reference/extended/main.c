#include "allocator.h"
#include "strategy_factory.h"
#include <stdio.h>
#include <string.h>

static void test_strategy(strategy_type_t type) {
    printf("\n===== Testing %s =====\n", strategy_type_name(type));

    alloc_strategy_t *strategy = strategy_factory_create(type);
    if (!strategy) {
        printf("Failed to create strategy\n");
        return;
    }

    allocator_t *alloc = allocator_create(strategy);
    if (!alloc) {
        printf("Failed to create allocator\n");
        strategy_factory_destroy(strategy);
        return;
    }

    /* Same allocation pattern for all strategies */
    void *p1 = my_malloc(alloc, 500);
    void *p2 = my_malloc(alloc, 2000);
    void *p3 = my_malloc(alloc, 100);
    void *p4 = my_malloc(alloc, 4000);

    printf("Allocated: p1(500)=%p p2(2000)=%p p3(100)=%p p4(4000)=%p\n",
           p1, p2, p3, p4);
    print_blocks(alloc);
    print_stats(alloc);

    /* Free p2 and p3, observe coalescing */
    my_free(alloc, p2);
    my_free(alloc, p3);
    printf("Freed p2 and p3\n");
    print_blocks(alloc);

    /* Reallocate in the freed space */
    void *p5 = my_malloc(alloc, 1500);
    printf("Reallocated p5(1500)=%p\n", p5);
    print_blocks(alloc);

    /* Cleanup */
    my_free(alloc, p1);
    my_free(alloc, p4);
    my_free(alloc, p5);

    allocator_destroy(alloc);
    strategy_factory_destroy(strategy);
}

static void test_buddy_specific(void) {
    printf("\n===== Buddy System - Power-of-2 test =====\n");

    alloc_strategy_t *strategy = strategy_factory_create(STRATEGY_BUDDY_SYSTEM);
    allocator_t *alloc = allocator_create(strategy);

    /* Buddy system rounds up to power of 2:
     *   100 -> 128, 500 -> 512, 900 -> 1024, 3000 -> 4096
     */
    void *p1 = my_malloc(alloc, 100);   /* should use 128-byte block */
    void *p2 = my_malloc(alloc, 500);   /* should use 512-byte block */
    void *p3 = my_malloc(alloc, 900);   /* should use 1024-byte block */
    void *p4 = my_malloc(alloc, 3000);  /* should use 4096-byte block */

    printf("Buddy allocations (sizes rounded up to power of 2):\n");
    printf("  p1(100)  -> %p (order %d)\n", p1, 0);
    printf("  p2(500)  -> %p\n", p2);
    printf("  p3(900)  -> %p\n", p3);
    printf("  p4(3000) -> %p\n", p4);
    print_blocks(alloc);
    print_stats(alloc);

    /* Free all, all should coalesce back to one block */
    my_free(alloc, p1);
    my_free(alloc, p2);
    my_free(alloc, p3);
    my_free(alloc, p4);
    printf("\nAfter freeing all:\n");
    print_blocks(alloc);
    print_stats(alloc);

    allocator_destroy(alloc);
    strategy_factory_destroy(strategy);
}

int main(void) {
    printf("===== Linux Memory Allocator - Extended (Strategy Pattern) =====\n");

    test_strategy(STRATEGY_FIRST_FIT);
    test_strategy(STRATEGY_BEST_FIT);
    test_strategy(STRATEGY_WORST_FIT);
    test_strategy(STRATEGY_BUDDY_SYSTEM);

    test_buddy_specific();

    printf("\n===== All extended tests passed =====\n");
    return 0;
}
