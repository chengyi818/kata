#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

#define POOL_SIZE  (1024 * 1024)  /* 1MB */
#define ALIGNMENT  8

/* Align a size up to multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~((size_t)(ALIGNMENT - 1)))

/* Size of block header, aligned */
#define HEADER_SIZE  ALIGN(sizeof(block_header_t))
#define MIN_BLOCK    (HEADER_SIZE + ALIGNMENT)

/* ---- Memory Block ---- */
typedef struct block_header {
    size_t size;          /* usable bytes (excluding this header) */
    int    is_free;       /* 1 = free, 0 = allocated */
    int    order;         /* buddy order: log2(total size incl header) (0 if unused) */
    struct block_header *next;
} block_header_t;

/* ---- Forward declarations ---- */
typedef struct alloc_strategy alloc_strategy_t;
typedef struct allocator      allocator_t;

/* ---- Strategy Interface ---- */
struct alloc_strategy {
    const char *name;
    void* (*allocate)(alloc_strategy_t *self, allocator_t *alloc, size_t size);
    void  (*deallocate)(alloc_strategy_t *self, allocator_t *alloc, void *ptr);
};

/* ---- Allocator (Memory Pool Manager) ---- */
struct allocator {
    void              *pool;       /* start of raw memory pool */
    size_t             pool_size;  /* total pool size */
    block_header_t    *free_list;  /* linked list of all blocks */
    alloc_strategy_t  *strategy;   /* current allocation strategy */
};

/* ---- Allocator Lifecycle ---- */
allocator_t* allocator_create(alloc_strategy_t *strategy);
void         allocator_destroy(allocator_t *alloc);

/* ---- Core API (delegates to strategy) ---- */
void* my_malloc(allocator_t *alloc, size_t size);
void  my_free(allocator_t *alloc, void *ptr);

/* ---- Statistics ---- */
void print_stats(allocator_t *alloc);
void print_blocks(allocator_t *alloc);

/* ---- Helper functions for strategy implementations ---- */
block_header_t* alloc_find_first(allocator_t *alloc, size_t size);
block_header_t* alloc_find_best(allocator_t *alloc, size_t size);
block_header_t* alloc_find_worst(allocator_t *alloc, size_t size);
int  alloc_split_block(allocator_t *alloc, block_header_t *block, size_t usable_size);
void alloc_coalesce(allocator_t *alloc);
void alloc_remove_free(allocator_t *alloc, block_header_t *target);

#endif /* ALLOCATOR_H */
