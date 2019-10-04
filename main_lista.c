#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
    tLista lista;

    int opcion = 0, *ingresar;
    printf("Hola!\n");
    printf("Opciones:\n");

    while(opcion != 4){
        printf("1- crear lista\n");
        printf("2- agregar elemento\n");
        printf("3- imprimir por pantalla\n");
        printf("4- salir\n");
        scanf("%d",&opcion);
        if(opcion == 1){
             crear_lista(&lista);
        }
        else if(opcion == 2){
            printf("Ingrese un numero entero, igrese -1 cuando desee parar\n");
            while(opcion == 2){
                ingresar = (int *)malloc(sizeof(int));
                scanf("%d", ingresar);
                if(*ingresar != -1) {
                    l_insertar(lista, l_primera(lista), ingresar);
                }
                else
                    opcion = 0;
            }
        }
        else if(opcion == 3){
            tPosicion pos = l_primera(lista);
            while(pos != l_fin(lista)) {
                int *elemento = l_recuperar(lista, pos);
                printf("elemento: %d\n", *elemento);
                pos = l_siguiente(lista, pos);
            }
        }
    }
    l_destruir(&lista, free);
    return 0;
}

