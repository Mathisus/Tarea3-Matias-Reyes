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
    Tarea *tareaActual = (Tarea *)firstTreeMap(mapa);
    
    while (tareaActual != NULL)
    {
        if (strcmp(tareaActual->nombre, nombreTarea) == 0)
        {
            return 1;
        }
        tareaActual = (Tarea *)nextTreeMap(mapa);
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
        Tarea *tareaAux = buscar_tarea(mapa, nombreTarea);
        Tarea *tarea_precedente = buscar_tarea(mapa, precedencia);

        if (tareaAux == NULL || tarea_precedente == NULL)
        {
            system("cls");
            puts("La tarea o la tarea precedente no se encuentran en el sistema, intente otra vez");

            system("pause");
            return;
        }

        pushBack(tareaAux->lista_precedencia, tarea_precedente);
        printf("Se ha definido la tarea %s como precedente de la tarea %s\n", tarea_precedente->nombre, tareaAux->nombre);
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
    
    while (precedenteAux != NULL)
    {
        printf("%s ", precedenteAux);
        precedenteAux = (Tarea *)nextList(tarea->lista_precedencia);
    }
    printf("\n");
    
}

void llenarLista(List *lista, TreeMap *mapa)
{
    Tarea *tarea_aux = (Tarea *)firstTreeMap(mapa);

    while (tarea_aux != NULL)
    {
        pushBack(lista, tarea_aux);
        tarea_aux = (Tarea *)nextTreeMap(mapa);
    }
}

void mostrarTareasPendientes(TreeMap *mapa)
{
    Tarea *tarea_aux = (Tarea *)firstTreeMap(mapa);
    List *ListaCompleta = createList();
    llenarLista(ListaCompleta, mapa);

    while (tarea_aux != NULL)
    {
        mostrar(tarea_aux);
        tarea_aux = (Tarea *)nextTreeMap(mapa);
    }

    puts("No existen mas tareas pendientes");
    system("pause");
}

void tareaRealizada(TreeMap *mapa, char* tarea)
{
    if(is_in_tree(mapa, tarea) == 0)
    {
        puts("La tarea no existe en la lista o ya fue completada, por favor intentelo de nuevo\n");
        system("pause");
        return;
    }   

    Tarea* tareaAux = firstTreeMap(mapa);

    while(tareaAux != NULL)
    {   
        Tarea* precedenciaActual = firstList(tareaAux->lista_precedencia);
        if(firstList(tareaAux->lista_precedencia) != NULL)
        {   
            while(precedenciaActual != NULL)
            {
                if(strcmp(precedenciaActual->nombre,tarea) == 0)
                {
                    popCurrent(tareaAux->lista_precedencia);
                }
                precedenciaActual = nextList(tareaAux->lista_precedencia);
            }
        }

        tareaAux = nextTreeMap(mapa);
    }

    findTask(mapa, tarea);

    eraseTreeMap(mapa);

    puts("La tarea ha sido marcada como completada exitosamente");

    system("pause");
}


