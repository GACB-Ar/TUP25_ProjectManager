#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_ESTADO 20
#define MAX_FECHA 11

// Estructura de Tarea
typedef struct Tarea {
	char nombre[MAX_NOMBRE];
	char responsable[MAX_NOMBRE];
	char estado[MAX_ESTADO]; // "pendiente", "en progreso", "completada"
	char fecha[MAX_FECHA];   // formato: "AAAA-MM-DD"
	int prioridad;           // 1: Alta, 2: Media, 3: Baja
	struct Tarea *sig;
} Tarea;

// Estructura de Proyecto
typedef struct Proyecto {
	char nombreProyecto[MAX_NOMBRE];
	Tarea *listaTareas;
	struct Proyecto *sig;
} Proyecto;

// Prototipos
void menu();
Proyecto *crearProyecto(Proyecto *lista);
Proyecto *buscarProyecto(Proyecto *lista, const char *nombre);
Proyecto *eliminarProyecto(Proyecto *lista, const char *nombre);
void eliminarTarea(Proyecto *lista);
Proyecto modificarProyecto(Proyecto *lista);
void modificarTarea(Proyecto *lista);
void agregarTarea(Proyecto *proyecto);
void mostrarTareasPorProyecto(Proyecto *lista);
void mostrarTareasPorResponsable(Proyecto *lista);
void buscarTarea(Proyecto *lista);
void ordenarTareasPorFecha(Tarea **inicio);
void ordenarTareasPorPrioridad(Tarea **inicio);
void guardarEnArchivo(Proyecto *lista);
Proyecto *cargarDesdeArchivo();

// Funciones auxiliares
void limpiarBuffer() {
	while (getchar() != '\n');
}

void leerCadena(char *cadena, int tam) {
	fgets(cadena, tam, stdin);
	cadena[strcspn(cadena, "\n")] = '\0';
}

int main() {
	Proyecto *proyectos = cargarDesdeArchivo();
	menu(proyectos);
	guardarEnArchivo(proyectos);
	return 0;
}

void menu(Proyecto *lista) {
	int opcion;
	char nombreProyecto[MAX_NOMBRE];
	Proyecto *p;
	
	do {
		printf("\n--- MENU ---\n");
		printf("1. Crear proyecto\n");
		printf("2. Agregar tarea\n");
		printf("3. Mostrar tareas por proyecto\n");
		printf("4. Mostrar tareas por responsable\n");
		printf("5. Buscar tarea por nombre o estado\n");
		printf("6. Eliminar proyecto\n");
		printf("7. Eliminar tarea\n");
		printf("8. Modificar proyecto\n");
		printf("9. Modificar tarea\n");
		printf("10. Guardar y salir\n");
		printf("Seleccione una opci\u00f3n: ");
		scanf("%d", &opcion);
		limpiarBuffer();
		
		switch(opcion) {
		case 1:
			lista = crearProyecto(lista);
			break;
		case 2:
			printf("Ingrese nombre del proyecto: ");
			leerCadena(nombreProyecto, MAX_NOMBRE);
			p = buscarProyecto(lista, nombreProyecto);
			if (p) agregarTarea(p);
			else printf("Proyecto no encontrado.\n");
			break;
		case 3:
			mostrarTareasPorProyecto(lista);
			break;
		case 4:
			mostrarTareasPorResponsable(lista);
			break;
		case 5:
			buscarTarea(lista);
			break;
		case 6:
			printf("Ingrese el nombre del proyecto a eliminar: ");
			leerCadena(nombreProyecto, MAX_NOMBRE);
			lista = eliminarProyecto(lista, nombreProyecto);
			break;
		case 7:
			eliminarTarea(lista);
			break;
		case 8:
			modificarProyecto(lista);
			break;
		case 9:
			modificarTarea(lista);
			break;
		case 10:
			printf("Guardando y saliendo...\n");
			break;
		default:
			printf("Opcion invalida.\n");
		}
	} while (opcion != 10);
}

Proyecto *modificarProyecto (Proyecto *lista) {
	char nombre[MAX_NOMBRE];
	printf("Ingrese el nombre del proyecto a modificar: ");
	leerCadena(nombre, MAX_NOMBRE);
	Proyecto *p = buscarProyecto(lista, nombre);
	if (!p) {
		printf("Proyecto no encontrado.\n");
		return lista;
	}
	printf("Nuevo nombre del proyecto: ");
	leerCadena(p->nombreProyecto, MAX_NOMBRE);
	printf("Proyecto modificado.\n");
	return lista;
}

void modificarTarea(Proyecto *lista) {
	char nombreProyecto[MAX_NOMBRE], nombreTarea[MAX_NOMBRE];
	printf("Ingrese nombre del proyecto: ");
	leerCadena(nombreProyecto, MAX_NOMBRE);
	Proyecto *p = buscarProyecto(lista, nombreProyecto);
	if (!p) {
		printf("Proyecto no encontrado.\n");
		return;
	}
	printf("Ingrese nombre de la tarea a modificar: ");
	leerCadena(nombreTarea, MAX_NOMBRE);
	Tarea *t = p->listaTareas;
	while (t) {
		if (strcmp(t->nombre, nombreTarea) == 0) {
			printf("Nuevo nombre: ");
			leerCadena(t->nombre, MAX_NOMBRE);
			printf("Nuevo responsable: ");
			leerCadena(t->responsable, MAX_NOMBRE);
			printf("Nuevo estado (pendiente/en progreso/completada): ");
			leerCadena(t->estado, MAX_ESTADO);
			printf("Nueva fecha (AAAA-MM-DD): ");
			leerCadena(t->fecha, MAX_FECHA);
			printf("Nueva prioridad (1: Alta, 2: Media, 3: Baja): ");
			scanf("%d", &t->prioridad);
			limpiarBuffer();
			printf("Tarea modificada.\n");
			return;
		}
		t = t->sig;
	}
	printf("Tarea no encontrada.\n");
}

// Las dem�s funciones (crearProyecto, buscarProyecto, etc.) permanecen sin cambios

void guardarEnArchivo(Proyecto *lista) {
	FILE *f = fopen("proyectos.txt", "w");
	if (!f) return;
	while (lista) {
		fprintf(f, "#%s\n", lista->nombreProyecto);
		Tarea *t = lista->listaTareas;
		while (t) {
			fprintf(f, "%s;%s;%s;%s;%d\n", t->nombre, t->responsable, t->estado, t->fecha, t->prioridad);
			t = t->sig;
		}
		lista = lista->sig;
	}
	fclose(f);
}

Proyecto *cargarDesdeArchivo() {
	FILE *f = fopen("proyectos.txt", "r");
	if (!f) return NULL;
	Proyecto *lista = NULL, *actual = NULL;
	char linea[200];
	while (fgets(linea, sizeof(linea), f)) {
		if (linea[0] == '#') {
			Proyecto *nuevo = malloc(sizeof(Proyecto));
			strcpy(nuevo->nombreProyecto, linea + 1);
			nuevo->nombreProyecto[strcspn(nuevo->nombreProyecto, "\n")] = '\0';
			nuevo->listaTareas = NULL;
			nuevo->sig = lista;
			lista = nuevo;
			actual = nuevo;
		} else {
			Tarea *t = malloc(sizeof(Tarea));
			sscanf(linea, "%[^;];%[^;];%[^;];%[^;];%d",
				   t->nombre, t->responsable, t->estado, t->fecha, &t->prioridad);
			t->sig = actual->listaTareas;
			actual->listaTareas = t;
		}
	}
	fclose(f);
	return lista;
}
