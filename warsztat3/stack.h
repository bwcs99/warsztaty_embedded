#ifndef STACK_H
#define STACK_H


#define STACK_OK 0xAB
#define STACK_OVERFLOW 0xABC
#define STACK_EMPTY 0xABCD

struct StackRec{
    void * storage;
    struct StackRec *next;
};

typedef struct StackRec * StackType;

void stackInitialize(StackType * stack);
int stackEmpty(StackType stack);
int stackPush(void * el, size_t nbrOfBytes, StackType * stack);
void stackPop(StackType * stack);
void * stackTop(StackType stack);
void stackDestroy(StackType* stack);
void traverseStack(StackType stack, void (*fun)(StackType));
size_t getNbrOfElements(StackType stack);

#endif
