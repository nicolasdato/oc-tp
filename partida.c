#include "partida.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre)
{
    int i,j ;
    (*p) = malloc(sizeof(struct partida));
    if(*p == NULL){
        exit(PART_ERROR_MEMORIA);
    }
    (*p)->tablero = malloc(sizeof(struct tablero));
    if((*p)->tablero == NULL){
        exit(PART_ERROR_MEMORIA);
    }
    (*p)->modo_partida = modo_partida;
    if (comienza == PART_JUGADOR_RANDOM) {
        srand(time(NULL));
        if ((rand() % 2) == 0) {
            (*p)->turno_de = PART_JUGADOR_1;
        }
        else {
            (*p)->turno_de = PART_JUGADOR_2;
        }
    }
    else {
        (*p)->turno_de = comienza;
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            (*p)->tablero->grilla[i][j] = 0;
        }
    }
    (*p)->estado = PART_EN_JUEGO;
    strcpy((*p)->nombre_jugador_1, j1_nombre);
    strcpy((*p)->nombre_jugador_2, j2_nombre);
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y)
{
    int **grilla;
    int i, j;
    int gano;
    int no_hay_empate = 0;

    if(p->tablero->grilla[mov_x][mov_y] != 0){
        return PART_MOVIMIENTO_ERROR;
    }
    else
    {
        if(p->turno_de == PART_JUGADOR_1) {
            p->tablero->grilla[mov_x][mov_y] = 1;
            p->turno_de = PART_JUGADOR_2;
        }
        else{
            p->tablero->grilla[mov_x][mov_y] = 2;
            p->turno_de = PART_JUGADOR_1;
        }
        grilla = p->tablero->grilla;
        gano = 0;
        if(mov_x != 1 && mov_y !=1){
            if(grilla[1][1] == grilla [mov_x][mov_y] && grilla[1][1] == grilla[fabs(mov_x-2)][fabs(mov_y-2)]){
                gano = grilla[1][1];
            }
            else{
                if(grilla[mov_x][mov_y] == grilla[(mov_x-1) %3][mov_y] && grilla[mov_x][mov_y] == grilla[(mov_x-2) %3][mov_y]){
                    gano = grilla[mov_x][mov_y];
                }
                else{
                    if(grilla[mov_x][mov_y] == grilla[mov_x][(mov_y-1) % 3] && grilla[mov_x][mov_y] == grilla[mov_x][(mov_y-1) % 3]){
                        gano = grilla[mov_x][mov_y];
                    }
                }
            }
        }
        else{
            if(grilla[mov_x][mov_y] == grilla[(mov_x-1)][mov_y] && grilla[mov_x][mov_y] == grilla[(mov_x+1)][mov_y]){
                gano = grilla[mov_x][mov_y];
            }
            else{
                if(grilla[mov_x][mov_y] == grilla[mov_x][(mov_y-1)] && grilla[mov_x][mov_y] == grilla[mov_x][(mov_y+1)]){
                    gano = grilla[mov_x][mov_y];
                }
                else{
                    if(grilla[mov_x][mov_y] == grilla[0][0] && grilla[mov_x][mov_y] == grilla[2][2]){
                        gano = grilla[mov_x][mov_y];
                    }
                    else{
                        if(grilla[mov_x][mov_y] == grilla[2][0] && grilla[mov_x][mov_y] == grilla[0][2]){
                            gano = grilla[mov_x][mov_y];
                        }
                    }
                }
            }
        }
        /*for (i = 0; i < 3; i++){
            if(grilla[i][0] == grilla[i][1] && grilla[i][1] == grilla[i][2]){
                gano = grilla[i][0];
            }
        }
        for (i = 0; !gano && i < 3; i++){
            if(grilla[0][i] == grilla[1][i] && grilla[1][i] == grilla[2][i]){
                gano = grilla[0][i];
            }
        }
        if(grilla[0][0] == grilla[1][1] && grilla[1][1] == grilla[2][2]){
            gano = grilla[0][0];
        }
        if(grilla[0][2] == grilla[1][1] && grilla[1][1] == grilla[2][0]){
            gano = grilla[0][2];
        }*/
        if(gano == 1){
            p->estado = PART_GANA_JUGADOR_1;
        }
        else if(gano == 2){
            p->estado = PART_GANA_JUGADOR_2;
        }
        else {
            for(i = 0; i < 3 && no_hay_empate == 0; i++){
                for(j = 0; j < 3; j++){
                    if(grilla[i][j] == 0) {
                        no_hay_empate = 1;
                        break;
                    }
                }
            }
            if (no_hay_empate == 0) {
                p->estado = PART_EMPATE;
            }
        }
    }

    return PART_MOVIMIENTO_OK;
}

void finalizar_partida(tPartida * p){
    free((*p)->tablero);
    free(*p);
}
