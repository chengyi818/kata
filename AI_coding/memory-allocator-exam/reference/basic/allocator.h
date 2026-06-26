#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

#define POOL_SIZE (1024 * 1024)  /* 1MB */
#define ALIGNMENT 8

/* Memory block header - placed immediately before user data */
typedef struct block_header {
    size_t size;          /* usable bytes (excluding header) */
    int    is_free;       /* 1 = free, 0 = allocated */
    struct block_header *next;
} block_header_t;

typedef struct {
    void           *pool;       /* start of the memory pool */
    size_t          pool_size;  /* total pool size in bytes */
    block_header_t *free_list;  /* head of free/allocated block list */
} allocator_t;

/* Create and initialize the memory pool allocator */
allocator_t* allocator_create(void);

/* Destroy the allocator and free all resources */
void allocator_destroy(allocator_t *alloc);

/* Allocate a block of at least `size` bytes (8-byte aligned) */
void* my_malloc(allocator_t *alloc, size_t size);

/* Free a previously allocated block */
void my_free(allocator_t *alloc, void *ptr);

/* Print memory pool statistics (fragmentation, etc.) */
void print_stats(allocator_t *alloc);

/* Print detailed block list */
void print_blocks(allocator_t *alloc);

#endif /* ALLOCATOR_H */
