#include <stdio.h>
#include <stdlib.h>
#include "ia.h"

int main()
{
    int opcion = 1, modo, turno ;
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
        }
    }

    return 0;
}
