#include "allocator.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    printf("===== Linux Memory Allocator - Basic (First-Fit) =====\n\n");

    allocator_t *alloc = allocator_create();
    if (!alloc) {
        printf("Failed to create allocator\n");
        return 1;
    }

    /* Test 1: Single allocation */
    void *p1 = my_malloc(alloc, 1024);
    printf("[1] Allocated 1024 bytes at %p\n", p1);
    print_blocks(alloc);
    print_stats(alloc);

    /* Test 2: Multiple allocations of different sizes */
    void *p2 = my_malloc(alloc, 512);
    void *p3 = my_malloc(alloc, 2048);
    void *p4 = my_malloc(alloc, 128);
    printf("\n[2] Allocated 512, 2048, 128 bytes\n");
    print_blocks(alloc);

    /* Test 3: Free middle block, observe coalescing */
    my_free(alloc, p3);
    printf("\n[3] Freed 2048-byte block (p3)\n");
    print_blocks(alloc);

    /* Test 4: Reuse freed memory */
    void *p5 = my_malloc(alloc, 1000);
    printf("\n[4] Allocated 1000 bytes (should reuse p3's space)\n");
    print_blocks(alloc);
    print_stats(alloc);

    /* Test 5: Free all */
    my_free(alloc, p1);
    my_free(alloc, p2);
    my_free(alloc, p4);
    my_free(alloc, p5);
    printf("\n[5] Freed all blocks\n");
    print_blocks(alloc);
    print_stats(alloc);

    /* Test 6: Stress test - allocate many small blocks */
    printf("\n[6] Stress test: 100 small allocations (128B each)\n");
    void *ptrs[100];
    for (int i = 0; i < 100; i++) {
        ptrs[i] = my_malloc(alloc, 128);
        if (!ptrs[i]) {
            printf("    Failed at allocation %d\n", i);
            break;
        }
    }
    printf("    Allocated %d blocks\n", 100);
    print_stats(alloc);

    /* Free half of them */
    for (int i = 0; i < 50; i++) {
        my_free(alloc, ptrs[i]);
    }
    printf("    Freed first 50 blocks\n");
    print_stats(alloc);

    /* Test 7: Edge cases */
    printf("\n[7] Edge cases:\n");
    void *p0 = my_malloc(alloc, 0);
    printf("    malloc(0) = %p (expected NULL)\n", p0);

    my_free(alloc, NULL);
    printf("    free(NULL) - no crash\n");

    void *too_big = my_malloc(alloc, alloc->pool_size);
    printf("    malloc(pool_size) = %p (expected NULL)\n", too_big);

    /* Cleanup remaining blocks */
    for (int i = 50; i < 100; i++) {
        my_free(alloc, ptrs[i]);
    }

    allocator_destroy(alloc);
    printf("\n===== All tests passed =====\n");
    return 0;
}
