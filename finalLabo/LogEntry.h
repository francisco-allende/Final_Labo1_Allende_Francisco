#ifndef LOGENTRY_H_INCLUDED
#define LOGENTRY_H_INCLUDED

struct
{
 char date[11];
 char time[6];
 char serviceName[65];
 int gravedad;
 char msg[65];
}typedef eLogEntry;

#endif // LOGENTRY_H_INCLUDED

int menu();
eLogEntry* eLogEntry_new();
eLogEntry* eLogEntry_newParametros(char* dateStr, char* timeStr, char* serviceNameStr, char* gravedadStr, char* msgStr);
int eLogEntry_setDate(eLogEntry* this, char* date);
int eLogEntry_setTime(eLogEntry* this, char* time);
int eLogEntry_setServiceName(eLogEntry* this, char* serviceName);
int eLogEntry_setGravedad(eLogEntry* this, int gravedad);
int eLogEntry_setMsg(eLogEntry* this, char* msg);
int eLogEntry_getDate(eLogEntry* this, char* date);
int eLogEntry_getTime(eLogEntry* this, char* time);
int eLogEntry_getServiceName(eLogEntry* this, char* serviceName);
int eLogEntry_getGravedad(eLogEntry* this, int* gravedad);
int eLogEntry_getMsg(eLogEntry* this, char* msg);
void eLogEntry_delete(eLogEntry* eLogEntry);
int eLogEntry_print(eLogEntry* log);


int eLogEntry_filterByWarnings(void* pElement);
int eLogEntry_filterBy4a7(void* pElement);
int eLogEntry_filterByError(void* pElement);
int eLogEntry_filtByLeve(void* pElement);


























