#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "LogEntry.h"
#include "parser.h"


/** \brief carga el archivo txt llamando al parser
 *
 * \param path char*
 * \param pArrayListLog LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListLog)
{
    int todoOk = 0;

    if(path != NULL && pArrayListLog != NULL)
    {
        FILE* fTxt = fopen(path, "r"); //abro en modo lectura

        if(fTxt != NULL)
        {
            todoOk = parser_LogsFromText(fTxt, pArrayListLog);
            fclose(fTxt);
        }
    }

    return todoOk;
}


/** \brief lista todos los elementos de una lista
 *
 * \param pArrayListLog LinkedList*
 * \return int
 *
 */
int controller_ListLog(LinkedList* pArrayListLog)
{
    int todoOk = 0;
    eLogEntry* aux = NULL;
    int tam = ll_len(pArrayListLog);


    if(pArrayListLog != NULL && tam > 0)
    {
        system("cls");
        printf("*****************************************************************************************************************************\n");
        printf("\tFecha\t  	Hora\t\t  	 \tNombre servicio\t    \tGravedad\t\t   \t\tMensaje Error\n");
        printf("*****************************************************************************************************************************\n\n");

        for(int i = 0; i < tam; i++)
        {
            aux = ll_get(pArrayListLog, i);
            eLogEntry_print(aux);
        }

        todoOk = 1;
    }

    return todoOk;
}


/** \brief guarda en un txt una lista
 *
 * \param path char*
 * \param pArrayListLog LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListLog)
{

    int todoOk = 0;
    eLogEntry* log = NULL;

    char date[11];
    char time[6];
    char serviceName[65];
    int gravedad;
    char msg[65];

    int tam = ll_len(pArrayListLog);

    if(path != NULL && pArrayListLog != NULL)
    {
        FILE* f = fopen(path, "w"); //lo abro en modo escritura txt
        log = eLogEntry_new(); //instancio al logleado para cargar bien los getters

        if(f != NULL && log != NULL)
        {
            fprintf(f, "Fecha; Hora; Nombre Servicio; Gravedad; Mensaje Error\n"); //cargo la data de las columnas

            for(int i = 0; i < tam; i++)
            {
                log = ll_get(pArrayListLog, i); //me traigo un logleado por iteracion

                if(log != NULL)
                {
                    eLogEntry_getDate(log, date);
                    eLogEntry_getTime(log, time);
                    eLogEntry_getServiceName(log, serviceName);
                    eLogEntry_getGravedad(log, &gravedad);
                    eLogEntry_getMsg(log, msg);

                    fprintf(f, "%s,%s,%s,%d,%s\n", date, time, serviceName, gravedad, msg);
                    todoOk = 1;
                }
            }
        }

        fclose(f);
    }

    return todoOk;
}

/** \brief calcula el porcentaje de una lista sobre otra
 *
 * \param pArrayListLog LinkedList*
 * \param listaFiltrada LinkedList*
 * \return float
 *
 */
float controller_calcularPorcentaje(LinkedList* pArrayListLog, LinkedList* listaFiltrada)
{
    float total = -1;
    int todo = ll_len(pArrayListLog);
    int parte = ll_len(listaFiltrada);

    total = (float) (parte * 100) / todo;

    return total;
}






















