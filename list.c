#include "stdlib.h"
#include "list.h"

struct item *item_create(void *data)
{
    struct item *item = malloc(sizeof(struct item));
    item->data = data;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

void item_delete(struct list *list, struct item *item)
{
    if (!item) return;
    if (item->data) list->delete(item->data);
    free(item);
}

struct list *list_create(void (*delete)(void *))
{
    struct list *list = malloc(sizeof(struct list));
    list->delete = delete;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void list_delete(struct list *list)
{
    struct item *current, *next;
    if (!list) return;
    /* Iterate through list and delete all items. */
    current = list->head;
    while (current) {
        next = current->next;
        item_delete(list, current);
        current = next;
    }
    free(list);
}

int list_empty(struct list *list)
    /* Returns a value greater than 0 if the list is non-empty, 0 if the list
     * is empty and -1 if an error occurs. */
{
    if (!list) return -1;
    return !list->size;
}

int list_size(struct list *list)
    /* Returns the number of elements in a list or -1 on error. */
{
    if (!list) return -1;
    return list->size;
}

int list_push_back(struct list *list, void *data)
    /* Pushes an item onto the back of a list and returns the new size of the
     * list or -1 on error. */
{
    struct item *item;
    if (!list) return -1;
    item = item_create(data);
    if (list_empty(list)) {
        item->next = NULL;
        item->prev = NULL;
        list->head = item;
        list->tail = item;
    }
    else {
        item->prev = list->tail;
        item->next = NULL;
        list->tail->next = item;
        list->tail = item;
    }
    return ++list->size;
}

int list_push_front(struct list *list, void *data)
{
    struct item *item;
    if (!list) return -1;
    item = item_create(data);
    if (item) {
        if (list_empty(list)) {
            item->next = NULL;
            item->prev = NULL;
            list->head = item;
            list->tail = item;
        }
        else {
            item->prev = NULL;
            item->next = list->head;
            list->head->prev = item;
            list->head = item;
        }
        return ++list->size;
    }
    return -1;
}

int list_pop_front(struct list *list)
    /* Removes and deletes an item from the front of a list and returns the new
     * size of the list or -1 on error. */
{
    struct item *item;
    if (!list) return -1;
    item = list->head;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        list->head->next->prev = NULL;
        list->head = list->head->next;
    }
    if (item) {
        item_delete(list, item);
        list->size--;
    }
    return list->size;
}

int list_pop_back(struct list *list)
{
    struct item *item;
    if (!list) return -1;
    item = list->tail;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        list->tail->prev->next = NULL;
        list->tail = list->tail->prev;
    }
    if (item) {
        item_delete(list, item);
        list->size--;
    }
    return list->size;
}

void *list_head(struct list *list)
{
    if (!list || !list->head) return NULL;
    return list->head->data;
}

void *list_tail(struct list *list)
{
    if (!list || !list->tail) return NULL;
    return list->tail->data;
}
