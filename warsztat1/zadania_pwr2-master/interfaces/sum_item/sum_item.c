#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sum_item.h"

struct SumItem* createSumItem(int sum, int firstElementIndex, int secondElementIndex){
    struct SumItem* newSumItem = malloc(sizeof(struct SumItem));

    newSumItem->sum = sum;
    newSumItem->firstElementIndex = firstElementIndex;
    newSumItem->secondElementIndex = secondElementIndex;

    return newSumItem;
}

bool checkIfSumItemsHaveCommonElements(struct SumItem* firstItem, struct SumItem* secondItem){

    if(firstItem->firstElementIndex == secondItem->firstElementIndex){

        return true;

    }  else if(firstItem->secondElementIndex == secondItem->secondElementIndex){

        return true;

    } else if(firstItem->firstElementIndex == secondItem->secondElementIndex){

        return true;

    } else if(firstItem->secondElementIndex == secondItem->firstElementIndex){

        return true;

    } else{

        return false;

    }
    
}

