#ifndef __LIST_H__
#define __LIST_H__

struct item {
    void *data;
    struct item *next;
    struct item *prev;
};

struct list {
    void (*delete)(void *);
    struct item *head;
    struct item *tail;
    unsigned int size;
};

struct item *item_create(void *data);
void item_delete(struct list *list, struct item *item);
struct list *list_create(void (*delete)(void *));
void list_delete(struct list *list);
int list_empty(struct list *list);
int list_size(struct list *list);
int list_push_back(struct list *list, void *data);
int list_push_front(struct list *list, void *data);
int list_pop_front(struct list *list);
int list_pop_back(struct list *list);
void *list_head(struct list *list);
void *list_tail(struct list *list);

#endif  /* __LIST_H__ */
