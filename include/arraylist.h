#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct ArrayList ArrayList;

ArrayList *al_create(size_t initial_capacity);
void al_destroy(ArrayList *list);

bool al_add(ArrayList *list, void *item);
bool al_insert(ArrayList *list, size_t index, void *item);
size_t al_size(const ArrayList *list);
void *al_remove(ArrayList *list, size_t index);
bool al_set(ArrayList *list, size_t index, void *item);
void *al_get(const ArrayList *list, size_t index);

#endif /* ARRAYLIST_H */
