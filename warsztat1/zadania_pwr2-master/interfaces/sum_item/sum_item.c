#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sum_item.h"

struct SumItem* createSumItem(long long int sum, size_t firstElementIndex, size_t secondElementIndex){

    struct SumItem* newSumItem = malloc(sizeof(struct SumItem));

    if(newSumItem != NULL){

        newSumItem->sum = sum;
        newSumItem->firstElementIndex = firstElementIndex;
        newSumItem->secondElementIndex = secondElementIndex;

    }

    return newSumItem;
}

bool checkIfSumItemsHaveCommonElements(struct SumItem* firstItem, struct SumItem* secondItem){

    if(firstItem == NULL || secondItem == NULL){

        return false;
        
    }

    if(firstItem->firstElementIndex == secondItem->firstElementIndex){

        return true;

    }  else if(firstItem->secondElementIndex == secondItem->secondElementIndex){

        return true;

    } else if(firstItem->firstElementIndex == secondItem->secondElementIndex){

        return true;

    } else if(firstItem->secondElementIndex == secondItem->firstElementIndex){

        return true;

    }

    return false;
    
}

