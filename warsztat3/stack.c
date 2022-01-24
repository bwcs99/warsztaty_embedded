///@file stack.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


void stackInitialize(StackType * stack){

  *stack = NULL;

}

int stackEmpty(StackType stack){
    
  return stack == NULL;

}


void * stackTop(StackType stack){
  
  if (stackEmpty(stack)) return NULL;
  
  return stack->storage;
  
}

int stackPush(void * el, size_t nbrOfBytes, StackType * stack){
    
    StackType tmp = (StackType) malloc(sizeof(struct StackRec));

    void * elem = malloc(nbrOfBytes);

    memcpy(elem, el, nbrOfBytes);

    if (tmp == NULL){

        return STACK_OVERFLOW;

    } else{

        tmp->storage = elem;
        tmp->next = *stack;
        *stack = tmp;
        return STACK_OK;

    }


}

void stackPop(StackType * stack){

  if(stackEmpty(*stack)){
    return;
  }

   StackType tmp = *stack;
   void * el = (*stack)->storage;
   *stack = (*stack)->next;
   
   free(el);
   free(tmp);

}

/**
 * Funkcja od niszczenia stosu.
 * 
 * @param[in] stack 
 */
void stackDestroy(StackType* stack){

  while(!stackEmpty(*stack)){

    stackPop(stack);

  }

  free(*stack);
  
}

/**
 * Funkcja przechodząca po stosie i wykonująca na każdym jego elemencie funkcję fun.
 * 
 * @param[in] stack 
 * @param[in] fun 
 */
void traverseStack(StackType stack, void (*fun)(StackType)){

  if(stackEmpty(stack)){
    return;
  }

  StackType stackCopy = stack;

  while(stackCopy != NULL){

    fun(stackCopy);

    stackCopy = stackCopy->next;

  }

}

/**
 * @brief Funkcja zwracjąca liczbę elementów znajdujących się na stosie.
 * 
 * @param[in] stack 
 * @return size_t 
 */
size_t getNbrOfElements(StackType stack){

  if(stackEmpty(stack)){
    return (size_t)0;
  }

  size_t count = 0;

  StackType stackCopy = stack;

  while(stackCopy != NULL){
    count += 1;
    stackCopy = stackCopy->next;
  }

  return count;
}

