#include "project_methods.h"
#include <stdio.h>

int main(void) {
    struct Project *all_projects = NULL;

    struct Project *projectA = project_create("Proyecto A");
    if (!projectA) {
        fprintf(stderr, "Error creating project A\n");
        return 1; // Exit with an error code
    }
    project_insert_end(&all_projects, projectA);

    struct Project *projectB = project_create("Proyecto B");
    if (!projectB) {
        fprintf(stderr, "Error creating project B\n");
        return 1; // Exit with an error code
    }
    project_insert_end(&all_projects, projectB);

    project_add_task(projectA, "Analisis");
    project_add_task(projectA, "Diseño");

    project_add_task(projectB, "Requisitos");
    project_add_task(projectB, "Prototipo UI");

    project_show_all(all_projects);

    printf("\nExiste Proyecto B? %s\n", project_search(all_projects, "Proyecto B") ? "Si" : "No");
    printf("Existe tarea 'Diseño' en Proyecto A? %s\n", project_remove_task(projectA, "Diseño") ? "Si" : "No");

    project_delete(&all_projects, "Proyecto B");

    puts("\nDespués de los borrados:");
    project_show_all(all_projects);

    project_free_all(all_projects);
    return 0;
}