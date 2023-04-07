/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Iglesias Iglesias LOGIN 1: f.iglesias2
 * AUTHOR 2: Luís Rodríguez Represa LOGIN 2: luis.rodriguez.represa
 * GROUP: 2.4
 * DATE: 08 / 03 / 2022
 */

#include "static_list.h"

void createEmptyList (tList *L) { // Recibe una lista
    L->lastPos=LNULL;
}
bool isEmptyList (tList L) { // Recibe la lista
    return (L.lastPos==LNULL); // Comprobamos si la última posición es LNULL
    //Si esto ocurre devuelve true, en caso contrario false
}
tPosL first (tList L) { // Recibe la lista
    return 0; // 0 es la primera posición de un array, por eso se hace return 0
}
tPosL last (tList L) { // Recibe la lista
    return L.lastPos;
}
tPosL next (tPosL p, tList L) {   // Recibe una posición y la lista
    if (p == last(L)) { // Si p es la última posición:
        return LNULL; // Devolvemos LNULL
    }
    else {  // En caso contrario:
        return ++p; // Devolvemos la posición siguiente (p+1)
    }
}
tPosL previous (tPosL p, tList L) { // Recibe una posición y la lista
    if (p == first(L)) { // Si p es la primera posición de la lista:
        return LNULL; // Se devuelve LNULL, pues el anterior al primero es LNULL
    }
    else { // En caso contrario:
        return --p; // Se devuelve la posición anterior (p-1)
    }
}
bool insertItem (tItemL d, tPosL p, tList *L) { // Recibe el item, una posición y la lista
    tPosL i;
    if (L->lastPos == MAX - 1) { // En caso de que la lista esté llena:
        return false; // Devolvemos false, no se puede insertar
    }
    if (p == LNULL) {
        L->lastPos++;
        L->dato[L->lastPos] = d; // Insertamos al final
    }
    else {
        L->lastPos++;
        for (i = L->lastPos; i >= p + 1; i--) // Recorremos la lista hasta que la última pos. sea mayor que el siguiente de p
            L->dato[i] = L->dato[i - 1]; // Desplazamos los elementos a una pos. mayor (+1)
        L->dato[p] = d;
    }
    return true;
}
void deleteAtPosition (tPosL p, tList*L) { // Recibe una posición y la lista
    tPosL i;
    L->lastPos--; // Restamos uno la última pos, pues se ha eliminado un elemento
    for (i=p;i<=L->lastPos;i++) { // Vamos incrementando hasta la última posición
        L->dato[i] = L->dato[i + 1]; // Se sobreescribenn los elementos, con lo que se borra el elemento deseado
    }
}
tItemL getItem (tPosL p, tList L) { // Recibe una posición y la lista
    return L.dato[p];
}
tItemL updateItem (tItemL d, tPosL p, tList *L) { // Recibe un item, una posición y la lista
    return L->dato[p]=d; // Actualizamos el valor de la posición p al valor del item d
}
tPosL findItem (tProductId d, tList L) { // Recibe el id del producto y la lista
    tPosL p;
    if (L.lastPos==LNULL) { // Comprobamos si la lista está vacía
        return LNULL; // Si es así, devolvemos LNULL
    }
    else {   // En caso contrario:
        for (p=0; (p<L.lastPos)&&strcmp(L.dato[p].productId,d)!=0;p++); // Recorremos la lista buscando el id del producto
        if (strcmp(L.dato[p].productId,d)==0) {  // Si lo encuentra, se para el bucle y devolvemos la posición donde está
            return p;
        }
        else // En caso de que no esté en la lista se devuelve LNULL
            return LNULL;
    }
}