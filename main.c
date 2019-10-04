#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"


void mostrar_arbol(tArbol arbol, tNodo nodo)
{
    tLista lista;
    tPosicion pos, posFin;
    int *elemento;
    elemento = a_recuperar(arbol, nodo);
    printf("%d\n", *elemento);
    lista = a_hijos(arbol, nodo);
    pos = l_primera(lista);
    posFin = l_fin(lista);
    while(pos != posFin){

        pos = l_siguiente(lista, pos);
    }

}

int main()
{
    tArbol arbol;
    tNodo nodo, nodo2, nodo3;
    int *elemento;
        tLista lista;
    tPosicion pos, posFin;


    crear_arbol(&arbol);
    elemento = malloc(sizeof(int));
    *elemento = 1;
    crear_raiz(arbol, elemento);
    nodo = a_raiz(arbol);
    elemento = malloc(sizeof(int));
    *elemento = 2;
    a_insertar(arbol, nodo, NULL, elemento);
    elemento = malloc(sizeof(int));
    *elemento = 3;
    a_insertar(arbol, nodo, NULL, elemento);
    elemento = malloc(sizeof(int));
    *elemento = 5;
    nodo2 = a_insertar(arbol, nodo, NULL, elemento);
    elemento = malloc(sizeof(int));
    *elemento = 4;
    a_insertar(arbol, nodo, nodo2, elemento);
    elemento = malloc(sizeof(int));
    *elemento = 6;
    a_insertar(arbol, nodo2, NULL, elemento);
    elemento = malloc(sizeof(int));
    *elemento = 7;
    nodo3 = a_insertar(arbol, nodo2, NULL, elemento);
    elemento = malloc(sizeof(int));
    *elemento = 8;
    a_insertar(arbol, nodo2, NULL, elemento);

    //mostrar_arbol(arbol, raiz);


    printf("%d\n",*(int *)a_recuperar(arbol,a_raiz(arbol)));
    lista = a_hijos(arbol,a_raiz(arbol));
    pos = l_primera(lista);
    posFin = l_fin(lista);
    while(pos != posFin){
        printf("%d ",*(int *)a_recuperar(arbol,l_recuperar(lista,pos)));
        pos = l_siguiente(lista, pos);
    }
    printf("\n");
    lista = a_hijos(arbol,nodo2);
    pos = l_primera(lista);
    posFin = l_fin(lista);
    while(pos != posFin){
        printf("%d ",*(int *)a_recuperar(arbol,l_recuperar(lista,pos)));
        pos = l_siguiente(lista, pos);
    }
    a_eliminar(arbol,nodo2,free);
    printf("\n");
    printf("\n");
    printf("\n");

    printf("%d\n",*(int *)a_recuperar(arbol,a_raiz(arbol)));
    lista = a_hijos(arbol,a_raiz(arbol));
    pos = l_primera(lista);
    posFin = l_fin(lista);
    while(pos != posFin){
        printf("%d ",*(int *)a_recuperar(arbol,l_recuperar(lista,pos)));
        pos = l_siguiente(lista, pos);
    }
    /*printf("\n");
    lista = a_hijos(arbol,nodo2);
    pos = l_primera(lista);
    posFin = l_fin(lista);
    while(pos != posFin){
        printf("%d ",*(int *)a_recuperar(arbol,l_recuperar(lista,pos)));
        pos = l_siguiente(lista, pos);
    }*/
    a_destruir(&arbol, free);
    return 0;
}
