/// @file vector.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

static size_t increaseCapacity(size_t capacity){

    if(capacity + VECTOR_INITIAL_CAPACITY <= VECTOR_MAX_CAPACITY){

        capacity += VECTOR_INITIAL_CAPACITY;

    }

    return capacity;
}

static size_t decreaseCapacity(size_t capacity){

    if(capacity - VECTOR_INITIAL_CAPACITY >= VECTOR_INITIAL_CAPACITY){

        capacity -= VECTOR_INITIAL_CAPACITY;

    }

    return capacity;
}

static void vectorResize(Vector* v, size_t newCapacity){

    if(v == NULL){

        return;

    }

    size_t oldCapacity = vectorCapacity((*v));

    if(newCapacity == oldCapacity){

        return;

    }

    void** tmp = realloc(v->elements, newCapacity*sizeof(void*));

    if(tmp != NULL){

        v->elements = tmp;
        
        v->capacity = newCapacity;

    }

}

/**
 * Funkcja służąca do inicjalizacji pustego wektora.
 * 
 * @param v 
 */
void vectorInit(Vector* v){
    
    v->size = 0;
    v->capacity = VECTOR_INITIAL_CAPACITY;
    v->elements = malloc(sizeof(void*)*VECTOR_INITIAL_CAPACITY);

}

/**
 * Funkcja wstawiająca nowy element na koniec wektora.
 * 
 * @param v 
 * @param element 
 */
void vectorPushBack(Vector* v, void* element){

    if(v == NULL){
        
        return;

    }

    size_t size = vectorSize((*v));

    if(size + 1 > VECTOR_MAX_CAPACITY){

        return;

    }

    size_t capacity = vectorCapacity((*v));

    if(size + 1 > capacity){

        size_t newCapacity = increaseCapacity(capacity);

        vectorResize(v, newCapacity);

    } 

    v->elements[size] = element;

    size += 1;

    v->size = size;

}

/**
 * Funkcja wstawiająca nowy element na początek wektora.
 * 
 * @param v 
 * @param element 
 */
void vectorPushFront(Vector* v, void* element){

    if(v == NULL || element == NULL){

        return;

    }

    size_t size = vectorSize((*v));
    size_t capacity = vectorCapacity((*v));

    if(size + 1 > VECTOR_MAX_CAPACITY){

        return;

    }

    size_t bytesToMove = size*sizeof(void*);

    if(size + 1 > capacity){

        size_t newCapacity = increaseCapacity(capacity);

        vectorResize(v, newCapacity);

    } 

    memmove(v->elements + 1, v->elements, bytesToMove);

    v->elements[0] = element;

    v->size = size + 1;

}

/**
 * Funkcja służąca do zmieniania wybranego elementu wektora (identyfikowanego za pomocą indeksu).
 * 
 * @param v 
 * @param newValue 
 * @param index 
 */
void vectorSet(Vector* v, void* newValue, size_t index){

    if(v == NULL){

        return;

    }

    if(vectorEmpty((*v))){

        return;

    }

    size_t size = vectorSize((*v));

    if(index >= size){

        return;

    }

    v->elements[index] = newValue;
}

/**
 * Funkcja służąca do pobierania wybranego elementu wektora (za pomocą indeksu).
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vectorGet(Vector v, size_t index){

    if(vectorEmpty(v)){

        return NULL;

    }

    size_t size = vectorSize(v);

    if(index >= size){

        return NULL;

    }

    return v.elements[index];
}

/**
 * Funkcja do sprawdzania, czy dany wektor jest pusty.
 * 
 * @param v 
 * @return int 
 */
int vectorEmpty(Vector v){

    if(v.size == 0){

        return 1;

    }

    return 0;
}

/**
 * Funkcja do pobierania rozmiaru wektora.
 * 
 * @param v 
 * @return size_t 
 */
size_t vectorSize(Vector v){

    return v.size;

}

/**
 * Funkcja do pobierania pojemności wektora.
 * 
 * @param v 
 * @return size_t 
 */
size_t vectorCapacity(Vector v){

    return v.capacity;

}

/**
 * Funkcja iterująca po każdym elemencie wektora, i wykonująca na nim funkcję function (wskaźnik
 * do funkcji).
 * 
 * @param v 
 * @param function 
 */
