/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Iglesias Iglesias LOGIN 1: f.iglesias2
 * AUTHOR 2: Luís Rodríguez Represa LOGIN 2: luis.rodriguez.represa
 * GROUP: 2.4
 * DATE: 23 / 02 / 2022
 */

#include "dynamic_list.h"

void createEmptyList (tList* L) {   // Recibimos *l
    *L = LNULL;
}
bool isEmptyList(tList L){     // Recibimos la lista
    return L == LNULL;      // En caso de que sea LNULL (la lista está vacía) devuelve true, en caso contrario false
}
tPosL first(tList L){   // Recibimos la lista
    return L;
}
tPosL last(tList L){    // Recibimos la lista
    tPosL p;
    for(p=L; p->next != LNULL; p=p->next); // Recorremos la lista hasta el final
    return p;       // Como el bucle acaba al final de la lista (en la última posición, antes de LNULL) se devuelve p
}
tPosL next(tPosL p, tList L){       // Recibimos una posición y lista
    return p->next;
}
tPosL previous(tPosL p, tList L) {       // Recibimos posición y lista
    tPosL q;
    if (p == L)        // Comprobamos si nos encontramos en la primera posición
        return LNULL;   // El anterior de la primera posición es LNULL
    else
    {
        for (q = L; q->next != p; q = q->next);      // Recorremos la lista hasta que el siguiente de q sea igual p
        return q;   // Devolvemos la posición anterior a p
    }
}
bool createNode (tPosL *p) {
    *p = malloc(sizeof(**p));
    return *p != LNULL;
}
bool insertItem(tItemL d, tPosL p, tList *L){        // Recibe un item, posición y lista
    tPosL q,r;
    if(!createNode(&q))             // Comprobamos si hay espacio para insertar
        return false;               // En caso de que no se pueda, se devuelve false
    else{
        q->dato = d;
        q->next = LNULL;
        if(*L == LNULL){           // Comprobamos si la lista está vacía
            *L = q;
        }else if(p == LNULL){
            for (r = *L; r->next != LNULL;r = r->next);    // Recorremos la lista hasta que el next de r sea NULL
            r->next = q;
        }else if(*L == p){
            q->next = p;
            *L = q;
        }else{
            q->dato = p->dato;
            p->dato = d;
            q->next = p->next;
            p->next = q;
        }
        return true;
    }
}
void deleteAtPosition(tPosL p, tList * L){ // Recibe una posición y la lista
    tPosL q;
    if(p==*L) {    // En caso de que p sea la primera pos.:
        *L=(*L)->next;        // Asignamos a L su siguiente
    }
    else if(p->next==LNULL) {           // En caso de que el siguiente de p sea LNULL, es decir, se encuentra al final de la lista:
        for(q=*L; q->next!=p; q=q->next);         // Recorremos hasta que next de q sea LNULL
        q->next=LNULL;
    }
    else{      // Si se encontrase por el medio de la lista, es decir, ni en la primera pos. ni en la última:
        q=p->next;
        p->dato=q->dato;
        p->next=q->next;
        p=q;
    }
    free(p);
}
tItemL getItem(tPosL p, tList L) {   // Recibe una posición y lista
    return (p->dato);
}
void updateItem(tItemL d, tPosL p, tList*L){   // Recibe un item, una posición y la lista
    p->dato = d;
}
tPosL  findItem(tProductId d, tList L){            // Recibe el identificador de producto y la lista
    tPosL p;
    for (p = L; (p != LNULL) && (strcmp(p->dato.productId , d)!=0);p = p->next); // Buscamos el elemento de la lista cuyo identificador de producto corresponde con el buscado
    return p;                  // Devolvemos la posición donde se encuentra el dato
}