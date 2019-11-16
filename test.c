#include "arbol.h"
#include <stdlib.h>
#include <stdio.h>

tElemento elemento(int i)
{
	tElemento e;
	e = malloc(sizeof(i));
	*(int *)e = i;
	return e;
}

void _preorder(tArbol arbol, tNodo nodo)
{
	int *e;
	tLista lista;
	tNodo n;
	tPosicion pos;
	int l;

	e = a_recuperar(arbol, nodo);
	printf("%d ", *e);
	lista = a_hijos(arbol, nodo);
	l = l_longitud(lista);
	pos = l_primera(lista);
	while (l > 0) {
		n = l_recuperar(lista, pos);
		_preorder(arbol, n);
		pos = l_siguiente(lista, pos);
		l--;
	}
}

void preorder(tArbol arbol)
{
	printf("[");
	_preorder(arbol, a_raiz(arbol));
	printf("]\n");
}

int main(int argc, char **argv)
{
	tArbol arbol;
	tNodo nodo3;
	tNodo nodo7;
	tNodo nodo9;
	tNodo nodo11;
	tNodo nodo12;
	tArbol subarbol;

	printf("Se crea arbol\n");
	crear_arbol(&arbol);
	printf("Se crea raiz\n");
	crear_raiz(arbol, elemento(1));
	preorder(arbol);
	printf("Se inserta 2\n");
	a_insertar(arbol, a_raiz(arbol), NULL, elemento(2));
	preorder(arbol);
	printf("Se inserta 3\n");
	nodo3 = a_insertar(arbol, a_raiz(arbol), NULL, elemento(3));
	preorder(arbol);
	printf("Se inserta 4\n");
	a_insertar(arbol, a_raiz(arbol), NULL, elemento(4));
	preorder(arbol);
	printf("Se inserta 5\n");
	a_insertar(arbol, a_raiz(arbol), NULL, elemento(5));
	preorder(arbol);
	printf("Se inserta 9\n");
	nodo9 = a_insertar(arbol, nodo3, NULL, elemento(9));
	preorder(arbol);
	printf("Se inserta 6\n");
	a_insertar(arbol, nodo3, nodo9, elemento(6));
	preorder(arbol);
	printf("Se inserta 7\n");
	nodo7 = a_insertar(arbol, nodo3, nodo9, elemento(7));
	preorder(arbol);
	printf("Se inserta 8\n");
	a_insertar(arbol, nodo3, nodo9, elemento(8));
	preorder(arbol);
	printf("Se inserta 10\n");
	a_insertar(arbol, nodo7, NULL, elemento(10));
	preorder(arbol);
	printf("Se inserta 11\n");
	nodo11 = a_insertar(arbol, nodo7, NULL, elemento(11));
	preorder(arbol);
	printf("Se inserta 12\n");
	nodo12 = a_insertar(arbol, nodo7, NULL, elemento(12));
	preorder(arbol);
	printf("Subarbol\n");
	a_sub_arbol(arbol, nodo7, &subarbol);
	preorder(arbol);
	preorder(subarbol);
	printf("Se elimina 3\n");
	a_eliminar(arbol, nodo3, free);
	preorder(arbol);
	printf("Se elimina 11\n");
	a_eliminar(subarbol, nodo11, free);
	preorder(subarbol);
	printf("Se elimina 12\n");
	a_eliminar(subarbol, nodo12, free);
	preorder(subarbol);
	printf("Se elimina raiz\n");
	a_eliminar(subarbol, a_raiz(subarbol), free);
	preorder(subarbol);
	printf("Se destruye arbol\n");
	a_destruir(&arbol, free);
	printf("Se destruye subarbol\n");
	a_destruir(&subarbol, free);

	return 0;
}

