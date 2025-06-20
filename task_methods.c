#include "task_methods.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char * str_dup(const char *s) {
    char *d = malloc(strlen(s)+1);
    if (d) strcpy(d, s);
    return d;
}

struct Task * task_create(const char *task_name,
                          const char *created_date,
                          const char *created_by,
                          int status)
{
    struct Task *t = malloc(sizeof *t);
    if (!t) return NULL;
    t->name         = str_dup(task_name);
    t->created_date = str_dup(created_date);
    t->created_by   = str_dup(created_by);
    t->status       = status;
    t->next         = NULL;
    if (!t->name || !t->created_date || !t->created_by) {
        free(t->name);
        free(t->created_date);
        free(t->created_by);
        free(t);
        return NULL;
    }
    return t;
}

void task_insert_end(struct Task **head, struct Task *new_task) {
    if (!new_task) return;
    if (*head == NULL) {
        *head = new_task;
    } else {
        struct Task *c = *head;
        while (c->next) c = c->next;
        c->next = new_task;
    }
}

bool task_search(const struct Task *head, const char *task_name) {
    while (head) {
        if (strcmp(head->name, task_name)==0) return true;
        head = head->next;
    }
    return false;
}

bool task_delete(struct Task **head, const char *task_name) {
    struct Task *cur = *head, *prev = NULL;
    while (cur && strcmp(cur->name, task_name)!=0) {
        prev = cur; cur = cur->next;
    }
    if (!cur) return false;
    if (!prev) *head = cur->next;
    else       prev->next = cur->next;
    free(cur->name);
    free(cur->created_date);
    free(cur->created_by);
    free(cur);
    return true;
}

void task_show_all(const struct Task *head) {
    while (head) {
        printf("    - %s | %s | %s | %d\n",
               head->name,
               head->created_date,
               head->created_by,
               head->status);
        head = head->next;
    }
}

void task_free_all(struct Task *head) {
    while (head) {
        struct Task *nx = head->next;
        free(head->name);
        free(head->created_date);
        free(head->created_by);
        free(head);
        head = nx;
    }
}

static struct Task *merge_sorted(struct Task *a, struct Task *b) {
    struct Task dummy;
    struct Task *tail = &dummy;
    dummy.next = NULL;
    while (a && b) {
        /* Comparamos cadenas “YYYY-MM-DD” lexicográficamente */
        if (strcmp(a->created_date, b->created_date) <= 0) {
            tail->next = a; a = a->next;
        } else {
            tail->next = b; b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a ? a : b);
    return dummy.next;
}

static void split_list(struct Task *source,
                       struct Task **frontRef,
                       struct Task **backRef)
{
    struct Task *fast, *slow;
    slow = source;
    fast = source->next;
    /* Avanzar fast dos pasos y slow uno */
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    /* slow está en punto medio */
    *frontRef = source;
    *backRef  = slow->next;
    slow->next = NULL;
}

void task_sort_by_date(struct Task **headRef) {
    struct Task *head = *headRef;
    if (!head || !head->next) return; /* 0 o 1 elemento */
    struct Task *a, *b;
    split_list(head, &a, &b);
    task_sort_by_date(&a);
    task_sort_by_date(&b);
    *headRef = merge_sorted(a, b);
}

struct Task *task_find(const struct Task *head, const char *name) {
    while (head) {
        if (strcmp(head->name, name) == 0)
            return (struct Task *)head; /* casteo seguro */
        head = head->next;
    }
    return NULL;
}
