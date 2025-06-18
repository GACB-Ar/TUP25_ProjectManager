#include "task_methods.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Project {
    char *name;
    struct Task *tasks; // Pointer to the list of tasks associated with the project
    struct Project *next; // Pointer to the next project in the list
};

struct Project * project_create(const char *project_name) {
    struct Project *new_project = malloc(sizeof *new_project);
    if (!new_project) return NULL;
    
    new_project->name = strdup(project_name);
    if (!new_project->name) {
        free(new_project); // Free the allocated project if strdup fails
        return NULL;
    }
    
    new_project->tasks = NULL; // Initialize the task list to NULL
    new_project->next = NULL; // Initialize the next project pointer to NULL
    return new_project;
}

void project_insert_end(struct Project **project_list_head, struct Project *new_project) {
    if (!new_project) return;
    if (*project_list_head == NULL) {
        *project_list_head = new_project;
    } else {
        struct Project *cursor = *project_list_head;
        while (cursor->next != NULL) {
            cursor = cursor->next;
        }
        cursor->next = new_project;
    }
}

bool project_search(const struct Project *project_list_head, const char *project_name) {
    const struct Project *cursor = project_list_head;
    while (cursor != NULL) {
        if (strcmp(cursor->name, project_name) == 0) {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

struct Project * project_find(const struct Project *head, const char *project_name) {
    while (head) {
        if (strcmp(head->name, project_name) == 0) {
            return (struct Project *)head;
        }
        head = head->next;
    }
    return NULL;
}

bool project_delete(struct Project **project_list_head, const char *project_name) {
    struct Project *cursor = *project_list_head;
    struct Project *previous = NULL;

    while (cursor != NULL && strcmp(cursor->name, project_name) != 0) {
        previous = cursor;
        cursor = cursor->next;
    }
    if (cursor == NULL) return false; // Project not found
    if (previous == NULL) {
        *project_list_head = cursor->next; // Deleting the head of the list
    } else {
        previous->next = cursor->next; // Bypass the cursor
    }

    task_free_all(cursor->tasks); // Free all tasks associated with the project
    free(cursor->name); // Free the project name
    free(cursor); // Free the project itself
    return true;
}

void project_add_task(struct Project *project, const char *task_name) {
    if (!project) return; // Ensure the project exists
    struct Task *new_task = task_create(task_name); // Create a new task
    task_insert_end(&project->tasks, new_task); // Insert the new task at the end of the task list
}

bool project_remove_task(struct Project *project, const char *task_name) {
    if (!project) return false; // Ensure the project exists
    return task_delete(&project->tasks, task_name); // Delete the task from the project's task list
}

void project_show_all(const struct Project *project_list_head) {
    const struct Project *cursor = project_list_head;
    while (cursor != NULL) {
        printf("Proyecto: %s\n", cursor->name); // Print the project name
        task_show_all(cursor->tasks); // Show all tasks associated with the project
        cursor = cursor->next; // Move to the next project
    }
}

void project_free_all(struct Project *project_list_head) {
    struct Project *cursor = project_list_head;
    while (cursor != NULL) {
        struct Project *next_project = cursor->next; // Store the next project
        task_free_all(cursor->tasks); // Free all tasks associated with the project
        free(cursor->name); // Free the project name
        free(cursor); // Free the project itself
        cursor = next_project; // Move to the next project
    }
}
