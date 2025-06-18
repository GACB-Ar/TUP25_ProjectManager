#ifndef TASK_METHODS_H
#define TASK_METHODS_H

#include <stdbool.h>

struct Task;

struct Task * task_create(const char *task_name);
void task_insert_end(struct Task **task_list_head, struct Task *new_task);
bool task_search(const struct Task *task_list_head, const char *task_name);
bool task_delete(struct Task **task_list_head, const char *task_name);
void task_show_all(const struct Task *task_list_head);
void task_free_all(struct Task *task_list_head);

#endif // TASK_METHODS_H