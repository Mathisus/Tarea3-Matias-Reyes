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
            /* code */
            break;
        
        default:
            break;
        }
        
    }

}