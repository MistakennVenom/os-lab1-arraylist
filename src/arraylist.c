#include "arraylist.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 4

struct ArrayList {
    void **data;
    size_t size;
    size_t capacity;
};

static bool al_resize(ArrayList *list, size_t new_capacity) {
    void **new_data = realloc(list->data, sizeof(void *) * new_capacity);
    if (!new_data) {
        return false;
    }
    list->data = new_data;
    list->capacity = new_capacity;
    return true;
}

ArrayList *al_create(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = DEFAULT_CAPACITY;
    }
    ArrayList *list = malloc(sizeof(ArrayList));
    if (!list) {
        return NULL;
    }
    list->data = malloc(sizeof(void *) * initial_capacity);
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->size = 0;
    list->capacity = initial_capacity;
    return list;
}

void al_destroy(ArrayList *list) {
    if (!list) {
        return;
    }
    free(list->data);
    free(list);
}

bool al_add(ArrayList *list, void *item) {
    if (!list) {
        return false;
    }
    if (list->size == list->capacity) {
        if (!al_resize(list, list->capacity * 2)) {
            return false;
        }
    }
    list->data[list->size++] = item;
    return true;
}

size_t al_size(const ArrayList *list) {
    return list ? list->size : 0;
}

void *al_get(const ArrayList *list, size_t index) {
    if (!list || index >= list->size) {
        return NULL;
    }
    return list->data[index];
}