void vectorTraverse(Vector v, void (*function)(void*)){

    if(vectorEmpty(v)){

        return;

    }

    size_t size = vectorSize(v);

    for(size_t i = 0 ; i < size ; i++){

        function(v.elements[i]);

    }

}

/**
 * Funkcja do odwracania kolejności elementów w wektorze (standardowy algorytm).
 * 
 * @param v 
 */
void vectorReverse(Vector* v){

    if(v == NULL){

        return;

    }

    if(vectorEmpty((*v))){

        return;

    }

    size_t size = vectorSize((*v));

    if(size == 1){

        return;

    }

    size_t endPosition = (size - 1) / 2;

    size_t beg = 0;
    size_t end = size - 1;

    void* tmp;

    while(beg <= endPosition){

        if(beg == endPosition && size % 2 != 0){

            break;

        }

        tmp = v->elements[beg];

        v->elements[beg] = v->elements[end];

        v->elements[end] = tmp;

        beg += 1;
        end -= 1;
    }
}

/**
 * Funkcja służąca do klonowania wektora.
 * 
 * @param v 
 * @return Vector 
 */
Vector vectorClone(Vector* v){ 

    Vector vClone;

    vectorInit(&vClone);

    if(v == NULL){

        return vClone;

    }

    if(vectorEmpty((*v))){

        return vClone;

    }

    size_t size = vectorSize((*v));

    for(size_t  i = 0 ; i < size ; ++i){

        void* item = vectorGet((*v), i);

        vectorPushBack(&vClone, item);

    }

    return vClone;
}

/**
 * Funkcja służąca do konwersji wektora na tablicę.
 * 
 * @param v 
 * @return void** 
 */
void** vectorToArray(Vector* v){ 

    if(v == NULL){

        return NULL;

    }

    size_t size = vectorSize((*v));

    void** array = malloc(sizeof(void*)*size);


    if(array == NULL){

        return NULL;

    }

    for(size_t i = 0 ; i < size ; ++i){

        array[i] = vectorGet((*v), i);

    }

    return array;

}

/**
 * Funkcja usuwająca element wektora (z przodu).
 * 
 * @param v 
 */
void vectorPopFront(Vector* v){

    if(v == NULL){

        return;

    }

    if(vectorEmpty((*v))){

        return;

    }

    size_t size = vectorSize((*v));
    size_t capacity = vectorCapacity((*v));
    size_t bytesToMove = (size - 1)*sizeof(void*);

    v->elements[0] = NULL;

    memmove(v->elements, v->elements + 1, bytesToMove);

    if((size - 1) % VECTOR_INITIAL_CAPACITY == 0){

        size_t newCapacity = decreaseCapacity(capacity);

        vectorResize(v, newCapacity);
         
    }

    v->size = size - 1;

}

/**
 * Funkcja usuwająca element wektora od końca.
 * 
 * @param v 
 */
void vectorPopBack(Vector* v){

    if(v == NULL){

        return;

    }

    if(vectorEmpty((*v))){

        return;

    }

    size_t size = vectorSize((*v));
    size_t capacity = vectorCapacity((*v));

    vectorSet(v, NULL, size - 1);

    if((size - 1) % VECTOR_INITIAL_CAPACITY == 0){

        size_t newCapacity = decreaseCapacity(capacity);

        vectorResize(v, newCapacity);

    }

    v->size = size - 1;
}

/**
 * Funkcja służąca do czyszczenia wektora (usuwanie wszystkich elementów z wektora).
 * 
 * @param v 
 */
void vectorClear(Vector* v){

    if(v == NULL){

        return;

    }

    if(vectorEmpty((*v))){

        return;

    }

    size_t size = vectorSize((*v));

    for(size_t i = 0 ; i < size ; ++i){

        vectorSet(v, NULL, i);
    }

    v->size = 0;
    v->capacity = VECTOR_INITIAL_CAPACITY;

    vectorResize(v, VECTOR_INITIAL_CAPACITY);

}

/**
 * Funkcja do niszczenia wektora.
 * 
 * @param v 
 */
void vectorDestroy(Vector* v){

    if(v == NULL){

        return;

    }

    vectorClear(v);

    free(v->elements);   

}

