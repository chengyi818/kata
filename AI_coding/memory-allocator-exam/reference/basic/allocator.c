#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~((size_t)(ALIGNMENT - 1)))
#define HEADER_SIZE ALIGN(sizeof(block_header_t))
#define MIN_BLOCK_SIZE (HEADER_SIZE + ALIGNMENT)

/* ---- static helpers ---- */

/* Find first free block with size >= requested */
static block_header_t* find_first_fit(allocator_t *alloc, size_t size) {
    block_header_t *curr = alloc->free_list;
    while (curr != NULL) {
        if (curr->is_free && curr->size >= size) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

/* Split a block: keep `size` bytes usable, return remainder to free list */
static void split_block(allocator_t *alloc, block_header_t *block, size_t size) {
    (void)alloc;
    if (block->size >= size + MIN_BLOCK_SIZE) {
        block_header_t *new_block = (block_header_t*)((char*)(block + 1) + size);
        new_block->size = block->size - size - HEADER_SIZE;
        new_block->is_free = 1;
        new_block->next = block->next;

        block->size = size;
        block->next = new_block;
    }
}

/* Merge adjacent free blocks */
static void coalesce(allocator_t *alloc) {
    block_header_t *curr = alloc->free_list;
    while (curr != NULL && curr->next != NULL) {
        if (curr->is_free && curr->next->is_free) {
            curr->size += HEADER_SIZE + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

/* ---- public API ---- */

allocator_t* allocator_create(void) {
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
    initial->size = alloc->pool_size - HEADER_SIZE;
    initial->is_free = 1;
    initial->next = NULL;

    alloc->free_list = initial;
    return alloc;
}

void allocator_destroy(allocator_t *alloc) {
    if (alloc) {
        free(alloc->pool);
        free(alloc);
    }
}

void* my_malloc(allocator_t *alloc, size_t size) {
    if (!alloc || size == 0) return NULL;

    size = ALIGN(size);

    /* ---- First-Fit strategy (hardcoded) ---- */
    block_header_t *block = find_first_fit(alloc, size);
    if (!block) return NULL;

    split_block(alloc, block, size);
    block->is_free = 0;

    return (void*)(block + 1);
}

void my_free(allocator_t *alloc, void *ptr) {
    if (!alloc || !ptr) return;

    block_header_t *block = (block_header_t*)ptr - 1;
    block->is_free = 1;

    coalesce(alloc);
}

void print_stats(allocator_t *alloc) {
    if (!alloc) return;

    size_t total_free = 0;
    size_t total_allocated = 0;
    size_t free_blocks = 0;
    size_t allocated_blocks = 0;
    size_t largest_free = 0;
    size_t smallest_free = (size_t)-1;

    block_header_t *curr = alloc->free_list;
    while (curr != NULL) {
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
    printf("  Pool size:       %10zu bytes (%.2f MB)\n",
           alloc->pool_size, alloc->pool_size / (1024.0 * 1024.0));
    printf("  Total free:      %10zu bytes (%.1f%%)\n",
           total_free, 100.0 * total_free / alloc->pool_size);
    printf("  Total allocated: %10zu bytes (%.1f%%)\n",
           total_allocated, 100.0 * total_allocated / alloc->pool_size);
    printf("  Free blocks:     %10zu\n", free_blocks);
    printf("  Allocated blocks:%10zu\n", allocated_blocks);
    printf("  Largest free:    %10zu bytes\n", largest_free);

    if (free_blocks > 0) {
        printf("  Smallest free:   %10zu bytes\n", smallest_free);
        if (largest_free > 0) {
            printf("  Fragmentation:   %10.2f (smallest/largest, 1=optimal)\n",
                   (double)smallest_free / largest_free);
        }
    }
    printf("========================================\n");
}

void print_blocks(allocator_t *alloc) {
    if (!alloc) return;

    printf("========== Block List ==========\n");
    block_header_t *curr = alloc->free_list;
    int i = 0;
    while (curr != NULL) {
        printf("  [%3d] addr=%-14p size=%-10zu %s\n",
               i++, (void*)curr, curr->size,
               curr->is_free ? "FREE" : "ALLOCATED");
        curr = curr->next;
    }
    printf("=================================\n");
}
