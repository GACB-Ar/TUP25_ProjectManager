#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include "project_methods.h"

/* Guarda en fichero de texto 'filename' toda la lista de proyectos
   y sus tareas en formato indentado, traduciendo el estado a texto. */
bool save_projects_to_file(const struct Project *projects,
                           const char *filename);

/* Imprime en pantalla la misma lista en formato indentado. */
void list_projects_console(const struct Project *projects);

#endif /* FILE_H */