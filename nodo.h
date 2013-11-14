#include <stdio.h>

/********************************/
/* DECLARACION DE LAS FUNCIONES */
/********************************/

//Inserta un nodo en la raiz de un arbol
struct nodo* insertar(struct nodo *raiz, int llave, float probabilidad);

/** 
    Estructura del nodo del arbol binario
    La estructura guardara el puntero a sus hijos,
    el valor que se le asigno, y la probabilidad 
    calculada.
**/
struct nodo 
{
    struct nodo *hijoIzquierdo;
    struct nodo *hijoDerecho;
    float valorZ;
    int variables[cantVariables];
};

/***********************************/
/* IMPLEMENTACION DE LAS FUNCIONES */
/***********************************/

struct nodo* insertar(struct nodo *raiz, int llave, float probabilidad)
{
    /*Si la raiz es nula inserta*/
    if(raiz == NULL)
    {
        raiz = (struct nodo*) malloc(sizeof(struct nodo));
        raiz->llave = llave;
        raiz->probabilidad = probabilidad;
        raiz->hijoIzquierdo = NULL;
        raiz->hijoDerecho = NULL;
    }
    else
    {
        /*Si existe un nodo y el valor es mayor que este va al lado derecho*/
        if (raiz->llave < llave)
         {
            raiz->hijoDerecho = insertar(raiz->hijoDerecho, llave, probabilidad);
         }
         /*En caso contrario (> o =), va al lado izquierdo*/
         else
         {
            raiz->hijoIzquierdo = insertar(raiz->hijoIzquierdo, llave, probabilidad);
         }
    }
    return(raiz);
}