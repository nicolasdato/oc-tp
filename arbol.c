#include "arbol.h"
#include <stdlib.h>

void no_eliminar(tElemento elemento) //Metodo auxiliar en caso de eliminar una mista de hijos de un nodo pero no eliminrarlo de la memoria o perderlos
{
}

void n_eliminar(tNodo n, void (*fEliminar)(tElemento))
{
    tPosicion pos;
    tPosicion posFin;
    struct nodo *nodo;

    n->padre = NULL;
    fEliminar(n->elemento);                 //Elimino el elemento del nodo con la funcion pasada por parametro
    pos = l_primera(n->hijos);
    posFin = l_fin(n->hijos);
    while (pos != posFin) {                 //Recorro la lista de hijos del nodo
        nodo = l_recuperar(n->hijos, pos);
        n_eliminar(nodo, fEliminar);        //LLamo con cada hijo a n_eliminar
        pos = l_siguiente(n->hijos, pos);
    }
    l_destruir(&(n->hijos), free);          //Elimino la lista de hijos del nodo, liberando de momoria con free todos los nodos en la lista
}

void crear_arbol(tArbol * a){
    (*a) = malloc(sizeof(struct arbol));    //Se le asigna espacio en memoria para el arbol
    if((*a) == NULL){                       //En caso de que no exista mas memoria para su creacion
        exit(ARB_ERROR_MEMORIA);
    }
    (*a)->raiz = NULL;                      //En su creacion la raiz del arbol sera NULL
}

void crear_raiz(tArbol a, tElemento e){
    if(a->raiz != NULL)                     //No se le puede asignar una raiz a un arbol que ya tiene una
        exit(ARB_OPERACION_INVALIDA);
    a->raiz = malloc(sizeof(struct nodo));  //Se le asigna espacio en memoria para la raiz
    if(a->raiz == NULL){                    //En caso de que no exista mas memoria para su creacion
        exit(ARB_ERROR_MEMORIA);
    }
    a->raiz->elemento = e;                  //Se guarda el elemento de la raiz
    a->raiz->padre = NULL;                  //La raiz no tendra un padre
    crear_lista(&(a->raiz->hijos));         //Se crea una lista vacia para sus hijos
}

tNodo a_raiz(tArbol a){
    if(a->raiz == NULL)                     //Si no existe una raiz se produce un error
        exit(ARB_OPERACION_INVALIDA);
    return a->raiz;                         //Se retorna la raiz del arbol
}

tLista a_hijos(tArbol a, tNodo n){
    return n->hijos;                        //Se retorna la lista con los hijos del nodo
}

tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;                     //Se retorna el elemento del nodo
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    struct nodo *nodo;
    tPosicion pos;
    tPosicion posFin;

    if (np == NULL)                                     //El nodo a insertar no puede no tener padre
        exit(ARB_OPERACION_INVALIDA);

    nodo = malloc(sizeof(struct nodo));                //Se reserva espacio en memoria para el nodo
    if(nodo == NULL){                                  //En caso de que no exista mas memoria para su creacion
        exit(ARB_ERROR_MEMORIA);
    }
    nodo->padre = np;                                  //Se le asigna el nodo padre

    if (nh == NULL){                                    //Si no se paso un hermano derecho
        crear_lista(&(nodo->hijos));                    //Se crea una lista vacia para los hijos
        nodo->elemento = e;                             //Se almacena el elemento
        l_insertar(np->hijos,l_fin(np->hijos),nodo);    //Y se lo ingresa al final de la lista de hijos del padre
    }
    else {
        pos = l_primera(np->hijos);
        posFin = l_fin(np->hijos);
        while(pos != posFin && nh != l_recuperar(np->hijos, pos)){      //Se busca al hermano derecho en la lista de hijos del padre
            pos = l_siguiente(np->hijos, pos);
        }
        if (pos == posFin) {                    //En caso de no encontrarlo
            free(nodo);                         //Se libera la memoria que se le habia reservado al nodo
            exit(ARB_POSICION_INVALIDA);        //Y se produce un error al haber pasado un nodo hermano que no estaba contenido en la lista de hijos del padre
        }
        crear_lista(&(nodo->hijos));            //Se crea una lista vacia para los hijos del nodo
        nodo->elemento = e;                     //Se guarda el elemento
        l_insertar(np->hijos, pos, nodo);       //Y se le guarda en la lista de hijos del padre a la izquierda de el nodo que sera su hermano derecho
    }
    return nodo;                                //Se retorna el nodo ingresado
}

