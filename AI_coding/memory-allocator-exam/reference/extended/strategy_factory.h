#ifndef STRATEGY_FACTORY_H
#define STRATEGY_FACTORY_H

#include "allocator.h"

/* Strategy type identifiers */
typedef enum {
    STRATEGY_FIRST_FIT,
    STRATEGY_BEST_FIT,
    STRATEGY_WORST_FIT,
    STRATEGY_BUDDY_SYSTEM,
    STRATEGY_COUNT
} strategy_type_t;

/* Create a strategy instance by type. Returns heap-allocated strategy. */
alloc_strategy_t* strategy_factory_create(strategy_type_t type);

/* Destroy a strategy created by the factory. */
void strategy_factory_destroy(alloc_strategy_t *strategy);

/* Get human-readable name for a strategy type */
const char* strategy_type_name(strategy_type_t type);

#endif /* STRATEGY_FACTORY_H */
