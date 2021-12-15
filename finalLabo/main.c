#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "parser.h"
#include "LogEntry.h"


int main()
{
    int option;
    int flagProcesado = 0;
    char msjCarga[140] = "Asegurese antes de cargar los datos (1)  y procesarlos (2). Solo se puede cargar ambas opciones una vez\n\n";
    char nombreArchivo[100];
    float totalLeve;
    float total4a7;
    float totalWarnings;
    float totalErrors;


    LinkedList* listaLogs = ll_newLinkedList();
    LinkedList* listaLeve = NULL;
    LinkedList* listaWarnings = NULL;
    LinkedList* lista4a7 = NULL;
    LinkedList* listaErrors = NULL;

    do
    {
        switch(menu())
        {
        case 1:
            printf("\nIndique el nombre del archivo a cargar. \n");
            fflush(stdin);
            scanf("%s", nombreArchivo);
            strcat(nombreArchivo, ".txt");
            while(strlen(nombreArchivo) > 100)
            {
                printf("Ingrese un nombre mas corto: \n");
                gets(nombreArchivo);
            }

            if(ll_isEmpty(listaLogs) || strcmp(nombreArchivo, "log.csv") != 0)
            {
                if(!controller_loadFromText(nombreArchivo, listaLogs))
                {
                    printf("No se pudieron cargar todos los datos en texto correctamente\n\n");
                }
                else
                {
                    system("cls");
                    printf("\n***\t Carga del archivo de texto exitosa! ***\n\n");
                }
            }
            else
            {
                printf("El archivo ya fue cargado. Solo se puede cargar una vez.\n\n");
            }
            break;

        case 2:
            if(!ll_isEmpty(listaLogs) && !flagProcesado)
            {

                listaLeve = ll_filter(listaLogs, eLogEntry_filtByLeve);

                lista4a7 = ll_filter(listaLogs, eLogEntry_filterBy4a7);

                if(lista4a7 != NULL)
                {
                    controller_ListLog(lista4a7);
                }

                listaWarnings = ll_filter(listaLogs, eLogEntry_filterByWarnings);

                if(listaWarnings != NULL)
                {
                    if(controller_saveAsText("warnings.txt", listaWarnings))
                    {
                        printf("Lista warning guardada con exito\n\n");
                    }
                }

                listaErrors = ll_filter(listaLogs, eLogEntry_filterByError);

                if(listaErrors != NULL)
                {
                    if(controller_saveAsText("errors.txt", listaErrors))
                    {
                        printf("Lista errors guardada con exito\n\n");
                    }
                }

                flagProcesado = 1;
            }
            else
            {
                printf("%s", msjCarga);
            }
            break;

        case 3:
            if(!ll_isEmpty(listaLogs) && flagProcesado)
            {
                totalLeve = controller_calcularPorcentaje(listaLogs, listaLeve);

                if(totalLeve > -1)
                {
                    controller_ListLog(listaLeve);
                    printf("\n\n");
                    printf("*** Gravedad menor a 3 ***\n\n");
                    printf("El porcentaje de errores de gravedad menor a 3 es de %.2f porciento sobre el total de la lista\n\n", totalLeve);
                    system("pause");
                }


                total4a7 = controller_calcularPorcentaje(listaLogs, lista4a7);

                if(total4a7 > -1)
                {
                    controller_ListLog(lista4a7);
                    printf("\n\n");
                    printf("*** Gravedad entre 4 y 7 inclusive ***\n\n");
                    printf("El porcentaje de errores de gravedad entre 4 y 7 inclusive es de %.2f porciento sobre el total de la lista\n\n",
                    total4a7);
                    system("pause");
                }


                totalWarnings = controller_calcularPorcentaje(listaLogs, listaWarnings);

                if(totalWarnings > -1)
                {
                    controller_ListLog(listaWarnings);
                    printf("\n\n");
                    printf("*** Warning. Gravedad = 3 ***\n\n");
                    printf("El porcentaje de errores de gravedad warning es de %.2f porciento sobre el total de la lista\n\n", totalWarnings);
                    system("pause");
                }


                totalErrors = controller_calcularPorcentaje(listaLogs, listaErrors);

                if(totalErrors > -1)
                {
                    controller_ListLog(listaErrors);
                    printf("\n\n");
                    printf("*** Error. Gravedad mayor a 7 ***\n\n");
                    printf("El porcentaje de errores de gravedad error es de %.2f porceinto sobre el total de la lista\n\n", totalErrors);
                    system("pause");
                }
            }
            else
            {
                printf("%s", msjCarga);
            }
            break;

        case 4:
            if(!ll_isEmpty(listaLogs))
            {
                if(!controller_ListLog(listaLogs))
                {
                    printf("No se pudo mostrar el listado de logs\n");
                }
            }
            else
            {
                printf("%s ", msjCarga);
            }
            break;

        case 5:
            printf("\nAdios!\n");
            option = -1;
            break;

        default:
            printf("Error, esa opcion es inexistente. Vuelvalo a intentar \n");
            break;
        }

        printf("\n\n");
        system("pause");
    }
    while(option != -1);

    //elimino las listas y devuevlo el espacio pedido en memoria
    ll_deleteLinkedList(listaLogs);
    ll_deleteLinkedList(listaLeve);
    ll_deleteLinkedList(listaWarnings);
    ll_deleteLinkedList(lista4a7);
    ll_deleteLinkedList(listaErrors);

    return 0;
}
