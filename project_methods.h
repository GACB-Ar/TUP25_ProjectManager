#ifndef PROJECT_METHODS_H
#define PROJECT_METHODS_H

#include <stdbool.h>

/* ----- Project ----- */
struct Project {
    char *name;
    char *created_date;  /* "YYYY-MM-DD" */
    char *created_by;    /* usuario */
    int   status;        /* 0=pendiente,1=en progreso,2=completada */
    struct Task *tasks;
    struct Project *next;
};

struct Project * project_create(const char *project_name,
                                const char *created_date,
                                const char *created_by,
                                int status);
void project_insert_end(struct Project **project_list_head,
                        struct Project *new_project);
bool project_search(const struct Project *project_list_head,
                    const char *project_name);
struct Project * project_find(const struct Project *head,
                              const char *project_name);
bool project_delete(struct Project **project_list_head,
                    const char *project_name);
void project_add_task(struct Project *project,
                      const char *task_name,
                      const char *created_date,
                      const char *created_by,
                      int status);
bool project_remove_task(struct Project *project,
                         const char *task_name);
void project_show_all(const struct Project *project_list_head);
void project_free_all(struct Project *project_list_head);

#endif /* PROJECT_METHODS_H */
