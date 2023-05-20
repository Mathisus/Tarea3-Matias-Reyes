#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "treemap.h"
#include <unistd.h>
#define MAXCHAR 30

int lower_than_string(void* key1, void* key2)
{
    char* k1 = (char *)key1;
    char* k2 = (char *)key2;
    if (strcmp(k1, k2) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enter_value(char *value, char* mostrarTexto)
{
    puts("-------------------------------");
    printf("%s\n", mostrarTexto);
    puts("-------------------------------");

    scanf("%30[^\n]s", value);

    while (getchar() != '\n');
}

int main()
{
    TreeMap *tareas = createTreeMap(lower_than_string);

    while(1)
    {
        mostrar_menu();
        int opcion;
        scanf("%d", &opcion);

        while (getchar() != '\n');

        char nombreTarea[MAXCHAR];
        char prioridad[MAXCHAR];
        char precedencia[MAXCHAR];

        switch (opcion)
        {
        case 1:
            system("cls");

            enter_value(nombreTarea, "Ingrese el nombre de la tarea");
            enter_value(prioridad, "Ingrese la prioridad de la tarea");

            agregarTarea(tareas, nombreTarea, prioridad);

            puts("Tarea agregada con exito");

            system("pause");
            system("cls");
            break;

        case 2:
            enter_value(nombreTarea, "Ingrese el nombre de la tarea");
            enter_value(precedencia, "Ingrese la tarea de la cual depende");

            definirPrecedencia(tareas, nombreTarea, precedencia);

            break;

        case 3:
            system("cls");

            mostrarTareasPendientes(tareas);

            system("pause");
            system("cls");
            break;

        case 4:
            system("cls");

            enter_value(nombreTarea, "Ingrese el nombre de la tarea");

            tareaRealizada(tareas, nombreTarea);

            system("pause");
            system("cls");
            break;
        
        case 5:
            system("cls");

            puts("Gracias por usar el programa");

            system("pause");
            system("cls");
            break;

        default:
            break;
        }
        
    }

}