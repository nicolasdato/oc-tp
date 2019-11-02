#include <stdlib.h>
#include "lista.h"

//Lista simplemente enlazada con posicion indirecta y puntero a un nodo centinela

void crear_lista(tLista * l)
{
    (*l) = malloc(sizeof(struct celda)); // Se reserva espacio en memoria para la lista con su primer elemento, centinela
    (*l)->elemento = NULL;               // El primer elemento en NULL, el cual seria el del nodo centinela
    (*l)->siguiente = NULL;
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e)
{
    struct celda *celda = malloc(sizeof(struct celda)); // Se reserva espacio para el nodo en el cual se guardara el elemento
    celda->elemento = e;
    celda->siguiente = p->siguiente;                     // El siguiente de la celda es el siguiente a la posicion al estar trabajando con posicion indirecta
    p->siguiente = celda;
}

/**
 Elimina el nodo que se encuentra en la posición P de L.
 El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento))
{
    struct celda *aux;
    if(p->siguiente == NULL)                    //En caso de que la posicion == fin
        exit(LST_POSICION_INVALIDA);
    fEliminar((p->siguiente)->elemento);        //Se elimina el elemento con la funcion pasada por parametro
    aux = p->siguiente;                         //Se apunta al nodo para asi despues eliminarlo
    p->siguiente = p->siguiente->siguiente;     //El nodo anterior apunta al nodo siguiente al actual
    free(aux);                                  //Se libera la celda de la memoria
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados mediante la función fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento))
{
    struct celda *aux;
    while((*l)->siguiente != NULL){             //Mientas existan celdas
        aux = (*l)->siguiente;                  //Apunto al siguiente de la lista
        fEliminar(aux->elemento);               //Se elimina el elemento con la funcion pasada por parametro
        (*l)->siguiente = aux->siguiente;       //Se cambia los siguientes
        free(aux);                              //Y se lo elemina de la memoria
    }
    free(*l);                                   //Por ultimo se elimina el espacio en memoria reservado para la lista
}

 /**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p)
{
    if(p->siguiente == NULL)                //En caso de que la posicion == fin
        exit(LST_POSICION_INVALIDA);
    return p->siguiente->elemento;          //Al estar en posicion indirecta se retorna el elemento del nodo siguiente a la posicion
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l)
{
    return l;  //La primera posicion es a la que apunta la lista
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p)
{
        if(p->siguiente == NULL)                //En caso de que posicion == fin
            exit(LST_NO_EXISTE_SIGUIENTE);
        return p->siguiente;                    //Se retorna la posicion siguiente
}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p)
{
    struct celda *auxiliar = l;

    if(p == l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);
    while (auxiliar->siguiente != p) {
        auxiliar = auxiliar->siguiente;
    }
    return auxiliar;
}


 /**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l)
{
    struct celda *auxiliar = l;
    if(l->siguiente == NULL)                                //Si noy hay siguiente se retorna la lista, es decir, no hay elementos
        return l;
    while ((auxiliar->siguiente)->siguiente != NULL) {      //Mientas que existan siguientas avanzo hasta la ultima posicion
        auxiliar = auxiliar->siguiente;
    }
    return auxiliar;
}

 /**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l)
{
    struct celda *auxiliar = l;

    while (auxiliar->siguiente != NULL) {       //Si noy hay siguiente se retorna la lista, es decir, no hay elementos
        auxiliar = auxiliar->siguiente;
    }
    return auxiliar;
}

/**
 Retorna la longitud actual de la lista.
**/
int l_longitud(tLista l)
{
    if(l->siguiente == NULL) {              //Si no puedo seguir avansando 0
        return 0;
    }
    return 1 + l_longitud(l->siguiente);    //Si pude avansar 1 + la longitud de la lista menos la posocion actual
}
