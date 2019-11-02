#include "partida.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre)
{
    int i,j ;
    (*p) = malloc(sizeof(struct partida));          //Se reserva espacio en memoria para la partida
    if(*p == NULL){                                 //En caso de que no se pueda se produce un error en la memoria
        exit(PART_ERROR_MEMORIA);
    }
    (*p)->tablero = malloc(sizeof(struct tablero)); //Se reserva espacio en memoria para el tablero
    if((*p)->tablero == NULL){                      //En caso de que no se pueda se produce un error en la memoria
        exit(PART_ERROR_MEMORIA);
    }
    (*p)->modo_partida = modo_partida;
    if (comienza == PART_JUGADOR_RANDOM) {          //En caso de comensar un jugador ramdom
        srand(time(NULL));
        if ((rand() % 2) == 0) {                    //Se genera un numero aleatorio si es par empiesa jugador 1 haciendo uso de la libreria time.h
            (*p)->turno_de = PART_JUGADOR_1;
        }
        else {                                      //Caso contrario empieza jugador 2
            (*p)->turno_de = PART_JUGADOR_2;
        }
    }
    else {                                          //Caso contrario empieza el jugador elejido por el usuario
        (*p)->turno_de = comienza;
    }
    for(i = 0; i < 3; i++){                         //Se iniciliza el tablero con todas sus posiciones en 0
        for(j = 0; j < 3; j++){
            (*p)->tablero->grilla[i][j] = 0;
        }
    }
    (*p)->estado = PART_EN_JUEGO;
    strcpy((*p)->nombre_jugador_1, j1_nombre);      //Se hace uso de una funcion de la liberia string.h para copiar los nombres
    strcpy((*p)->nombre_jugador_2, j2_nombre);
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y)
{
    int grilla[3][3];
    int i, j;
    int gano;
    int no_hay_empate = 0;

    if(p->tablero->grilla[mov_x][mov_y] != 0){      //Si la ficha ya esta ocupada se produce un error
        return PART_MOVIMIENTO_ERROR;
    }
    else                                            //Caso contrario
    {
        if(p->turno_de == PART_JUGADOR_1) {         //Si es el turno del jugador 1 realiza su movimiento y se cambia el turno
            p->tablero->grilla[mov_x][mov_y] = 1;
            p->turno_de = PART_JUGADOR_2;
        }
        else{                                       //Caso contrario, si es el turno del jugador 2 realiza su movimiento y se cambia el turno
            p->tablero->grilla[mov_x][mov_y] = 2;
            p->turno_de = PART_JUGADOR_1;
        }
        memcpy(grilla, p->tablero->grilla, sizeof(grilla)); //Se hace uso de una funcion de la libreria string.h para copiar el tablero
        gano = 0;                                           //Variable auxiliar usado para guardar la ficha en caso de que alguien gane
        for (i = 0; i < 3; i++){                                                //Se recorre el tablero horisontalmente
            if(grilla[i][0] == grilla[i][1] && grilla[i][1] == grilla[i][2]){
                gano = grilla[i][0];
            }
        }
        for (i = 0; !gano && i < 3; i++){                                       //Se recorre el tablero verticalmente
            if(grilla[0][i] == grilla[1][i] && grilla[1][i] == grilla[2][i]){
                gano = grilla[0][i];
            }
        }
        if(grilla[0][0] == grilla[1][1] && grilla[1][1] == grilla[2][2]){       //Se recorre una diagonal
            gano = grilla[0][0];
        }
        if(grilla[0][2] == grilla[1][1] && grilla[1][1] == grilla[2][0]){       //Se recorre la otra diagonal
            gano = grilla[0][2];
        }
        if(gano == 1){
            p->estado = PART_GANA_JUGADOR_1;
        }
        else if(gano == 2){
            p->estado = PART_GANA_JUGADOR_2;
        }
        else {
            for(i = 0; i < 3 && no_hay_empate == 0; i++){           //Se recorre la grilla buscando si todavia hay lugares vacios
                for(j = 0; j < 3; j++){
                    if(grilla[i][j] == 0) {
                        no_hay_empate = 1;
                        break;
                    }
                }
            }
            if (no_hay_empate == 0) {       //En caso de que no halla, hay un empate
                p->estado = PART_EMPATE;
            }
        }
    }

    return PART_MOVIMIENTO_OK;
}

void finalizar_partida(tPartida * p){
    free((*p)->tablero);                    //Se libera el espacio en memoria asignado al tablero
    free(*p);                               //Se libera el espacio en memoria asginado a la partida
}
