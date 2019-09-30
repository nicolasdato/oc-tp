#include "arbol.h"
#include <stdlib.h>

void crear_arbol(tArbol * a){
    (*a) = malloc(sizeof(struct arbol));
    (*a)->raiz = NULL;
}

void crear_raiz(tArbol a, tElemento e){
    if(a->raiz != NULL)
        exit(ARB_OPERACION_INVALIDA);
    a->raiz = malloc(sizeof(struct nodo));
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
        l_insertar(np->hijos, l_anterior(np->hijos, pos), nodo);
    }
    return nodo;
}

void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    tPosicion pos;
    tPosicion posFin;
    if(n == a->raiz){
        pos = l_primera(n->hijos);
        posFin = l_fin(n->hijos);
        if(pos == posFin){
            fEliminar(n->elemento);
            l_destruir(&(n->hijos),fEliminar();
            free(n);
        }
        else{
            if (l_siguiente(n->hijos,pos) == posFin){

            }
            else
                exit(ARB_POSICION_INVALIDA);

        }
    }

}
