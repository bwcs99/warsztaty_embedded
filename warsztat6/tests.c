/// @file tests.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

/**
 * Pomocnicza funkcja przekazywana do vectorTraverse.
 * 
 * @param a 
 */
void traverseFunction(void* a){

    char* _a = (char*)a;

    printf("Element wektora: %s \n", _a);
}

/**
 * Pomocnicza funkcja przekazywana do vectorTraverse.
 * 
 * @param a 
 */
void traverseFunction2(void* a){

    int* _a = (int*)a;

    printf("Element wektora: %d \n", *_a);
}

/**
 * Główna funkcja, w której odbywają się testy.
 * 
 * @return int 
 */
int main(void){

    Vector v1;
    Vector v2;

    int testArray[] = {-1, 2, 6, 8, 1, 2, 3, 0, 10, -11};

    printf("---- TESTY WEKTORA ! ---- \n");

    printf("\n");

    printf("Inicjuje wektory \n");
    vectorInit(&v1);
    vectorInit(&v2);

    printf("\n");

    printf("Wypełniam wektor przykładowymi danymi: \n");
    vectorPushBack(&v1, "aa");
    vectorPushBack(&v1, "ab");
    vectorPushBack(&v1, "ac");
    vectorPushBack(&v1, "ba");
    vectorPushBack(&v1, "ca");
    vectorPushBack(&v1, "da");
    vectorPushBack(&v1, "ala ma kota");

    printf("Wielkość wektora: %zu \n", vectorSize(v1));

    printf("\n");

    printf("Pojemność wektora: %zu \n", vectorCapacity(v1));

    printf("\n");

    printf("Czy wektor jest pusty: %s \n", vectorEmpty(v1) == 0  ? "NIE":"TAK");

    printf("\n");

    for(size_t i = 0 ; i < sizeof(testArray)/sizeof(int) ; ++i){

        vectorPushFront(&v2, &testArray[i]);

    }

    printf("Zawartość wektora: \n");
    vectorTraverse(v1, traverseFunction);

    printf("\n");

    vectorSet(&v1, "abc", 2);
    vectorSet(&v1, "g", 8);

    printf("Zawartość wektora po modyfikacji: \n");
    vectorTraverse(v1, traverseFunction);

    printf("\n");

    printf("Odwracam zawartość wektora: \n");
    vectorReverse(&v1);

    printf("\n");

    printf("Zawartość wektora po odwróceniu: \n");
    vectorTraverse(v1, traverseFunction);

    printf("\n");

    Vector v1Clone;

    v1Clone = vectorClone(&v1);

    printf("Zawartość sklonowanego wektora: \n");
    vectorTraverse(v1Clone, traverseFunction);

    printf("\n");

    size_t arraySize = vectorSize(v1Clone);

    char** strArray = (char**) vectorToArray(&v1Clone);

    printf("Efekt konwersji wektora na tablicę: \n");
    for(size_t i = 0 ; i < arraySize ; ++i){

        printf("Element tablicy: %s\n", strArray[i]);

    }

    vectorDestroy(&v1Clone);

    printf("\n");

    free(strArray);

    vectorPopBack(&v1);

    printf("Zawartość wektora po usunięciu ostatniego elementu: \n");
    vectorTraverse(v1, traverseFunction);

    printf("\n");

    vectorPushFront(&v1, "bbbbb");
    vectorPushFront(&v1, "vvvvvv");

    printf("Wektor po dodaniu dwóch nowych wartości z przodu: \n");
    vectorTraverse(v1, traverseFunction);

    printf("\n");

    vectorPopFront(&v1);
    vectorPopFront(&v1);
    vectorPopFront(&v1);

    printf("Wektor po usunięciu trzech wartości z początku: \n");
    vectorTraverse(v1, traverseFunction);

    printf("\n");

    printf("Liczby całkowite: \n");
    vectorTraverse(v2, traverseFunction2);

    printf("\n");

    printf("Czyszczenie wektora z napisami: \n");
    vectorClear(&v1);

    printf("Zawartość wyczyszczonego wektora: \n");
    vectorTraverse(v1, traverseFunction);

    printf("\n");

    printf("Niszczenie wektora z liczbami całkowitymi: \n");
    vectorDestroy(&v2);

    printf("Niszczenie wektora z napisami: \n");
    vectorDestroy(&v1);

    printf("\n");

    return 0;
    
}