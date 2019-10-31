#include <stdio.h>
#include <stdlib.h>
#include "ia.h"

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
    int opcion = 1, modo, turno, x, y;
    char nombre_1[1000], nombre_2[1000];
    tPartida partida;
    tBusquedaAdversaria busqueda;

    while(opcion == 1){
        printf("bienvenido, presione 1- si desea jugar, 2- si de desea salir\n");
        scanf("%d",&opcion);
        if(opcion == 1){
            printf("1-Modo jugador vs jugador\n");
            printf("2-Modo jugador vs computadora\n");
            printf("3-Modo computadora vs computadora\n");
            scanf("%d",&modo);
            printf("Que jugador desea que empiece primero\n");
            printf("1-Jugador 1\n");
            printf("2-Jugador 2\n");
            printf("3-Jugador aleatorio\n");
            scanf("%d",&turno);
            if(modo == 1){
                modo = PART_MODO_USUARIO_VS_USUARIO;
            }
            else{
                if(modo == 2){
                    modo = PART_MODO_USUARIO_VS_AGENTE_IA;
                }
                else{
                    modo = PART_MODO_AGENTE_IA_VS_AGENTE_IA;
                }
            }
            if(turno == 1){
                turno = PART_JUGADOR_1;
            }
            else{
                if(turno == 2){
                    turno = PART_JUGADOR_2;
                }
                else{
                    turno = PART_JUGADOR_RANDOM;
                }
            }
            printf("Ingrese el nombre del jugador 1, sin espacios: ");
            scanf("%s", nombre_1);
            printf("Ingrese el nombre del jugador 2, sin espacios: ");
            scanf("%s", nombre_2);
            nueva_partida(&partida, modo, turno, nombre_1, nombre_2);
            dibujar_tablero(partida->tablero);
            while(partida->estado == PART_EN_JUEGO){
                if(partida->turno_de == PART_JUGADOR_1){
                    printf("Es el turno de %s\n", partida->nombre_jugador_1);
                }
                else{
                     printf("Es el turno de %s\n", partida->nombre_jugador_2);
                }
                if((partida->turno_de == PART_JUGADOR_1 && modo != PART_MODO_AGENTE_IA_VS_AGENTE_IA) || (partida->turno_de == PART_JUGADOR_2 && modo == PART_MODO_USUARIO_VS_USUARIO)){
                    x = -1;
                    y = -1;
                    while(x < 0 || x > 2 || y < 0 || y > 2){
                        printf("Ingrese las coordenadas separadas por coma (arrancando en 0): ");
                        scanf("%d,%d", &x, &y);
                    }
                }
                else{
                    crear_busqueda_adversaria(&busqueda, partida);
                    proximo_movimiento(busqueda, IA_GANA_MAX, &x, &y);
                    destruir_busqueda_adversaria(&busqueda);
                    printf("La IA pone ficha en %d,%d\n", x, y);
                }
                nuevo_movimiento(partida, x, y);
                dibujar_tablero(partida->tablero);
            }
            switch(partida->estado){
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
    }
    return 0;
}
