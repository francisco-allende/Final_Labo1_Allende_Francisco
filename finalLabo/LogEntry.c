#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LogEntry.h"

/** \brief menu general de opciones
 *
 * \return int
 *
 */
int menu()
{
    int opcion = 0;

    system("cls");
    printf("*****************************************\n");
    printf("*\t 		Menu log entry \t*\n");
    printf("*****************************************\n\n");
    printf("1 - Leer Log\n");
    printf("2 - Procesar informacion\n");
    printf("3 - Mostrar estadisticas\n");
    printf("4 - Imprimir lista logs\n");
    printf("5 - Salir\n");
    printf("\n\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}


//**************    Constructores   ********************

/** \brief instancia la estructura eLogEntry
 *
 * \return eLogEntry*
 *
 */
eLogEntry* eLogEntry_new()
{
    eLogEntry* newLog = NULL;

    newLog = (eLogEntry*) malloc(sizeof(eLogEntry));

    if(newLog != NULL)
    {
        strcpy(newLog->date, "nn");
        strcpy(newLog->time, "nn");
        strcpy(newLog->serviceName, "nn");
        newLog->gravedad = 0;
        strcpy(newLog->msg, "nn");
    }

    return newLog;
}



/** \brief instancia cada cmapo de la estructura eLogEntry
 *
 * \param dateStr char*
 * \param timeStr char*
 * \param serviceNameStr char*
 * \param gravedadStr char*
 * \param msgStr char*
 * \return eLogEntry*
 *
 */
eLogEntry* eLogEntry_newParametros(char* dateStr, char* timeStr, char* serviceNameStr, char* gravedadStr, char* msgStr)
{
    eLogEntry* newLog = eLogEntry_new();

    if(dateStr != NULL && timeStr != NULL && serviceNameStr != NULL && gravedadStr != NULL && msgStr)
    {
        if(!(eLogEntry_setDate(newLog, dateStr)
                && eLogEntry_setTime(newLog, timeStr)
                && eLogEntry_setServiceName(newLog, serviceNameStr)
                && eLogEntry_setGravedad(newLog, atoi(gravedadStr))
                && eLogEntry_setMsg(newLog, msgStr)
            ))
        {
            free(newLog);
            newLog = NULL;
        }
    }

    return newLog;
}

//**************    Setters     ********************


/** \brief setea el campo date
 *
 * \param this eLogEntry*
 * \param date char*
 * \return int
 *
 */
int eLogEntry_setDate(eLogEntry* this, char* date)
{
    int todoOk = 0;

    if(this != NULL && date != NULL)
    {
        if(strlen(date) >= 1 && strlen(date) < 12)
        {
            strcpy(this->date, date);

            todoOk = 1;
        }
    }
    return todoOk;
}



/** \brief setea el campo time
 *
 * \param this eLogEntry*
 * \param time char*
 * \return int
 *
 */
int eLogEntry_setTime(eLogEntry* this, char* time)
{
    int todoOk = 0;

    if(this != NULL && time != NULL)
    {
        if(strlen(time) >= 1 && strlen(time) < 7)
        {
            strcpy(this->time, time);

            todoOk = 1;
        }
    }

    return todoOk;
}


/** \brief setea el campo service by name
 *
 * \param this eLogEntry*
 * \param serviceName char*
 * \return int
 *
 */
int eLogEntry_setServiceName(eLogEntry* this, char* serviceName)
{
    int todoOk = 0;

    if(this != NULL && serviceName != NULL)
    {
        if(strlen(serviceName) >= 1 && strlen(serviceName) < 65)
        {
            strcpy(this->serviceName, serviceName);

            todoOk = 1;
        }
    }

    return todoOk;
}



/** \brief setea el campo gravedad
 *
 * \param this eLogEntry*
 * \param gravedad int
 * \return int
 *
 */
int eLogEntry_setGravedad(eLogEntry* this, int gravedad)
{
    int todoOk = 0;

    if(this != NULL)
    {
        this->gravedad = gravedad;

        todoOk = 1;
    }

    return todoOk;
}

/** \brief setea el campo mensaje
 *
 * \param this eLogEntry*
 * \param msg char*
 * \return int
 *
 */
int eLogEntry_setMsg(eLogEntry* this, char* msg)
{
    int todoOk = 0;

    if(this != NULL && msg != NULL)
    {
        if(strlen(msg) >= 1 && strlen(msg) < 65)
        {
            strcpy(this->msg, msg);

            todoOk = 1;
        }
    }

    return todoOk;
}
//**************    Getters     ********************


/** \brief gettea el campo date
 *
 * \param this eLogEntry*
 * \param date char*
 * \return int
 *
 */
int eLogEntry_getDate(eLogEntry* this, char* date)
{
    int todoOk = 0;

    if(this != NULL && date!= NULL)
    {
        strcpy(date, this->date);

        todoOk = 1;
    }

    return todoOk;
}


/** \brief gettea el campo time
 *
 * \param this eLogEntry*
 * \param time char*
 * \return int
 *
 */
int eLogEntry_getTime(eLogEntry* this, char* time)
{
    int todoOk = 0;

    if(this != NULL && time!= NULL)
    {
        strcpy(time, this->time);

        todoOk = 1;
    }

    return todoOk;
}


/** \brief gettea el campo service by name
 *
 * \param this eLogEntry*
 * \param serviceName char*
 * \return int
 *
 */
int eLogEntry_getServiceName(eLogEntry* this, char* serviceName)
{
    int todoOk = 0;

    if(this != NULL && serviceName != NULL)
    {
        strcpy(serviceName, this->serviceName);

        todoOk = 1;
    }

    return todoOk;
}



/** \brief gettea el campo gravedad
 *
 * \param this eLogEntry*
 * \param gravedad int*
 * \return int
 *
 */
int eLogEntry_getGravedad(eLogEntry* this, int* gravedad)
{
    int todoOk = 0;

    if(this != NULL && gravedad != NULL)
    {
        *gravedad = this->gravedad;

        todoOk = 1;
    }

    return todoOk;
}

/** \brief gettea el campo mensaje
 *
 * \param this eLogEntry*
 * \param msg char*
 * \return int
 *
 */
int eLogEntry_getMsg(eLogEntry* this, char* msg)
{
    int todoOk = 0;

    if(this != NULL && msg!= NULL)
    {
        strcpy(msg, this->msg);

        todoOk = 1;
    }

    return todoOk;
}

/** \brief borra una estructrua eLogEntry
 *
 * \param eLogEntry eLogEntry*
 * \return void
 *
 */
void eLogEntry_delete(eLogEntry* eLogEntry)
{
    free(eLogEntry);
}


/** \brief printea una estructura
 *
 * \param log eLogEntry*
 * \return int
 *
 */
int eLogEntry_print(eLogEntry* log)
{
    int todoOk = 0;

    if(log != NULL)
    {
        printf("%15s %15s   %40s\t\t   %d   %40s\n",
               log->date,
               log->time,
               log->serviceName,
               log->gravedad,
               log->msg);

        todoOk = 1;
    }

    return todoOk;
}


/*************** Filter pFunc ***********************/

/** \brief filtra por warnings ( gravedad = 3)
 *
 * \param pElement void*
 * \return int
 *
 */
int eLogEntry_filterByWarnings(void* pElement)
{
    int retorno = 0;
    eLogEntry* aux = NULL;

    if(pElement != NULL)
    {
        aux = (eLogEntry*) pElement;

        if(aux != NULL)
        {
            if(aux->gravedad == 3)
            {
                retorno = 1;
            }
        }
    }

    return retorno;
}

/** \brief filtra por gravedad mayor o menor a 7 inclusive
 *
 * \param pElement void*
 * \return int
 *
 */
int eLogEntry_filterBy4a7(void* pElement)
{
    int retorno = 0;
    eLogEntry* aux = NULL;

    if(pElement != NULL)
    {
        aux = (eLogEntry*) pElement;

        if(aux != NULL)
        {
            if(aux->gravedad >= 4 && aux->gravedad <= 7)
            {
                retorno = 1;
            }
        }
    }

    return retorno;
}

/** \brief filtra por errores (gravedad mayor a 7)
 *
 * \param pElement void*
 * \return int
 *
 */
int eLogEntry_filterByError(void* pElement)
{
    int retorno = 0;
    eLogEntry* aux = NULL;

    if(pElement != NULL)
    {
        aux = (eLogEntry*) pElement;

        if(aux != NULL)
        {
            if(aux->gravedad > 7)
            {
                retorno = 1;
            }
        }
    }

    return retorno;
}

/** \brief filtra por gravedad menor a 3
 *
 * \param pElement void*
 * \return int
 *
 */
int eLogEntry_filtByLeve(void* pElement)
{
    int retorno = 0;
    eLogEntry* aux = NULL;

    if(pElement != NULL)
    {
        aux = (eLogEntry*) pElement;

        if(aux != NULL)
        {
            if(aux->gravedad < 3)
            {
                retorno = 1;
            }
        }
    }

    return retorno;
}









