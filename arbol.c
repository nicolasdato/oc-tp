#include "arbol.h"
#include <stdlib.h>

void no_eliminar(tElemento elemento)
{
}

void n_eliminar(tNodo n, void (*fEliminar)(tElemento))
{
    tPosicion pos;
    tPosicion posFin;
    struct nodo *nodo;

    n->padre = NULL;
    fEliminar(n->elemento);
    pos = l_primera(n->hijos);
    posFin = l_fin(n->hijos);
    while (pos != posFin) {
        nodo = l_recuperar(n->hijos, pos);
        n_eliminar(nodo, fEliminar);
        pos = l_siguiente(n->hijos, pos);
    }
    l_destruir(&(n->hijos), free);
}

void crear_arbol(tArbol * a){
    (*a) = malloc(sizeof(struct arbol));
    if((*a) == NULL){
        exit(ARB_ERROR_MEMORIA);
    }
    (*a)->raiz = NULL;
}

void crear_raiz(tArbol a, tElemento e){
    if(a->raiz != NULL)
        exit(ARB_OPERACION_INVALIDA);
    a->raiz = malloc(sizeof(struct nodo));
    if(a->raiz == NULL){
        exit(ARB_ERROR_MEMORIA);
    }
    a->raiz->elemento = e;
    a->raiz->padre = NULL;
    crear_lista(&(a->raiz->hijos));
}

tNodo a_raiz(tArbol a){
    if(a->raiz == NULL)
        exit(ARB_OPERACION_INVALIDA);
    return a->raiz;
}

tLista a_hijos(tArbol a, tNodo n){
    return n->hijos;
}

tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    struct nodo *nodo;
    tPosicion pos;
    tPosicion posFin;

    if (np == NULL)
        exit(ARB_OPERACION_INVALIDA);

    nodo = malloc(sizeof(struct nodo));
    if(nodo == NULL){
        exit(ARB_ERROR_MEMORIA);
    }
    nodo->padre = np;

    if (nh == NULL){
        crear_lista(&(nodo->hijos));
        nodo->elemento = e;
        l_insertar(np->hijos,l_fin(np->hijos),nodo);
    }
    else {
        pos = l_primera(np->hijos);
        posFin = l_fin(np->hijos);
        while(pos != posFin && nh != l_recuperar(np->hijos, pos)){
            pos = l_siguiente(np->hijos, pos);
        }
        if (pos == posFin) {
            free(nodo);
            exit(ARB_POSICION_INVALIDA);
        }
        crear_lista(&(nodo->hijos));
        nodo->elemento = e;
        l_insertar(np->hijos, pos, nodo);
    }
    return nodo;
}

void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    tPosicion pos;
    tPosicion posFin;
    tPosicion posPadre;
    tPosicion posFinPadre;
    struct nodo *padre;
    struct nodo *hijo;
    if(n == a->raiz){
        pos = l_primera(n->hijos);
        posFin = l_fin(n->hijos);
        if(pos == posFin){
            a->raiz = NULL;
        }
        else{
            if (l_siguiente(n->hijos,pos) == posFin){
                a->raiz = l_recuperar(n->hijos, pos);
                a->raiz->padre = NULL;
            }
            else
                exit(ARB_OPERACION_INVALIDA);
        }
    }
    else{
        padre = n->padre;
        posPadre = l_primera(padre->hijos);
        posFinPadre = l_fin(padre->hijos);
        pos = l_primera(n->hijos);
        posFin = l_fin(n->hijos);
        if(pos == posFin){
            while (posPadre != posFinPadre) {
                if(n == l_recuperar(padre->hijos, posPadre)){
                    l_eliminar(padre->hijos, posPadre, no_eliminar);
                    break;
                }
                posPadre = l_siguiente(padre->hijos, posPadre);
            }
        }
        else {
           while (posPadre != posFinPadre) {
                if(n == l_recuperar(padre->hijos, posPadre)){
                    while (pos != posFin) {
                        hijo = l_recuperar(n->hijos, pos);
                        hijo->padre = padre;
                        l_insertar(padre->hijos, posPadre, hijo);
                        pos = l_siguiente(n->hijos, pos);
                        posPadre = l_siguiente(padre->hijos, posPadre);
                    }
                    l_eliminar(padre->hijos, posPadre, no_eliminar);
                    break;
                }
                posPadre = l_siguiente(padre->hijos, posPadre);
            }
        }
    }
    l_destruir(&(n->hijos), no_eliminar);
    fEliminar(n->elemento);
    free(n);
}

void a_destruir(tArbol * a, void (*fEliminar)(tElemento))
{
    struct nodo *nodo;

    if((*a)->raiz != NULL){
        nodo = (*a)->raiz;
        n_eliminar(nodo,fEliminar);
        free(nodo);
    }
    free(*a);
}

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa)
{
    struct nodo *padre;
    tPosicion pos;
    tPosicion posFin;

    crear_arbol(sa);
    (*sa)->raiz = n;
    if (n->padre != NULL){
        padre = n->padre;
        n->padre = NULL;
        pos = l_primera(padre->hijos);
        posFin = l_fin(padre->hijos);
        while (pos != posFin) {
            if(n == l_recuperar(padre->hijos, pos)){
                l_eliminar(padre->hijos, pos, no_eliminar);
                break;
            }
            pos = l_siguiente(padre->hijos, pos);
        }
    }
    else{
        a->raiz = NULL;
    }
}
