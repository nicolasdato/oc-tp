#include <stdlib.h>
#include "lista.h"

void crear_lista(tLista * l)
{
    (*l) = malloc(sizeof(struct celda));
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e)
{
    struct celda *celda = malloc(sizeof(struct celda));
    celda->elemento = e;
    celda->siguiente = p->siguiente;
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
    if(p->siguiente == NULL)
        exit(LST_POSICION_INVALIDA);
    fEliminar((p->siguiente)->elemento);
    aux = p->siguiente;
    p->siguiente = p->siguiente->siguiente;
    free(aux);
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados mediante la función fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento))
{
    struct celda *aux;
    while((*l)->siguiente != NULL){
        aux = (*l)->siguiente;
        fEliminar(aux->elemento);
        (*l)->siguiente = aux->siguiente;
        free(aux);
    }
    free(*l);
}

 /**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p)
{
    if(p->siguiente == NULL)
        exit(LST_POSICION_INVALIDA);
    return p->siguiente->elemento;
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l)
{
    return l;
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p)
{
        if(p->siguiente == NULL)
            exit(LST_NO_EXISTE_SIGUIENTE);
        return p->siguiente;
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
    if(l->siguiente == NULL)
        return l;
    while ((auxiliar->siguiente)->siguiente != NULL) {
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

    while (auxiliar->siguiente != NULL) {
        auxiliar = auxiliar->siguiente;
    }
    return auxiliar;
}

/**
 Retorna la longitud actual de la lista.
**/
int l_longitud(tLista l)
{
    if(l->siguiente == NULL) {
        return 0;
    }
    return 1 + l_longitud(l->siguiente);
}
