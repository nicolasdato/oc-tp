#include <stdlib.h>

#include "lista.h"
#include "arbol.h"
#include "ia.h"

// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);

void no_eliminar_ia(tElemento elemento)
{
}

void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la búsqueda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representarán a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un árbol para la búsqueda adversaria inicialmente vacío.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la raíz del árbol de búsqueda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}


void proximo_movimiento(tBusquedaAdversaria b, int resultado_esperado, int * x, int * y){
    tEstado raiz = a_recuperar(b->arbol_busqueda,a_raiz(b->arbol_busqueda));
    tEstado actual;
    int encontre = 0;
    resultado_esperado = raiz->utilidad;
    tLista hijos = a_hijos(b->arbol_busqueda,a_raiz(b->arbol_busqueda));
    tPosicion pos = l_primera(hijos);
    tPosicion posFin = l_fin(hijos);

    while(pos != posFin && encontre == 0){
        actual = l_recuperar(hijos,pos);
        if(actual->utilidad == resultado_esperado){
            encontre = 1;
        }
    }
    diferencia_estados(raiz,actual, x, y);
}

void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    a_destruir(&(*b)->arbol_busqueda, free);
    free(*b);
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
estado inicial el estado de la partida almacenado en el árbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;

    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al árbol de búsqueda adversaria.
- N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
- ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){
    tEstado estado;
    tEstado estadoHijo;
    tLista sucesores;
    int mejor_valor_sucesores;
    tPosicion posFin;
    tNodo nodo;
    tLista hijos;
    tPosicion hijo;
    tPosicion hijoFin;

    estado = a_recuperar(a,n);
    if(!(estado->utilidad == IA_EMPATA_MAX || estado->utilidad == IA_GANA_MAX || estado->utilidad == IA_PIERDE_MAX)){
        if(es_max == 1){
            mejor_valor_sucesores = IA_INFINITO_NEG;
            sucesores = estados_sucesores(estado, jugador_max);
            posFin = l_fin(sucesores);
            while(l_primera(sucesores) != posFin){
                nodo = a_insertar(a, n, NULL, l_recuperar(sucesores, l_primera(sucesores)));
                crear_sucesores_min_max(a, nodo, 0, alpha, beta, jugador_max, jugador_min);
                l_eliminar(sucesores, l_primera(sucesores),no_eliminar_ia);
                hijos = a_hijos(a, nodo);
                hijo = l_primera(hijos);
                hijoFin = l_fin(hijos);
                while(hijo != hijoFin){
                    estadoHijo = l_recuperar(hijos, hijo);
                    if(estadoHijo->utilidad > mejor_valor_sucesores){
                        mejor_valor_sucesores = estadoHijo->utilidad;
                    }
                }
                estado->utilidad = mejor_valor_sucesores;
            }
            l_destruir(&sucesores, no_eliminar_ia);
        }
        else{
            mejor_valor_sucesores = IA_INFINITO_POS;
            sucesores = estados_sucesores(estado, jugador_min);
            posFin = l_fin(sucesores);
            while(l_primera(sucesores) != posFin){
                nodo = a_insertar(a, n, NULL, l_recuperar(sucesores, l_primera(sucesores)));
                crear_sucesores_min_max(a, nodo, 1, alpha, beta, jugador_max, jugador_min);
                l_eliminar(sucesores, l_primera(sucesores), no_eliminar_ia);
                hijos = a_hijos(a, nodo);
                hijo = l_primera(hijos);
                hijoFin = l_fin(hijos);
                while(hijo != hijoFin){
                    estadoHijo = l_recuperar(hijos, hijo);
                    if(estadoHijo->utilidad < mejor_valor_sucesores){
                        mejor_valor_sucesores = estadoHijo->utilidad;
                    }
                }
                estado->utilidad = mejor_valor_sucesores;
            }
            l_destruir(&sucesores, no_eliminar_ia);
        }
    }
}

/**
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX ganó la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empató la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdió la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max)
{
    int i;
    int hay_vacios = 0;
    int gano = 0;

    for (i = 0; i < 3 && gano == 0; i++){
        if(e->grilla[i][0] == e->grilla[i][1] && e->grilla[i][1] == e->grilla[i][2]){
            gano = e->grilla[i][0];
        }
        if(e->grilla[i][0] == 0 || e->grilla[i][1] == 0 || e->grilla[i][2] == 0){
            hay_vacios = 1;
        }
    }
    for (i = 0; !gano && i < 3; i++){
        if(e->grilla[0][i] == e->grilla[1][i] && e->grilla[1][i] == e->grilla[2][i]){
            gano = e->grilla[0][i];
        }
    }
    if(!gano && e->grilla[0][0] == e->grilla[1][1] && e->grilla[1][1] == e->grilla[2][2]){
        gano = e->grilla[0][0];
    }
    if(!gano && e->grilla[0][2] == e->grilla[1][1] && e->grilla[1][1] == e->grilla[2][0]){
        gano = e->grilla[0][2];
    }

    if(gano == jugador_max){
        return IA_GANA_MAX;
    }
    else if(gano != 0){
        return IA_PIERDE_MAX;
    }
    if(!hay_vacios){
        return IA_EMPATA_MAX;
    }
    return IA_NO_TERMINO;
}

/**
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonación del estado E, junto con la incorporación de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){
    int i, j;
    tEstado eNuevo;
    tLista lista;

    crear_lista(&lista);
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if (e->grilla[i][j] == 0) {
                eNuevo = clonar_estado(e);
                eNuevo->grilla[i][j] = ficha_jugador;
                eNuevo->utilidad = valor_utilidad(eNuevo, ficha_jugador);
                l_insertar(lista, l_primera(lista), eNuevo);
            }
        }
    }

    return lista;
}

/**
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    tEstado toReturn;
    int i,j;

    toReturn = malloc(sizeof(struct estado));
    if(toReturn == NULL){
        exit(IA_ERROR_MEMORIA);
    }
    toReturn->utilidad = e->utilidad;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            toReturn->grilla[i][j] = e->grilla[i][j];
        }
    }
    return toReturn;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}
