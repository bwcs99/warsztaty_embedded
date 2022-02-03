#ifndef VECTOR_H    
#define VECTOR_H

#include <stdio.h>

#define VECTOR_MAX_CAPACITY 2048*2048
#define VECTOR_INITIAL_CAPACITY 5

typedef struct Vector{

    void** elements;
    size_t size;
    size_t capacity;

} Vector;


void vectorInit(Vector* v);
void vectorPushBack(Vector* v, void* element);
void vectorPushFront(Vector* v, void* element);
void vectorSet(Vector* v, void* newValue, size_t index);
void* vectorGet(Vector v, size_t index);
int vectorEmpty(Vector v);
size_t vectorSize(Vector v);
size_t vectorCapacity(Vector v);
void vectorTraverse(Vector v, void (*function)(void*));
void vectorReverse(Vector* v);
Vector vectorClone(Vector* v);
void** vectorToArray(Vector* v);
void vectorPopFront(Vector* v);
void vectorPopBack(Vector* v);
void vectorClear(Vector* v);
void vectorDestroy(Vector* v);

#endif
