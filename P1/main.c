/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Fernando Iglesias Iglesias LOGIN 1: f.iglesias2
 * AUTHOR 2: Luís Rodríguez Represa LOGIN 2: luis.rodriguez.represa
 * GROUP: 2.4
 * DATE: 15 / 03 / 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

void New (char *param1, char *param2, char *param3, char *param4,tList *L);
// Recibe productId, userId, productCategory y productPrice además de la lista
// Añade un nuevo producto con su identificador, el vendedor, su categoría, su precio y el número de pujas efectuadas sobre el producto
// El contador de pujas se inicializa a 0
// El producto se incorpora al final de la lista
// Una condición necesaria para que se pueda ejecutar New, es que no exista ese mismo producto en la lista antes de ejecutar New
void Stats (tList L);
// Únicamente recibe la lista
// La función imprime el identificador del producto, su vendedor, su categoría, su precio y el número de pujas efectuadas sobre el producto
// A mayores aporta por categorías (book or painting) el número de productos, la suma de los precios y el precio medio por producto
// Es necesario que la lista no esté vacía, en caso contrario no será posible devolver dichas estadísticas
void Bid (char *param1, char *param2, char *param3, tList *L);
// Recibe productId, userId, y productPrice
// Puja por un producto, modificando su precio al ofertado por el pujador y el número de pujas efectuadas sobre ese producto, imprimiendo dicha información
// Es necesario que exista dicho producto (mismo productId)
//  También ue el vendedor y el pujador sean usuarios distintos (distintos seller)
//  Y además que el precio de la puja sea mayor que el precio anterior de hacer la puja
void Delete (char *param1, tList *L);
// Recibe productId
// Elimina un producto de la lista
// Para poder ejecutar correctamente la función Delete es necesario que el productId buscado se encuentre en la lista

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4,tList *L) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: product %s seller %s category %s price %s\n",commandNumber,command,param1,param2,param3,param4);
            New(param1, param2, param3,param4,L);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c\n",commandNumber,command);
            Stats(*L);
            break;
        case 'B':
            printf("********************\n");
            printf("%s %c: product %s bidder %s price %s\n",commandNumber,command,param1,param2,param3);
            Bid(param1,param2,param3,L);
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: product %s\n",commandNumber,command,param1);
            Delete(param1,L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename,tList *L) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4,L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    tList L;
    createEmptyList(&L);

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name,&L);

    return 0;
}
void New(char *param1, char *param2, char *param3, char *param4,tList *L) {
    tItemL item;
    tPosL pos;
    strcpy(item.productId,param1);
    strcpy(item.seller,param2);
    if (strcmp(param3, "book") == 0) {     // Comprobamos si el producto es book o painting
        item.productCategory = book;
    }
    else {
        item.productCategory = painting;
    }
    item.productPrice = atof(param4); // Utilizamos atof para pasar productPrice de string a float
    item.bidCounter=0;
    pos = findItem(item.productId,*L);
    if(pos==LNULL) {  // Comprobamos si el elemento está en la lista
        if (insertItem(item,pos,L)==true) {   // En caso de que pos=LNULL, insertItem inserta automáticamente después de la última posición
            printf("* New: product %s seller %s category %s price %s\n",param1,param2,param3,param4); // Como devuelve true es que se ha podido insertar
        }
    }
    else    // En caso contrario imprimimos el error
        printf("+ Error: New not possible\n");
}
char *book_or_painting (tProductCategory category) {  // Hacemos una función que nos permita pasar productCategory a un string:
    if (category == book)
        return "book";
    else
        return "painting";
}
void Stats (tList L) {
    tItemL item;
    tPosL pos;
    int totalBooks=0, totalPaintings=0;            // Declaramos dos variables que vayan contando la cantidad de productos de cada categoría
    float sumPricesBooks=0, sumPricesPaintings=0; // Declaramos dos variables para la suma de los precios de cada categoría
    float mediaBooks,mediaPaintings;             // Declaramos dos variables para la media de los precios de cada categoría
    if (!isEmptyList(L)) {                      // Comprobamos si la lista está vacía
        for (pos = first(L); pos != LNULL; pos = next(pos, L)) { // Recorremos la lista
            item = getItem(pos, L);
            printf("Product %s seller %s category %s price %.2f bids %d\n",item.productId,item.seller,
                   book_or_painting(item.productCategory),item.productPrice,item.bidCounter);
            if (item.productCategory == book) {      // Comprobamos si el producto es book o painting
                ++totalBooks;       // Sumamos uno al contador de books
                sumPricesBooks = sumPricesBooks + item.productPrice;        // Se va sumando el precio de cada book
            }
            else {
                ++totalPaintings;     // Sumamos uno al contador de paintings
                sumPricesPaintings = sumPricesPaintings + item.productPrice; // Se va sumando el precio de cada painting
            }
        }
        if (totalBooks==0)       // En caso de que el total de books sea 0
            mediaBooks=0;       // La media del precio será 0
        else
            mediaBooks = sumPricesBooks/(float)totalBooks;

        if (totalPaintings==0)      // En caso de que el total de paintings sea 0
            mediaPaintings=0;      // La media del precio será 0
        else
            mediaPaintings = sumPricesPaintings/(float)totalPaintings;

        printf("\n");
        printf("Category Products  Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n",totalBooks,sumPricesBooks,mediaBooks);
        printf("Painting  %8d %8.2f %8.2f\n",totalPaintings,sumPricesPaintings,mediaPaintings);
    }
    else {
        printf("+ Error: Stats not possible\n");
    }
}
void Delete (char *param1, tList *L) {
    tPosL pos;
    tItemL item;
    strcpy(item.productId,param1);
    pos = findItem(param1,*L); // Buscamos la posición donde se encuentra el producto
    if (pos != LNULL) {  // Comprobamos si el producto se encuentra en la lista
        // Si se encuentra en la lista:
        item = getItem(pos,*L);   // Cogemos el item
        deleteAtPosition(pos,L); // Se elimina
        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",item.productId,item.seller,
               book_or_painting(item.productCategory),item.productPrice,item.bidCounter);
    }
    else { // En caso de que no se encuentre el producto en la lista imprimimos el error:
        printf("+ Error: Delete not possible\n");
    }
}
void Bid (char *param1, char *param2, char *param3, tList *L) {
    tPosL pos;
    tItemL item, item_temp;  // Declaramos un item auxiliar para poder comprobar las condiciones
    pos = findItem(param1, *L);  // Buscamos la posición del productId del producto por el que queremos pujar
    item_temp = getItem(pos, *L);
    strcpy(item.productId, param1);
    strcpy(item.seller, param2);
    item.productPrice = atof(param3); // Utilizamos atof para pasar productPrice de string a float
    item_temp.bidCounter = 0;  // Inicializamos a 0 el contador de pujas

    if (pos != LNULL) {  // La posición debe ser distinta de LNULL, es decir, que el producto por el que se quiere pujar esté en la lista
        if (strcmp(param2,item_temp.seller)!=0) {  // El vendedor y el pujador deben ser distintos
            if (item.productPrice > item_temp.productPrice) { // El precio de la puja debe ser mayor que el precio original
                ++item_temp.bidCounter; // Se le suma uno al contador de pujas
                item_temp.productPrice = item.productPrice; // Ponemos su nuevo precio
                printf("* Bid: product %s seller %s category %s price %.2f bids %d\n",item_temp.productId,item_temp.seller,
                       book_or_painting(item_temp.productCategory),item_temp.productPrice,item_temp.bidCounter);
                updateItem(item_temp,pos,L); // Actualizamos los datos
            }
            else // Si el precio de la puja no es mayor que el del precio anterior, imprimimos error:
                printf("+ Error: Bid not possible\n");
        }
        else  // Si el vendedor y el pujador son los mismos, imprimimos el error:
            printf("+ Error: Bid not possible\n");
    }
    else // Si no existiese el producto al que se desea pujar, imprimimos el error:
        printf("+ Error: Bid not possible\n");
}