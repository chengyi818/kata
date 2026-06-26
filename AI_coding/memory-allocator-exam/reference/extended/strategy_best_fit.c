#include "allocator.h"
#include <stdlib.h>

/* ================================================================
 * Best-Fit Strategy
 * Selects the smallest free block that satisfies the request.
 * Minimizes wasted space (internal fragmentation).
 * ================================================================ */

static void* bf_allocate(alloc_strategy_t *self, allocator_t *alloc,
                         size_t size) {
    (void)self;

    block_header_t *block = alloc_find_best(alloc, size);
    if (!block) return NULL;

    alloc_split_block(alloc, block, size);
    block->is_free = 0;
    return (void*)(block + 1);
}

static void bf_deallocate(alloc_strategy_t *self, allocator_t *alloc,
                          void *ptr) {
    (void)self;

    block_header_t *block = (block_header_t*)ptr - 1;
    block->is_free = 1;
    alloc_coalesce(alloc);
}

alloc_strategy_t* strategy_best_fit_create(void) {
    alloc_strategy_t *s = (alloc_strategy_t*)malloc(sizeof(alloc_strategy_t));
    if (!s) return NULL;
    s->name       = "Best-Fit";
    s->allocate   = bf_allocate;
    s->deallocate = bf_deallocate;
    return s;
}

void strategy_best_fit_destroy(alloc_strategy_t *s) {
    free(s);
}
