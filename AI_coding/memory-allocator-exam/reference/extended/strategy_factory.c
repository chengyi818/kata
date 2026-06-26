#include "strategy_factory.h"
#include <stdlib.h>

/* ---- Forward declarations of strategy create/destroy functions ---- */

/* First-Fit */
alloc_strategy_t* strategy_first_fit_create(void);
void strategy_first_fit_destroy(alloc_strategy_t *s);

/* Best-Fit */
alloc_strategy_t* strategy_best_fit_create(void);
void strategy_best_fit_destroy(alloc_strategy_t *s);

/* Worst-Fit */
alloc_strategy_t* strategy_worst_fit_create(void);
void strategy_worst_fit_destroy(alloc_strategy_t *s);

/* Buddy System */
alloc_strategy_t* strategy_buddy_create(void);
void strategy_buddy_destroy(alloc_strategy_t *s);

/* ---- Vtable of creators/destroyers ---- */

typedef alloc_strategy_t* (*create_fn)(void);
typedef void (*destroy_fn)(alloc_strategy_t*);

static create_fn creators[STRATEGY_COUNT] = {
    strategy_first_fit_create,
    strategy_best_fit_create,
    strategy_worst_fit_create,
    strategy_buddy_create
};

static destroy_fn destroyers[STRATEGY_COUNT] = {
    strategy_first_fit_destroy,
    strategy_best_fit_destroy,
    strategy_worst_fit_destroy,
    strategy_buddy_destroy
};

static const char *names[STRATEGY_COUNT] = {
    "First-Fit",
    "Best-Fit",
    "Worst-Fit",
    "Buddy System"
};

alloc_strategy_t* strategy_factory_create(strategy_type_t type) {
    if (type >= STRATEGY_COUNT) return NULL;
    return creators[type]();
}

void strategy_factory_destroy(alloc_strategy_t *strategy) {
    if (!strategy) return;

    /* Find and call the appropriate destroyer */
    for (int i = 0; i < STRATEGY_COUNT; i++) {
        if (creators[i] && strategy->name && names[i] &&
            strategy->name == names[i]) {
            destroyers[i](strategy);
            return;
        }
    }

    /* Fallback: free the strategy struct itself */
    free(strategy);
}

const char* strategy_type_name(strategy_type_t type) {
    if (type >= STRATEGY_COUNT) return "Unknown";
    return names[type];
}
