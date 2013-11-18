#include <stdio.h>

/********************************/
/* DECLARACION DE LAS FUNCIONES */
/********************************/

//Inserta un nodo en la lista
struct nodo* insertarNodo(struct nodo *raiz, int objetive, int *variable, int factible);

/** 
    Estructura del nodo del arbol binario
    La estructura guardara el puntero a sus hijos,
    el valor que se le asigno, y la probabilidad 
    calculada.
**/
struct nodo 
{
    struct nodo *sgt;
    int objetivo;
    int *variables;  
    int candidata;
};

/***********************************/
/* IMPLEMENTACION DE LAS FUNCIONES */
/***********************************/

struct nodo* insertarNodo(struct nodo *raiz, int objetive, int *variable, int factible)
{
    if (raiz == NULL)
    {
        raiz = (struct nodo*) malloc(sizeof(struct nodo));
        raiz->objetivo = objetive;
        raiz->variables = variable;
        raiz->candidata = factible;
    }
    else
    {
        struct nodo *sgt = raiz->sgt;
        while(sgt != NULL)
        {
            sgt = sgt->sgt;
        }
        struct nodo *agregar;
        agregar->objetivo = objetive;
        agregar->variables = variable;
        agregar->candidata = factible;
        sgt->sgt = agregar;
    }
    return raiz;
}

void llenarCeros(struct nodo *raiz, int cantidadVariables)
{
    int *array = malloc(cantidadVariables * sizeof(int));
    int i;
    for (i = 0; i < cantidadVariables; i++)
    {
        array[i] = 0;
    }
    raiz->variables = array;
}