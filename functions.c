#include "functions.h"
#include "treemap.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAXCHAR 30

void mostrar_menu()
{   
    puts("-----------------------------------------------");
    puts("Bienvenido al programa, Ingrese una opcion:");
    puts("-----------------------------------------------");
    printf("1. Agregar tarea\n");
    printf("2. Definir precedencia entre tareas\n");
    printf("3. Mostrar tareas pendientes\n");
    printf("4. Marcar tarea como realizada\n");
    printf("5. Salir\n");
    puts("-----------------------------------------------");
}

int esta_presente(TreeMap *mapa, char *nombreTarea)
{
    Tarea *current_task = (Tarea *)firstTreeMap(mapa);
    
    while (current_task != NULL)
    {
        if (strcmp(current_task->nombre, nombreTarea) == 0)
        {
            return 1;
        }
        current_task = (Tarea *)nextTreeMap(mapa);
    }

    return 0;
}

void agregarTarea(TreeMap *mapa, char *nombreTarea, char* prioridad)
{
    Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea));

    if(esta_presente(mapa, nombreTarea) == 1)
    {
        system("cls");
        puts("La tarea ya se encuentra en el sistema, intente otra vez");

        system("pause");
    }

    strcpy(nuevaTarea->nombre, nombreTarea);
    strcpy(nuevaTarea->prioridad, prioridad);
    nuevaTarea->lista_precedencia = createList();

    insertTreeMap(mapa, nuevaTarea->prioridad, nuevaTarea);

    return;
}

Tarea* buscar_tarea(TreeMap *mapa, char *precedencia)
{
    Tarea *tarea_aux = (Tarea*) firstTreeMap(mapa);
    
    while (tarea_aux != NULL)
    {
        if (strcmp(precedencia, tarea_aux->nombre) == 0)
        {
            return tarea_aux;
        }
        tarea_aux = (Tarea *)nextTreeMap(mapa);
    }

    return NULL;
}

void definirPrecedencia(TreeMap *mapa, char *nombreTarea, char* precedencia)
{
    if(strcmp(nombreTarea, precedencia) == 0)
    {
        puts("No se puede definir una tarea como precedente de si misma, intentelo otra vez");
        system("pause");
        return;
    }

    if (esta_presente(mapa, nombreTarea) == 1 || esta_presente(mapa, precedencia) == 1)
    {   
        Tarea *tarea = buscar_tarea(mapa, nombreTarea);
        Tarea *tarea_precedente = buscar_tarea(mapa, precedencia);

        if (tarea == NULL || tarea_precedente == NULL)
        {
            system("cls");
            puts("La tarea o la tarea precedente no se encuentran en el sistema, intente otra vez");

            system("pause");
            return;
        }

        pushBack(tarea_aux->lista_precedencia, tarea_precedente);
        printf("Se ha definido la tarea %s como precedente de la tarea %s\n", tarea_precedente->nombre, tarea_aux->nombre);
        system("pause");

        return;
    }else{
        puts("La tarea o la tarea precedente no se encuentran en el sistema, intente otra vez");
        system("pause");
    }
}

void mostrar(Tarea* tarea)
{
    printf("Nombre: %s - Prioridad: %s \n", tarea->nombre, tarea->prioridad);
    Tarea *precedenteAux = (Tarea *)firstList(tarea->lista_precedencia);

    if("")
}