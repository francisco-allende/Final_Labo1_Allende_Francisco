#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "LogEntry.h"


/** \brief parsea a texto el archivo enviado por parametro
 *
 * \param pFile FILE*
 * \param pArrayListeLogEntry LinkedList*
 * \return int
 *
 */
int parser_LogsFromText(FILE* pFile , LinkedList* pArrayListeLogEntry)
{
	int todoOk = 0;

	eLogEntry* auxLogEntry = NULL;
	char buffer[5][80];
	int cant;

	if(pFile!= NULL && pArrayListeLogEntry != NULL)
	{
		fscanf(pFile, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]); //lectura fantasma

		while(!feof(pFile))
		{
			cant = fscanf(pFile, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]); //lectura real

			if(cant == 5)
			{
				auxLogEntry = eLogEntry_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

				if(auxLogEntry!=NULL)
				{
					if(!ll_add(pArrayListeLogEntry, auxLogEntry))
					{
						todoOk = 1;
					}
					else
					{
						eLogEntry_delete(auxLogEntry);
						todoOk = 0;
						break;
					}
				}
			}
		}
	}

	return todoOk;
}
