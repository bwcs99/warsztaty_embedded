#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"

bool checkBalanced(char* str, size_t size){

    StackType pStack;

    stackInitialize(&pStack);

    for(size_t i = 0 ; i < size ; i++){

        if(str[i] == '(' || str[i] == '['){

            stackPush(str[i], sizeof(char), &pStack);

        } else if(str[i] == ')' || str[i] == ']'){

            char currentChar = (char) stackTop(pStack);

            if(currentChar == str[i]){

                stackPop(&pStack);
                
            }

        }

    }

    if(stackEmpty(pStack)){

        return true;

    }

    return false;
}

int main(void){

    char* test1 = "((((())))))))";
    char* test2 = "()()(())[][[]]";
    char* test3 = "(([[))]]";

    return 0;
}