#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../interfaces/hash_table/hash_table.h"
#include "../interfaces/dynamic_array/array.h"
#include "../interfaces/sum_item/sum_item.h"

//runs in quadratic time
int * sumOfTwoNaive(int * inputArray, int targetSum){


    int *result = NULL;

    int inputArrayLength = array_length(inputArray);

    for (int i = 0; i < inputArrayLength; ++i){

        for (int j = 1; j < inputArrayLength; ++j){

            if (inputArray[i] != inputArray[j]){

                    int sum = inputArray[i] + inputArray[j];

                    if (sum == targetSum){
                    array_push(result, inputArray[i]);
                    array_push(result, inputArray[j]);
                    return result;
                }

            }

        }

    }

    return result;

}

int* sumOfTwoLinear(int* inputArray, int targetSum, int inputArrayLength){
    int necessaryValue;
    struct DataItem* foundItem;
    int* answer = NULL;

    for(int i = 0 ; i < inputArrayLength ; i++){

        necessaryValue = targetSum - inputArray[i];
        foundItem = search(necessaryValue);

        if(foundItem != NULL){

            if(foundItem->data == i){
                continue;
            }

            array_push(answer, inputArray[i]);
            array_push(answer, necessaryValue);

            printf("Znaleziona para: (%d, %d)\n", inputArray[i], necessaryValue);
        }

        insert(inputArray[i], i);

    }

    for(int i = 0 ; i < inputArrayLength ; i++){
        foundItem = search(inputArray[i]);

        if(foundItem != NULL){
            delete(foundItem);
        }
    }

    return answer;

}

void swap(int* a, int* b){
    
    int temp = *a;

    *a = *b;
    *b = temp;
    
}

int partition(int* inputArray, int lowerIndex, int upperIndex){

    int x = inputArray[upperIndex];
    int i = lowerIndex - 1;

    for(int j = lowerIndex ; j < upperIndex ; j++){
        
        if(inputArray[j] <= x){

            i += 1;

            swap(&inputArray[i], &inputArray[j]);

        }
    }

    swap(&inputArray[i+1], &inputArray[upperIndex]);

    return i+1;
}

void quickSort(int* inputArray, int lowerIndex, int upperIndex){

    if(lowerIndex < upperIndex){

        int pivot = partition(inputArray, lowerIndex, upperIndex);

        quickSort(inputArray, lowerIndex, pivot - 1);
        quickSort(inputArray, pivot + 1, upperIndex);

    }

}

void findSumOfThree(int* inputArray, int targetSum, int arrayLength){

    int currentElement;
    // int* answer;

    int low = 0;
    int high = arrayLength - 1;

    quickSort(inputArray, low, high);

    for(int i = 0 ; i < arrayLength - 2 ; i++){

        currentElement = inputArray[i];

        low = i + 1;

        while(low < high){
            
            if(currentElement + inputArray[low] + inputArray[high] < targetSum){

                low += 1;


            } else if(currentElement + inputArray[low] + inputArray[high] > targetSum){

                high -= 1;

            } else{

                printf("Znaleziona trójka: %d, %d, %d \n", currentElement, inputArray[low], inputArray[high]);

                break;

            }

        }
        
    }

    // return answer;

}

void findSumOfFours(int* inputArray, int targetSum, int arrayLength){

    int counter = 0;
    int sumItemsLength = (arrayLength*(arrayLength - 1))/2;
    struct SumItem* sumItems[sumItemsLength];

    for(int i = 0 ; i < arrayLength - 1 ; i++){
        for(int j = i + 1 ; j < arrayLength ; j++){

            int sum = inputArray[i] + inputArray[j];

            struct SumItem* newSumItem = createSumItem(sum, i, j);

            sumItems[counter] = newSumItem;

            counter += 1;

        }

    }

    int low = 0;
    int high = sumItemsLength - 1;

    while(low < high){
        if(sumItems[low]->sum + sumItems[high]->sum == targetSum && (!checkIfSumItemsHaveCommonElements(sumItems[low], sumItems[high]))){

            int i1 = sumItems[low]->firstElementIndex;
            int i2 = sumItems[low]->secondElementIndex;
            int i3 = sumItems[high]->firstElementIndex;
            int i4 = sumItems[high]->secondElementIndex;

            printf("Znaleziona czwórka: %d, %d, %d, %d\n", inputArray[i1], inputArray[i2], inputArray[i3], inputArray[i4]);

            return;

        } else if(sumItems[low]->sum + sumItems[high]->sum > targetSum){
            high -= 1;
        } else{
            low += 1;
        }
    }

}

