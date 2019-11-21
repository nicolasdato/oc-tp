#include <stdio.h>
#include <stdlib.h>
#include "ia.h"

/**
 Metodo auxiliar para la muestra del tablero por consola
**/
void dibujar_tablero(struct tablero *tablero)
{
    int i, j;
    char ficha;
    printf("\n\n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(tablero->grilla[i][j] == 1){
                ficha = 'X';
            }
            else if(tablero->grilla[i][j] == 2){
                ficha = 'O';
            }
            else{
                ficha = ' ';
            }
            if(j < 2){
                printf("%c|", ficha);
            }
            else{
                printf("%c\n", ficha);
            }
        }
        if(i < 2){
            printf("-----\n");
        }
    }
    printf("\n\n");
}

int main()
{
    int opcion = 1, modo, turno, x, y, ingreso = 0;
    char nombre_1[50], nombre_2[50];
    tPartida partida;
    tBusquedaAdversaria busqueda;
    while(opcion != 2){             //Aparece el menu con las opciones de juego
        printf("bienvenido, presione 1- si desea jugar, 2- si de desea salir\n");
        scanf("%d",&opcion);
        if(opcion == 1){
            while(ingreso < 2){
                ingreso = 0;
                printf("1-Modo jugador vs jugador\n");
                printf("2-Modo jugador vs computadora\n");
                printf("3-Modo computadora vs computadora\n");
                scanf("%d",&modo);
                printf("Que jugador desea que empiece primero\n");
                printf("1-Jugador 1\n");
                printf("2-Jugador 2\n");
                printf("3-Jugador aleatorio\n");
                scanf("%d",&turno);
                if(modo == 1){                              //Se guardan las opciones seleccionadas por el usuario
                    modo = PART_MODO_USUARIO_VS_USUARIO;
                    ingreso++;
                }
                else{
                    if(modo == 2){
                        modo = PART_MODO_USUARIO_VS_AGENTE_IA;
                        ingreso++;
                    }
                    else{
                        if(modo == 3){
                            modo = PART_MODO_AGENTE_IA_VS_AGENTE_IA;
                            ingreso++;
                        }
                        else{
                            printf("El modo ingresado no es valido\n");
                        }
                    }
                }
                if(turno == 1){
                    turno = PART_JUGADOR_1;
                    ingreso++;
                }
                else{
                    if(turno == 2){
                        turno = PART_JUGADOR_2;
                        ingreso++;
                    }
                    else{
                        if(turno == 3){
                            turno = PART_JUGADOR_RANDOM;
                            ingreso++;
                        }
                        else{
                            printf("El turno ingresado no es valido\n");
                        }
                    }
                }
            }
            ingreso = 0;
            printf("Ingrese el nombre del jugador 1, sin espacios: ");
            scanf("%s", nombre_1);
            printf("Ingrese el nombre del jugador 2, sin espacios: ");
            scanf("%s", nombre_2);
            nueva_partida(&partida, modo, turno, nombre_1, nombre_2);   //Se crea una nueva partida
            dibujar_tablero(partida->tablero);                          //Y se dibuja el tablero vacio
            while(partida->estado == PART_EN_JUEGO){                    //Mientras se este en juago
                if(partida->turno_de == PART_JUGADOR_1){
                    printf("Es el turno de %s\n", partida->nombre_jugador_1);
                }
                else{
                     printf("Es el turno de %s\n", partida->nombre_jugador_2);
                }
                if((partida->turno_de == PART_JUGADOR_1 && modo != PART_MODO_AGENTE_IA_VS_AGENTE_IA) || (partida->turno_de == PART_JUGADOR_2 && modo == PART_MODO_USUARIO_VS_USUARIO)){//En caso de que juega el usuario
                    x = -1;
                    y = -1;
                    while(x < 0 || x > 2 || y < 0 || y > 2){
                        printf("Ingrese las coordenadas separadas por coma (arrancando en 0): ");
                        scanf("%d,%d", &x, &y);
                    }
                }
                else{
                    system("PAUSE()");
                    crear_busqueda_adversaria(&busqueda, partida);      //Se crea la busqueda adversaria
                    proximo_movimiento(busqueda, IA_GANA_MAX, &x, &y);  //Se calcula el mejor movimiento para Max
                    destruir_busqueda_adversaria(&busqueda);            //Luego se destruye la busqueda
                    printf("La IA pone ficha en %d,%d\n", x, y);
                }
                nuevo_movimiento(partida, x, y);                        //Se realiza el nuevo movimiento
                dibujar_tablero(partida->tablero);  //Se dibuja el estado actual del tablero despues del movimiento
            }
            switch(partida->estado){    //Se analisa el estado de la partida
                case PART_EMPATE:
                    printf("Empate!\n");
                    break;
                case PART_GANA_JUGADOR_1:
                    printf("Gano el jugador %s!\n", partida->nombre_jugador_1);
                    break;
                case PART_GANA_JUGADOR_2:
                    printf("Gano el jugador %s!\n", partida->nombre_jugador_2);
                    break;
            }
            finalizar_partida(&partida);
        }
        else{
            if (opcion != 2){
                printf("Usted no a ingresado un numero valido, vuelva a ingresar su opcion\n");
            }
        }
    }
    return 0;
}
/*
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
*/
