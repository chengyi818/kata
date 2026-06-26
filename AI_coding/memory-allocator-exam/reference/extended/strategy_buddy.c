#include "allocator.h"
#include <stdlib.h>
#include <stdint.h>

/* ================================================================
 * Simplified Buddy System Strategy
 *
 * Key behaviors:
 *   1. Allocation sizes rounded UP to next power of 2
 *   2. Blocks split recursively by halving until target size reached
 *   3. Deallocation uses adjacent-coalescing (merging contiguous
 *      free blocks, which are guaranteed to be buddies when split
 *      correctly by this strategy)
 *
 * Simplifications vs. full Buddy System:
 *   - Uses a single linked list instead of per-order free lists
 *   - Buddy coalescing is implicit via adjacent coalescing, since
 *     halving places buddies as adjacent blocks in memory
 *   - No separate bitmap or free-area arrays
 * ================================================================ */

/* Round up to next power of 2 */
static size_t next_pow2(size_t v) {
    if (v == 0) return 0;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
#if SIZE_MAX > 0xFFFFFFFFULL
    v |= v >> 32;
#endif
    return v + 1;
}

/* Integer log2 of a power-of-2 value */
static int ilog2(size_t v) {
    int r = 0;
    while (v >>= 1) r++;
    return r;
}

static void* buddy_allocate(alloc_strategy_t *self, allocator_t *alloc,
                            size_t size) {
    (void)self;

    /* Round up requested size to next power of 2 */
    size_t buddy_size = next_pow2(size);
    if (buddy_size < size) return NULL; /* overflow */

    /* Find first free block large enough */
    block_header_t *block = alloc_find_first(alloc, buddy_size);
    if (!block) return NULL;

    /*
     * Buddy split: operate on total_size (usable + HEADER),
     * which is always a power of 2 in the buddy system.
     * Halving total_size guarantees both halves are properly
     * aligned (total_size is a power of 2 >= HEADER_SIZE,
     * so half_total is also a power of 2 and aligned).
     */
    size_t total = block->size + HEADER_SIZE;
    while (total / 2 >= buddy_size + HEADER_SIZE) {
        size_t half_total  = total / 2;
        size_t half_usable = half_total - HEADER_SIZE;

        if (half_usable < ALIGNMENT) break;

        /* Buddy block starts at block + half_total */
        block_header_t *buddy_blk =
            (block_header_t*)((char*)block + half_total);
        buddy_blk->size    = half_usable;
        buddy_blk->is_free = 1;
        buddy_blk->order   = ilog2(half_total);
        buddy_blk->next    = block->next;

        block->size  = half_usable;
        block->order = buddy_blk->order;
        block->next  = buddy_blk;
        total = half_total;
    }

    block->order  = ilog2(total);
    block->is_free = 0;
    return (void*)(block + 1);
}

static void buddy_deallocate(alloc_strategy_t *self, allocator_t *alloc,
                             void *ptr) {
    (void)self;

    block_header_t *block = (block_header_t*)ptr - 1;
    block->is_free = 1;

    /*
     * Adjacent coalescing merges contiguous free blocks.
     * Since buddy-split creates adjacent blocks in memory order,
     * this naturally merges buddies when both are free.
     *
     * Note: this is a simplification. A full buddy system would
     * use per-order free lists and XOR-based buddy address
     * calculation for O(log n) coalescing.
     */
    alloc_coalesce(alloc);

    /* Recalculate order for all free blocks */
    block_header_t *curr = alloc->free_list;
    while (curr) {
        if (curr->is_free) {
            curr->order = ilog2(curr->size + HEADER_SIZE);
        }
        curr = curr->next;
    }
}

alloc_strategy_t* strategy_buddy_create(void) {
    alloc_strategy_t *s = (alloc_strategy_t*)malloc(sizeof(alloc_strategy_t));
    if (!s) return NULL;
    s->name       = "Buddy System";
    s->allocate   = buddy_allocate;
    s->deallocate = buddy_deallocate;
    return s;
}

void strategy_buddy_destroy(alloc_strategy_t *s) {
    free(s);
}
