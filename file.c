#include "file.h"
#include "task_methods.h"
#include <stdio.h>
#include <stdbool.h>

/* Traducir el código de estado a cadena */
static const char * status_to_str(int status) {
    switch (status) {
    case 0: return "pendiente";
    case 1: return "en progreso";
    case 2: return "completada";
    default: return "desconocido";
    }
}

bool save_projects_to_file(const struct Project *projects,
                           const char *filename)
{
    if (!projects || !filename) return false;
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return false;
    }

    for (const struct Project *p = projects; p; p = p->next) {
        /* Proyecto: traducir estado */
        fprintf(f,
            "Proyecto: %s | %s | %s | %s\n",
            p->name,
            p->created_date,
            p->created_by,
            status_to_str(p->status)
        );
        /* Tareas: traducir estado */
        for (const struct Task *t = p->tasks; t; t = t->next) {
            fprintf(f,
                "    - %s | %s | %s | %s\n",
                t->name,
                t->created_date,
                t->created_by,
                status_to_str(t->status)
            );
        }
    }

    fclose(f);
    return true;
}

void list_projects_console(const struct Project *projects)
{
    if (!projects) {
        puts("(no hay proyectos)");
        return;
    }

    for (const struct Project *p = projects; p; p = p->next) {
        printf("Proyecto: %s | %s | %s | %s\n",
               p->name,
               p->created_date,
               p->created_by,
               status_to_str(p->status)
        );
        for (const struct Task *t = p->tasks; t; t = t->next) {
            printf("    - %s | %s | %s | %s\n",
                   t->name,
                   t->created_date,
                   t->created_by,
                   status_to_str(t->status)
            );
        }
    }
}