void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    tPosicion pos;
    tPosicion posFin;
    tPosicion posPadre;
    tPosicion posFinPadre;
    struct nodo *padre;
    struct nodo *hijo;
    if(n == a->raiz){                                       //En caso de querer eliminar la raiz
        pos = l_primera(n->hijos);
        posFin = l_fin(n->hijos);
        if(pos == posFin){                                  //Si la raiz es NULL el arbol deja de apuntarla
            a->raiz = NULL;
        }
        else{
            if (l_siguiente(n->hijos,pos) == posFin){       //En caso de que tenga un solo hijo
                a->raiz = l_recuperar(n->hijos, pos);       //Se remplaza los nodos
                a->raiz->padre = NULL;                      //Y deja de tener un padre la nueva raiz
            }
            else
                exit(ARB_OPERACION_INVALIDA);               //En caso de tener mas de un hijo se produce un error debido a que no puede ser eliminada
        }
    }
    else{                                                   //En caso de no ser la raiz
        padre = n->padre;
        posPadre = l_primera(padre->hijos);
        posFinPadre = l_fin(padre->hijos);
        pos = l_primera(n->hijos);
        posFin = l_fin(n->hijos);
        if(pos == posFin){                                              //Si no tiene hijos
            while (posPadre != posFinPadre) {                           //Lo busco en la lista de hijos del padre
                if(n == l_recuperar(padre->hijos, posPadre)){
                    l_eliminar(padre->hijos, posPadre, no_eliminar);    //Una ves encontrado es eliminado
                    break;
                }
                posPadre = l_siguiente(padre->hijos, posPadre);
            }
        }
        else {                                                          //En caso de tener uno o mas hijos
           while (posPadre != posFinPadre) {                            //Recorro la lista de hijos del padre
                if(n == l_recuperar(padre->hijos, posPadre)){           //Si lo encuentro
                    while (pos != posFin) {                             //Recorro la lista de hijos y los inserto en la lista de hijos del padre al nodo a eliminar
                        hijo = l_recuperar(n->hijos, pos);
                        hijo->padre = padre;
                        l_insertar(padre->hijos, posPadre, hijo);
                        pos = l_siguiente(n->hijos, pos);
                        posPadre = l_siguiente(padre->hijos, posPadre);
                    }
                    l_eliminar(padre->hijos, posPadre, no_eliminar);    //Voy eliminando de la lista de hijos del nodo los hijos sin eliminarlos de la memoria
                    break;
                }
                posPadre = l_siguiente(padre->hijos, posPadre);
            }
        }
    }
    l_destruir(&(n->hijos), free);                               //Una ves terminado borra de la memoria la lista de los hijos del nodo
    fEliminar(n->elemento);                                      //Elimino su elememnto con la funcion pasada por parametro
    free(n);                                                     //Elimino de la memoria el espacio asignado al nodo
}

void a_destruir(tArbol * a, void (*fEliminar)(tElemento))
{
    struct nodo *nodo;

    if((*a)->raiz != NULL){         //Si tiene una raiz
        nodo = (*a)->raiz;
        n_eliminar(nodo,fEliminar); //Llamo a un metodo auxiliar con el nodo en la raiz
        free(nodo);                 //Elimino de la memoria el espacio asignado al nodo
    }
    free(*a);                       //Elimino de la memoria el espacio asignado al nodo
}

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa)
{
    struct nodo *padre;
    tPosicion pos;
    tPosicion posFin;

    crear_arbol(sa);                                        //Se crea el arbol a retornar
    (*sa)->raiz = n;                                        //Se le asigna como raiz el nodo pasado por parametro
    if (n->padre != NULL){                                  //Si no es la raiz
        padre = n->padre;
        n->padre = NULL;                                    //Deja de tener raiz, ya que, es la raiz del subarbol
        pos = l_primera(padre->hijos);
        posFin = l_fin(padre->hijos);
        while (pos != posFin) {                             //Se recorre la lista de hijos de su padre para eliminarlo de esta
            if(n == l_recuperar(padre->hijos, pos)){        //Una ves encontrado y eliminado yo no se encuentra en el arbol
                l_eliminar(padre->hijos, pos, no_eliminar);
                break;
            }
            pos = l_siguiente(padre->hijos, pos);
        }
    }
    else{
        a->raiz = NULL;                                     //En caso de ser la raiz se le asigna NULL, es decir el arbol principal se queda son nodos
    }
}
