#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size = 0;
        this->pFirstNode = NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (myNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* myNode = NULL;
    int tam = ll_len(this);

    if(this != NULL && nodeIndex >= 0 && nodeIndex < tam)
    {
        myNode = this->pFirstNode; //consiguo la dira del nodo 0

        for(int i = 0; i < nodeIndex; i++) //nodeIndex es el tam
        {
            myNode = myNode->pNextNode;
        }

        /*
        while(nodeIndex > 0)
        {
            myNode = myNode->pNextNode; //actualizo el nodo en el que estoy parado con la dire en memoria del que viene atras
            nodeIndex--; //decremento hasta el primer nodo en el indice 0
        }
        */
    }

    return myNode;
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int tam = ll_len(this);

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= tam)
    {

        Node* newNode = NULL; //creo el nuevo nodo. Inicializo de manera segura
        Node* nodoAnterior = NULL;

        newNode = (Node*) malloc(sizeof(Node)); //pido espacio en memoria dinamica para el nuevo nodo

        if(newNode != NULL)
        {

            newNode->pElement = pElement; //hago que mi nuevo vagon apunte a la carga (cargo mi nuevo nodo)

            newNode->pNextNode = getNode(this, nodeIndex); //embocar un vagon en el tren. Lo hago remplazando la posicion donde esta el q quiero remplazar

            if(nodeIndex == 0)
            {
                this->pFirstNode = newNode;
            }
            else
            {
                nodoAnterior = getNode(this, nodeIndex -1);
                nodoAnterior->pNextNode = newNode;
            }

            this->size++;

            returnAux = 0;
        }
        else
        {
            printf("No se consiguio espacio en memoria para un nuevo nodo\n");
        }
    }


    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    return addNode(this, ll_len(this), pElement); //la funcion addNode ya la tengo hecha. Solo la llamo pasando los parametros correctos.
}


/** \brief Permite obtener un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* node = NULL;

    node = getNode(this, index);

    if(node != NULL)
    {
        returnAux = node->pElement;
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* aux = NULL;
    int tam = ll_len(this);

    if(this != NULL && index >=0 && index < tam)
    {
        aux = getNode(this, index);
        if(aux != NULL)
        {
            aux->pElement = pElement;

            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int tam = ll_len(this);

    Node* nodeToRemove = NULL;
    Node* nodoAnterior = NULL;

    if(this != NULL &&  index >= 0 && index < tam)
    {
        nodeToRemove = getNode(this, index);

        if(index == 0)
        {
            this->pFirstNode = nodeToRemove->pNextNode;
        }
        else
        {
            nodoAnterior = getNode(this, index-1);
            nodoAnterior->pNextNode = nodeToRemove->pNextNode;
        }

        free(nodeToRemove);
        this->size--;
        returnAux = 0;
    }


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        while(ll_len(this) > 0)
        {
            returnAux = ll_remove(this, 0);
            if(returnAux != 0)
            {
                break;
            }
        }

        returnAux = 0;
    }


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(!ll_clear(this))
        {
            free(this);
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    int tam = ll_len(this);

    if(this!=NULL)
    {
        for(int i = 0; i < tam; i++)
        {

            if(ll_get(this, i) == pElement)
            {
                returnAux = i;
                break;
            }
        }
    }


    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        int tam = ll_len(this);

        if( tam > 0)
        {
            returnAux = 0;
        }
        else if(tam == 0)
        {
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this, index, pElement);
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    int tam = ll_len(this);

    if(this != NULL &&  index >= 0 && index < tam)
    {
        returnAux = ll_get(this, index);
        ll_remove(this, index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = 0;
        if(ll_indexOf(this, pElement) != -1)
        {
            returnAux =1;
        }
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int tam = ll_len(this);
    void* aux;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;
        for(int i = 0; i < tam; i++)
        {
            aux = ll_get(this2, i);
            if(!ll_contains(this, aux))
            {
                returnAux = 0;
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL && from < to && from >= 0 && to <= ll_len(this))
    {

        cloneArray = ll_newLinkedList();
        if(cloneArray != NULL)
        {
            for(int i = from; i < to; i++)
            {
                ll_add(cloneArray, ll_get(this, i));
            }
        }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    return ll_subList(this, 0, ll_len(this));
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int tam = ll_len(this);
    void* aux = NULL;

    if(this != NULL && pFunc != NULL && order >= 0 && order <= 1)
    {
        for(int i = 0; i < tam -1; i++)
        {
            for(int j = i+1; j < tam; j++)
            {
                if(
                    (pFunc(ll_get(this, i), ll_get(this, j)) > 0 && order)
                    || (pFunc(ll_get(this, i), ll_get(this, j)) < 0 && !order)
                )
                {
                    aux = ll_get(this, i);
                    ll_set(this, i, ll_get(this, j));
                    ll_set(this, j, aux);
                }
            }
        }

        returnAux = 0;
    }
    return returnAux;

}

/** \brief filtra segun el criterio que devuelve pfunc
 *
 * \param void*
 * \return LinkedList* ll_filter(LinkedList* this,
 *
 */
LinkedList* ll_filter(LinkedList* this, int(*pFunc)(void*))
{
    LinkedList* filterList = NULL;
    int tam = ll_len(this);
    void* aux = NULL;

    if(this != NULL && pFunc != NULL)
    {
        filterList = ll_newLinkedList();

        if(filterList != NULL)
        {
            for(int i = 0; i < tam; i++)
            {
                aux = ll_get(this, i);

                if(pFunc(aux)) //retorna 1 si la carga a la filter list, 0 sino cumple los requisitos
                {
                    if(ll_add(filterList, aux)) //en caso de que no se pueda cargar
                    {
                        ll_deleteLinkedList(filterList);
                        filterList = NULL;
                        break;
                    }
                }
            }
        }
    }

    return filterList;
}

LinkedList* ll_map(LinkedList* lista, void* (*pFunc) (void*))
{
    LinkedList* newList = NULL;
    newList = ll_newLinkedList();
    int tam = ll_len(lista);

    for(int i=0; i < tam; i++)
    {
        ll_add(newList, pFunc(ll_get(lista, i)));
    }

    return newList;
}
