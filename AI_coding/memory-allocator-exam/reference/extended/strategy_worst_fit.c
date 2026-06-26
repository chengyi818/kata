#include "allocator.h"
#include <stdlib.h>

/* ================================================================
 * Worst-Fit Strategy
 * Selects the largest free block.
 * Leaves larger fragments for potential future large requests.
 * ================================================================ */

static void* wf_allocate(alloc_strategy_t *self, allocator_t *alloc,
                         size_t size) {
    (void)self;

    block_header_t *block = alloc_find_worst(alloc, size);
    if (!block) return NULL;

    alloc_split_block(alloc, block, size);
    block->is_free = 0;
    return (void*)(block + 1);
}

static void wf_deallocate(alloc_strategy_t *self, allocator_t *alloc,
                          void *ptr) {
    (void)self;

    block_header_t *block = (block_header_t*)ptr - 1;
    block->is_free = 1;
    alloc_coalesce(alloc);
}

alloc_strategy_t* strategy_worst_fit_create(void) {
    alloc_strategy_t *s = (alloc_strategy_t*)malloc(sizeof(alloc_strategy_t));
    if (!s) return NULL;
    s->name       = "Worst-Fit";
    s->allocate   = wf_allocate;
    s->deallocate = wf_deallocate;
    return s;
}

void strategy_worst_fit_destroy(alloc_strategy_t *s) {
    free(s);
}
