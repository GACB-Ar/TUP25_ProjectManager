#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task_methods.h"
#include "project_methods.h"
#include "file.h"

/* Lee una línea de stdin, quita '\n' final */
static void read_line(const char *prompt, char *buf, size_t sz) {
    printf("%s", prompt);
    if (!fgets(buf, sz, stdin)) {
        perror("fgets");
        exit(1);
    }
    buf[strcspn(buf, "\n")] = '\0';
}

int main(void) {
    struct Project *all_projects = NULL;
    char projectName[128];
    char taskName[128];
    char date[16];
    char user[64];
    int  status;
    int  opt;

    do {
        puts("\n--- Project Manager ---");
        puts("1) Crear proyecto");
        puts("2) Listar proyectos");
        puts("3) Borrar proyecto");
        puts("4) Añadir tarea a proyecto");
        puts("5) Borrar tarea de proyecto");
        puts("6) Ordenar tareas de un proyecto");
        puts("7) Buscar tarea por nombre");
        puts("8) Guardar proyectos en archivo");
        puts("9) Listar proyectos desde archivo");
        puts("0) Salir");
        printf("Opción: ");
        if (scanf("%d%*c", &opt) != 1) break;

        switch (opt) {
        case 1:
            read_line("Nombre del proyecto: ", projectName, sizeof projectName);
            read_line("Fecha (YYYY-MM-DD): ", date, sizeof date);
            read_line("Usuario: ", user, sizeof user);
            printf("Estado (0=pend,1=en proc,2=comp): ");
            if (scanf("%d%*c", &status) != 1) status = 0;
            {
                struct Project *p = project_create(
                    projectName, date, user, status
                );
                if (!p) {
                    fprintf(stderr, "Error creando proyecto\n");
                } else {
                    project_insert_end(&all_projects, p);
                }
            }
            break;

        case 2:
            project_show_all(all_projects);
            break;

        case 3:
            read_line("¿Qué proyecto borro? ", projectName, sizeof projectName);
            if (!project_delete(&all_projects, projectName))
                puts("Proyecto no encontrado.");
            break;

        case 4:
            read_line("Proyecto destino: ", projectName, sizeof projectName);
            {
                struct Project *p = project_find(all_projects, projectName);
                if (!p) {
                    puts("Proyecto no existe.");
                    break;
                }
                read_line("Nombre tarea: ", taskName, sizeof taskName);
                read_line("Fecha tarea: ", date, sizeof date);
                read_line("Usuario tarea: ", user, sizeof user);
                printf("Estado tarea (0/1/2): ");
                if (scanf("%d%*c", &status) != 1) status = 0;

                project_add_task(p, taskName, date, user, status);
            }
            break;

        case 5:
            read_line("Proyecto: ", projectName, sizeof projectName);
            {
                struct Project *p = project_find(all_projects, projectName);
                if (!p) { puts("Proyecto no existe."); break; }
                read_line("Tarea a borrar: ", taskName, sizeof taskName);
                if (!project_remove_task(p, taskName))
                    puts("Tarea no encontrada.");
            }
            break;

        case 6:
            read_line("Proyecto para ordenar tareas: ",
                      projectName, sizeof projectName);
            {
                struct Project *p = project_find(all_projects, projectName);
                if (!p) { puts("Proyecto no existe."); break; }
                task_sort_by_date(&p->tasks);
                puts("Tareas ordenadas por fecha.");
            }
            break;

        case 7:
            read_line("Ingresar el nombre del Proyecto donde quiere buscar la tarea: ", projectName, sizeof projectName);
            {
                struct Project *p = project_find(all_projects, projectName);
                if (!p) { puts("Proyecto no existe."); break; }
                read_line("Nombre exacto de la tarea: ",
                          taskName, sizeof taskName);

                struct Task *t = task_find(p->tasks, taskName);
                if (t) {
                    printf("Encontrada:\n"
                           "  - Nombre : %s\n"
                           "  - Fecha  : %s\n"
                           "  - Usuario: %s\n"
                           "  - Estado : %d\n",
                           t->name,
                           t->created_date,
                           t->created_by,
                           t->status);
                } else {
                    puts("Tarea no encontrada.");
                }
            }
            break;

        case 8:
            if (save_projects_to_file(all_projects, "proyectos.txt"))
                puts("Guardado en 'proyectos.txt' OK.");
            else
                puts("Error guardando en archivo.");
            break;

        case 9:
            list_projects_console(all_projects);
            break;
        default:
            puts("Opción inválida.");
        case 0:
            break;
        }
    } while (opt != 0);

    project_free_all(all_projects);
    return 0;
}