int main (int argc, char * argv[]){

  int doubleTest1[5] = {0, -1, 2, -3, 1};
  int doubleTest2[5] = {1, -2, 1, 0, 5};
  int dobleTest3[6]  = {1, 4, 45, 6, 10, -8}; 
  int doubleTest4[6] = {8, 7, 2, 5, 3, 1};
 
  int tripletTest1[6] = {12, 3, 4, 1, 6, 9};
  int tripletTest2[5] = {1, 2, 3, 4, 5};
  int tripletTest3[6] = {1, 4, 45, 6, 10, 8};
  int tripletTest4[7] = {3, 1, 7, 4, 5, 9, 10};

  int foursTest1[8] = {10, 2, 3, 4, 5, 9, 7, 8};
  int foursTest2[8] = {1, 2, 3, 4, 5, 9, 7, 8};
  int foursTest3[6] = {10, 20, 30, 40, 1, 2 };
  int foursTest4[6] = {1, 4, 45, 6, 10, 12}; 

  int doublesTargetSum1 = -2;
  int doublesTargetSum2 = 0;
  int doublesTargetSum3 = 16; 
  int doublesTargetSum4 = 10;

  int tripletTargetSum1 = 24;
  int tripletTargetSum2 = 9;
  int tripletTargetSum3 = 22;
  int tripletTargetSum4 = 21;

  int foursTargetSum1 = 23;
  int foursTargetSum2 = 16;
  int foursTargetSum3 = 91;
  int foursTargetSum4 = 21; 

  printf("**** DWÓJKI - TEST 1 ****\n");
  int* doublesAnswer1 = sumOfTwoLinear(doubleTest1, doublesTargetSum1, 5);

  printf("**** DWÓJKI - TEST 2 ****\n");
  int* doublesAnswer2 = sumOfTwoLinear(doubleTest2, doublesTargetSum2, 5);

  printf("**** DWÓJKI - TEST 3 ****\n");
  int* doublesAnswer3 = sumOfTwoLinear(dobleTest3, doublesTargetSum3, 6);

  printf("**** DWÓJKI - TEST 4 ****\n");
  int* doublesAnswer4 = sumOfTwoLinear(doubleTest4, doublesTargetSum4, 6);

  printf("################## \n");
  
  printf("**** TRÓJKI - TEST 1 ****\n");
  findSumOfThree(tripletTest1, tripletTargetSum1, 6);

  printf("**** TRÓJKI - TEST 2 ****\n");
  findSumOfThree(tripletTest2, tripletTargetSum2, 5);

  printf("**** TRÓJKI - TEST 3 ****\n");
  findSumOfThree(tripletTest3, tripletTargetSum3, 6);

  printf("**** TRÓJKI - TEST 4 ****\n");
  findSumOfThree(tripletTest4, tripletTargetSum4, 7);

  printf("################## \n");

  printf("**** CZWÓRKI - TEST 1 ****\n");
  findSumOfFours(foursTest1, foursTargetSum1, 8);
  
  printf("**** CZWÓRKI - TEST 2 ****\n");
  findSumOfFours(foursTest2, foursTargetSum2, 8);

  printf("**** CZWÓRKI - TEST 3 ****\n");
  findSumOfFours(foursTest3, foursTargetSum3, 6);

  printf("**** CZWÓRKI - TEST 4 ****\n");
  findSumOfFours(foursTest4, foursTargetSum4, 6);

  printf("################## \n");

  printf("KONIEC TESTÓW...\n");

  printf("\n");

  return EXIT_SUCCESS;

}

