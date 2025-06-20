#ifndef TASK_METHODS_H
#define TASK_METHODS_H

#include <stdbool.h>

struct Task {
    char *name;
    char *created_date;
    char *created_by;
    int   status;
    struct Task *next;
};

struct Task * task_create(const char *task_name,
                          const char *created_date,
                          const char *created_by,
                          int status);
void task_insert_end(struct Task **task_list_head,
                     struct Task *new_task);
bool task_search(const struct Task *task_list_head,
                 const char *task_name);
bool task_delete(struct Task **task_list_head,
                 const char *task_name);
void task_show_all(const struct Task *task_list_head);
void task_free_all(struct Task *task_list_head);
void task_sort_by_date(struct Task **task_list_head);
struct Task *task_find(const struct Task *task_list_head,
                       const char *name);
                       
#endif /* TASK_METHODS_H */