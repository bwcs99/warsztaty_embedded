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

int sumItemArrayPartition(struct SumItem** sumItemArray, int low, int high){

    struct SumItem* currentElement;
    struct SumItem* temporaryElement;
    struct SumItem* x = sumItemArray[high];
    int i = low - 1;

    for(int j = low ; j < high ; j++){

        currentElement = sumItemArray[j];

        if(currentElement->sum <= x->sum){
            i += 1;

            temporaryElement = currentElement;
            currentElement = sumItemArray[i];
            sumItemArray[i] = temporaryElement;

        }

    }

    temporaryElement = x;
    x = sumItemArray[i+1];
    sumItemArray[i+1] = temporaryElement;

    return i + 1;

}

void quickSortOfSumItemsElements(struct SumItem** sumItemArray, int low, int high){

    if(low < high){

        int pivot = sumItemArrayPartition(sumItemArray, low, high);

        quickSortOfSumItemsElements(sumItemArray, low, pivot - 1);
        quickSortOfSumItemsElements(sumItemArray, pivot + 1, high);

    }

}