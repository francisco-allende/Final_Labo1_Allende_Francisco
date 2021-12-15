#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

int controller_loadFromText(char* path, LinkedList* pArrayListPelis);
int controller_ListLog(LinkedList* pArrayListLog);
int controller_saveAsText(char* path, LinkedList* pArrayListPelis);
float controller_calcularPorcentaje(LinkedList* pArrayListLog, LinkedList* listaFiltrada);

#endif // CONTROLLER_H_INCLUDED
