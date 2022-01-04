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

    }else{

        tmp->storage = elem;
        tmp->next = *stack;
        *stack = tmp;
        return STACK_OK;

    }


}

void stackPop(StackType * stack){

   StackType tmp = *stack;
   void * el = (*stack)->storage;
   *stack = (*stack)->next;
   
   free(el);
   free(tmp);

}

