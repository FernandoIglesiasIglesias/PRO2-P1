/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Iglesias Iglesias LOGIN 1: f.iglesias2
 * AUTHOR 2: Luís Rodríguez Represa LOGIN 2: luis.rodriguez.represa
 * GROUP: 2.4
 * DATE: 23 / 02 / 2022
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#define LNULL NULL
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct tNode* tPosL;
typedef struct tNode {   // Almacena los datos
    tItemL dato;  // Almacena la información
    tPosL next;     // Relaciona al siguiente elemento
}tNode;
typedef tPosL tList;
bool createNode (tPosL *p);
bool insertItem(tItemL d, tPosL p, tList *L);
// Recibe un item, una posición y la lista,
// devuelve true en caso de que se haya podido insertar el elemento o false en caso contrario.
// Si la posición fuese LNULL, se inserta al final de la lista
// La posición debe ser válida, y las posiciones de los elementos posteriores al elemento insertado pueden haberse visto afectadas
void updateItem(tItemL d, tPosL p, tList *L);
// Recibe un item, una posición y la lista.
// Modifica el contenido del elemento de la posición indicada,
// esta posición debe ser válida
void deleteAtPosition(tPosL, tList *L);
// Recibe una posición y la lista y elemina el elemento de la posición indicada.
// Las posiciones de los elementos posteriores al elemento eleminado pueden haberse visto afectadas
tPosL findItem(tProductId d, tList L);
// Recibe un identificador de producto y la lista
// y devuelve la posición del primer elemento de la lista que su identificador de producto coincida con el indicado,
// puede devolver NULL si no existe dicho elemento
void createEmptyList (tList* L);
// Recibe la lista
// y crea una vacía (inicializada y sin elementos)
tItemL getItem(tPosL p, tList L);
// Recibe una posición y la lista
// y devuelve el contenido de la lista de la posición indicada,
// esta posición debe ser válida
tPosL first(tList L);
// Recibe la lista
// y devuelve la posición del primer elemento de dicha lista (la lista no está vacía)
tPosL last(tList L);
// Recibe la lista
// y devuelve la posición del último elemento de dicha lista (la lista no está vacía)
tPosL previous(tPosL, tList L);
// Recibe una posición
// y la lista y devuelve la posición anterior,
// si no lo tuviese devuelve NULL (la posición que devuelve es una posición válida)
tPosL next(tPosL, tList L);
// Recibe una posición y la lista
// y devuelve la posición siguiente,
// en caso de que no tenga siguiente devuelve NULL (la posición que devuelve es una posición válida)
bool isEmptyList(tList L);
// Recibe la lista,
// comprueba si la lista está vacía (true en caso de que esté vacía o en caso contrario false)

#endif