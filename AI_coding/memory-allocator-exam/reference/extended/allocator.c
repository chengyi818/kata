#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
 * Core Allocator — delegates allocation/deallocation to strategy
 * ================================================================ */

allocator_t* allocator_create(alloc_strategy_t *strategy) {
    allocator_t *alloc = (allocator_t*)malloc(sizeof(allocator_t));
    if (!alloc) return NULL;

    alloc->pool_size = POOL_SIZE;
    alloc->pool = malloc(alloc->pool_size);
    if (!alloc->pool) {
        free(alloc);
        return NULL;
    }

    /* Initialize the entire pool as one free block */
    block_header_t *initial = (block_header_t*)alloc->pool;
    initial->size   = alloc->pool_size - HEADER_SIZE;
    initial->is_free = 1;
    initial->order  = 0;
    initial->next   = NULL;

    alloc->free_list = initial;
    alloc->strategy  = strategy;

    return alloc;
}

void allocator_destroy(allocator_t *alloc) {
    if (alloc) {
        free(alloc->pool);
        free(alloc);
    }
}

/* ---- Core API (thin wrappers that delegate to strategy) ---- */

void* my_malloc(allocator_t *alloc, size_t size) {
    if (!alloc || !alloc->strategy || size == 0) return NULL;
    return alloc->strategy->allocate(alloc->strategy, alloc, ALIGN(size));
}

void my_free(allocator_t *alloc, void *ptr) {
    if (!alloc || !alloc->strategy || !ptr) return;
    alloc->strategy->deallocate(alloc->strategy, alloc, ptr);
}

/* ================================================================
 * Helper functions for strategy implementations
 * ================================================================ */

/* Find first free block with size >= requested */
block_header_t* alloc_find_first(allocator_t *alloc, size_t size) {
    block_header_t *curr = alloc->free_list;
    while (curr) {
        if (curr->is_free && curr->size >= size) return curr;
        curr = curr->next;
    }
    return NULL;
}

/* Find smallest free block with size >= requested (best-fit) */
block_header_t* alloc_find_best(allocator_t *alloc, size_t size) {
    block_header_t *best = NULL;
    block_header_t *curr = alloc->free_list;
    while (curr) {
        if (curr->is_free && curr->size >= size) {
            if (!best || curr->size < best->size) best = curr;
        }
        curr = curr->next;
    }
    return best;
}

/* Find largest free block (worst-fit) */
block_header_t* alloc_find_worst(allocator_t *alloc, size_t size) {
    block_header_t *worst = NULL;
    block_header_t *curr = alloc->free_list;
    while (curr) {
        if (curr->is_free && curr->size >= size) {
            if (!worst || curr->size > worst->size) worst = curr;
        }
        curr = curr->next;
    }
    return worst;
}

/* Split a free block: keep `usable_size` bytes, put remainder back */
int alloc_split_block(allocator_t *alloc, block_header_t *block,
                      size_t usable_size) {
    (void)alloc;
    if (block->size < usable_size + MIN_BLOCK) return 0;

    block_header_t *new_block =
        (block_header_t*)((char*)(block + 1) + usable_size);
    new_block->size   = block->size - usable_size - HEADER_SIZE;
    new_block->is_free = 1;
    new_block->order  = 0;
    new_block->next   = block->next;

    block->size = usable_size;
    block->next = new_block;
    return 1;
}

/* Merge adjacent free blocks in the free list */
void alloc_coalesce(allocator_t *alloc) {
    block_header_t *curr = alloc->free_list;
    while (curr && curr->next) {
        if (curr->is_free && curr->next->is_free) {
            curr->size += HEADER_SIZE + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

/* Remove a free block from the free list */
void alloc_remove_free(allocator_t *alloc, block_header_t *target) {
    block_header_t *curr = alloc->free_list;
    block_header_t *prev = NULL;

    while (curr) {
        if (curr == target) {
            if (prev) {
                prev->next = curr->next;
            } else {
                alloc->free_list = curr->next;
            }
            curr->next = NULL;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

/* ================================================================
 * Statistics
 * ================================================================ */

void print_stats(allocator_t *alloc) {
    if (!alloc) return;

    size_t total_free = 0, total_allocated = 0;
    size_t free_blocks = 0, allocated_blocks = 0;
    size_t largest_free = 0, smallest_free = (size_t)-1;

    block_header_t *curr = alloc->free_list;
    while (curr) {
        if (curr->is_free) {
            total_free += curr->size;
            free_blocks++;
            if (curr->size > largest_free) largest_free = curr->size;
            if (curr->size < smallest_free) smallest_free = curr->size;
        } else {
            total_allocated += curr->size;
            allocated_blocks++;
        }
        curr = curr->next;
    }

    printf("========== Memory Pool Stats ==========\n");
    printf("  Strategy:        %s\n",
           alloc->strategy ? alloc->strategy->name : "none");
    printf("  Pool size:       %10zu bytes (%.2f MB)\n",
           alloc->pool_size, alloc->pool_size / (1024.0 * 1024.0));
    printf("  Total free:      %10zu bytes (%.1f%%)\n",
           total_free, 100.0 * total_free / alloc->pool_size);
    printf("  Total allocated: %10zu bytes (%.1f%%)\n",
           total_allocated, 100.0 * total_allocated / alloc->pool_size);
    printf("  Free blocks:     %10zu\n", free_blocks);
    printf("  Allocated blocks:%10zu\n", allocated_blocks);
    printf("  Largest free:    %10zu bytes\n", largest_free);
    if (free_blocks > 0 && largest_free > 0) {
        printf("  Smallest free:   %10zu bytes\n", smallest_free);
        printf("  Fragmentation:   %10.2f (1=optimal)\n",
               (double)smallest_free / largest_free);
    }
    printf("========================================\n");
}

void print_blocks(allocator_t *alloc) {
    if (!alloc) return;

    printf("========== Block List ==========\n");
    block_header_t *curr = alloc->free_list;
    int i = 0;
    while (curr) {
        printf("  [%3d] addr=%-14p size=%-10zu order=%-3d %s\n",
               i++, (void*)curr, curr->size, curr->order,
               curr->is_free ? "FREE" : "ALLOCATED");
        curr = curr->next;
    }
    printf("=================================\n");
}
