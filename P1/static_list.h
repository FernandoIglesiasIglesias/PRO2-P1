/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Iglesias Iglesias LOGIN 1: f.iglesias2
 * AUTHOR 2: Luís Rodríguez Represa LOGIN 2: luis.rodriguez.represa
 * GROUP: 2.4
 * DATE: 07 / 03 / 2022
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#define LNULL -1
#define MAX 25
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef int tPosL;
typedef struct tList {
    tItemL dato[MAX];
    tPosL lastPos;
}tList;

bool insertItem(tItemL d, tPosL p, tList *L);
//Recibe un item, una posición y la lista,
// devuelve true en caso de que se haya podido insertar el elemento o false en caso contrario.
// En caso de que la posición recibida sea LNULL, se inserta al final de la lista
// La posición debe ser válida o LNULL, y las posiciones de los elementos posteriores al elemento insertado pueden haberse visto afectadas
tItemL updateItem(tItemL d, tPosL p, tList *L);
//Recibe un item, una posición y la lista.
// Modifica/Actualiza el contenido del elemento de la posición indicada,
// esta posición debe ser válida
void deleteAtPosition(tPosL, tList *L);
//Recibe una posición y la lista
// elemina el elemento de la posición indicada.
// Las posiciones de los elementos posteriores al elemento eleminado pueden haberse visto afectadas
tPosL findItem(tProductId d, tList L);
//Recibe un identificador de producto y la lista
// devuelve la posición del primer elemento de la lista que su identificador de producto coincida con el indicado,
// puede devolver NULL si no se encontrase dicho elemento en la lista
// Primero comprueba si la lista está vacía
void createEmptyList (tList* L);
//Recibe la lista
// crea una vacía (inicializada y sin elementos)
tItemL getItem(tPosL p, tList L);
//Recibe una posición y la lista
// devuelve el contenido de la lista de la posición indicada,
// esta posición debe ser válida
tPosL first(tList L);
// Recibe la lista
// devuelve la posición del primer elemento de dicha lista
// (la lista no está vacía)
tPosL last(tList L);
//Recibe la lista
// devuelve la posición del último elemento de dicha lista
// (la lista no está vacía)
tPosL previous(tPosL, tList L);
//Recibe una posición y la lista
// devuelve la posición anterior,
// si la posición fuese la primera de una devuelve LNULL
// (la posición que devuelve es una posición válida)
tPosL next(tPosL, tList L);
// Recibe una posición y la lista
// devuelve la posición siguiente,
// en caso de que la posición sea la última de la lista devuelve LNULL
// (la posición que devuelve es una posición válida)
bool isEmptyList(tList L);
// Recibe la lista,
// comprueba si la lista está vacía (true en caso de que esté vacía o false en caso contrario)

#endif
