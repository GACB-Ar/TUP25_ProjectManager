#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct Task {
    char *name;
    struct Task *next;
};

struct Task * task_create(const char *task_name) {
    struct Task *new_task = malloc(sizeof *new_task);
    if (!new_task) return NULL;
    
    new_task->name = strdup(task_name);
    if (!new_task->name) {
        free(new_task); // Free the allocated task if strdup fails
        return NULL;
    }
    
    new_task->next = NULL;
    return new_task;
}

void task_insert_end(struct Task **task_list_head, struct Task *new_task) {
    if (!new_task) return;
    if (*task_list_head == NULL) {
        *task_list_head = new_task;
    } else {
        struct Task *cursor = *task_list_head;
        while (cursor->next != NULL) {
            cursor = cursor->next;
        }
        cursor->next = new_task;
    }
}

bool task_search(const struct Task *task_list_head, const char *task_name) {
    const struct Task *cursor = task_list_head;
    while (cursor != NULL) {
        if (strcmp(cursor->name, task_name) == 0) {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

bool task_delete(struct Task **task_list_head, const char *task_name) {
    struct Task *cursor = *task_list_head;
    struct Task *previous = NULL;

    while (cursor != NULL && strcmp(cursor->name, task_name) != 0) {
        previous = cursor;
        cursor = cursor->next;
    }
    if (cursor == NULL) return false;
    if (previous == NULL) {
        *task_list_head = cursor->next;
    } else {
        previous->next = cursor->next;
    }
    free(cursor->name);
    free(cursor);
    return true;
}

void task_show_all(const struct Task *task_list_head) {
    const struct Task *cursor = task_list_head;
    while (cursor != NULL) {
        printf("    - %s\n", cursor->name);
        cursor = cursor->next;
    }
}

void task_free_all(struct Task *task_list_head) {
    struct Task *cursor = task_list_head;
    while (cursor != NULL) {
        struct Task *next_task = cursor->next;
        free(cursor->name);
        free(cursor);
        cursor = next_task;
    }
}