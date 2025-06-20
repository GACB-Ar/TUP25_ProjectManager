#include "project_methods.h"
#include "task_methods.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char * str_dup(const char *s) {
    char *d = malloc(strlen(s)+1);
    if (d) strcpy(d, s);
    return d;
}

struct Project * project_create(const char *project_name,
                                const char *created_date,
                                const char *created_by,
                                int status)
{
    struct Project *p = malloc(sizeof *p);
    if (!p) return NULL;
    p->name         = str_dup(project_name);
    p->created_date = str_dup(created_date);
    p->created_by   = str_dup(created_by);
    p->status       = status;
    p->tasks        = NULL;
    p->next         = NULL;
    if (!p->name || !p->created_date || !p->created_by) {
        free(p->name);
        free(p->created_date);
        free(p->created_by);
        free(p);
        return NULL;
    }
    return p;
}

void project_insert_end(struct Project **head, struct Project *new_project) {
    if (!new_project) return;
    if (*head==NULL) *head = new_project;
    else {
        struct Project *c = *head;
        while (c->next) c = c->next;
        c->next = new_project;
    }
}

bool project_search(const struct Project *head, const char *project_name) {
    while (head) {
        if (strcmp(head->name, project_name)==0) return true;
        head = head->next;
    }
    return false;
}

struct Project * project_find(const struct Project *head,
                              const char *project_name)
{
    while (head) {
        if (strcmp(head->name, project_name)==0)
            return (struct Project*)head;
        head = head->next;
    }
    return NULL;
}

bool project_delete(struct Project **head, const char *project_name) {
    struct Project *cur = *head, *prev = NULL;
    while (cur && strcmp(cur->name, project_name)!=0) {
        prev = cur; cur = cur->next;
    }
    if (!cur) return false;
    if (!prev) *head = cur->next;
    else       prev->next = cur->next;
    task_free_all(cur->tasks);
    free(cur->name);
    free(cur->created_date);
    free(cur->created_by);
    free(cur);
    return true;
}

void project_add_task(struct Project *p,
                      const char *task_name,
                      const char *created_date,
                      const char *created_by,
                      int status)
{
    if (!p) return;
    struct Task *t = task_create(task_name, created_date, created_by, status);
    task_insert_end(&p->tasks, t);
}

bool project_remove_task(struct Project *p, const char *task_name) {
    if (!p) return false;
    return task_delete(&p->tasks, task_name);
}

void project_show_all(const struct Project *head) {
    while (head) {
        printf("Proyecto: %s | %s | %s | %d\n",
               head->name,
               head->created_date,
               head->created_by,
               head->status);
        task_show_all(head->tasks);
        head = head->next;
    }
}

void project_free_all(struct Project *head) {
    while (head) {
        struct Project *nx = head->next;
        task_free_all(head->tasks);
        free(head->name);
        free(head->created_date);
        free(head->created_by);
        free(head);
        head = nx;
    }
}