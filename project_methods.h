#ifndef PROJECT_METHODS_H
#define PROJECT_METHODS_H

#include <stdbool.h>
#include "task_methods.h"

struct Project;

struct Project * project_create(const char *project_name);
void project_insert_end(struct Project **project_list_head, struct Project *new_project);
bool project_search(const struct Project *project_list_head, const char *project_name);
bool project_delete(struct Project **project_list_head, const char *project_name);
void project_add_task(struct Project *project, const char *task_name);
bool project_remove_task(struct Project *project, const char *task_name);
void project_show_all(const struct Project *project_list_head);
void project_free_all(struct Project *project_list_head);
struct Project * project_find(const struct Project *head, const char *project_name);

#endif // PROJECT_METHODS_H