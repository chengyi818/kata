#include "allocator.h"
#include <stdlib.h>

/* ================================================================
 * First-Fit Strategy
 * Selects the first free block large enough to satisfy the request.
 * ================================================================ */

static void* ff_allocate(alloc_strategy_t *self, allocator_t *alloc,
                         size_t size) {
    (void)self;

    block_header_t *block = alloc_find_first(alloc, size);
    if (!block) return NULL;

    alloc_split_block(alloc, block, size);
    block->is_free = 0;
    return (void*)(block + 1);
}

static void ff_deallocate(alloc_strategy_t *self, allocator_t *alloc,
                          void *ptr) {
    (void)self;

    block_header_t *block = (block_header_t*)ptr - 1;
    block->is_free = 1;
    alloc_coalesce(alloc);
}

alloc_strategy_t* strategy_first_fit_create(void) {
    alloc_strategy_t *s = (alloc_strategy_t*)malloc(sizeof(alloc_strategy_t));
    if (!s) return NULL;
    s->name       = "First-Fit";
    s->allocate   = ff_allocate;
    s->deallocate = ff_deallocate;
    return s;
}

void strategy_first_fit_destroy(alloc_strategy_t *s) {
    free(s);
}
