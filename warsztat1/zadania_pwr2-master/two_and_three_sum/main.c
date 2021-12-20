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

int compareIntegersFunction(const void* a, const void* b){

    int value1 = *(int*)a;
    int value2 = *(int*)b;

    if(value1 > value2){

        return 1;

    } else if(value1 < value2){

        return -1;

    } else{

        return 0;

    }
}

int* findSumOfThree(int* inputArray, long long int targetSum, size_t arrayLength){

    if(inputArray == NULL || arrayLength <= 2){
        return NULL;
    }

    int* answer = NULL;
    long long int currentSum;

    size_t low = 0;
    long long int high = arrayLength - 1;

    qsort(inputArray, arrayLength, sizeof(int), compareIntegersFunction);

    for(size_t i = 0 ; i < arrayLength - 2 ; i++){

        low = i + 1;

        while(low < high){

            currentSum = inputArray[i] + inputArray[low] + inputArray[high];
            
            if(currentSum < targetSum){

                low += 1;


            } else if(currentSum > targetSum){

                high -= 1;

            } else{

                array_push(answer, inputArray[i]);
                array_push(answer, inputArray[low]);
                array_push(answer, inputArray[high]);

                low += 1;
                high -= 1;

            }

        }
        
    }

    return answer;

}

int compareSumItemsFunction(const void* a, const void* b){

    struct SumItem* ptrLeftArgument = *((struct SumItem**)a);
    struct SumItem* ptrRightArgument = *((struct SumItem**)b);

    if(ptrLeftArgument->sum > ptrRightArgument->sum){

        return 1;

    } else if(ptrLeftArgument->sum < ptrRightArgument->sum){

        return -1;

    } else{
        
        return 0;

    }
}

bool checkIfFourIsAlreadyFound(int* answerArray, int x1, int x2, int x3, int x4){

    size_t answerArrayLength = array_length(answerArray);

    if(answerArrayLength <= 3 || answerArray == NULL){
        return false;
    }

    long long int mul1 = x1*x2*x3*x4;
    long long int sum1 = x1 + x2 + x3 + x4;

    long long int mul2, sum2;

    for(size_t i = 0 ; i < answerArrayLength ; i++){

        mul2 = answerArray[i]*answerArray[i+1]*answerArray[i+2]*answerArray[i+3];
        sum2 = answerArray[i] + answerArray[i+1] + answerArray[i+2] + answerArray[i+3];

        if(mul1 == mul2 && sum1 == sum2){
            return true;
        }

    }

    return false;
}

int* findSumOfFours(int* inputArray, long long int targetSum, size_t arrayLength){

    if(inputArray == NULL || arrayLength <= 3){

        return NULL;

    }

    int* answer = NULL;

    size_t counter = 0;
    size_t sumItemsLength = (arrayLength*(arrayLength - 1))/2;
    struct SumItem* sumItems[sumItemsLength];

    long long int sum;

    for(size_t i = 0 ; i < arrayLength - 1 ; i++){
        for(size_t j = i + 1 ; j < arrayLength ; j++){

            sum = inputArray[i] + inputArray[j];

            struct SumItem* newSumItem = createSumItem(sum, i, j);

            if(newSumItem == NULL){

                return NULL;
                
            }

            sumItems[counter] = newSumItem;

            counter += 1;

        }

    }

    size_t low = 0;
    long long int high = sumItemsLength - 1;

    qsort(sumItems, sumItemsLength, sizeof(struct SumItem*), compareSumItemsFunction);

    while(low < high){
        
        sum = sumItems[low]->sum + sumItems[high]->sum;

        if(sum == targetSum && (!checkIfSumItemsHaveCommonElements(sumItems[low], sumItems[high]))){

            int i1 = sumItems[low]->firstElementIndex;
            int i2 = sumItems[low]->secondElementIndex;
            int i3 = sumItems[high]->firstElementIndex;
            int i4 = sumItems[high]->secondElementIndex;

            if(checkIfFourIsAlreadyFound(answer, inputArray[i1], inputArray[i2], inputArray[i3], inputArray[i4])){

                low += 1;
                high -= 1;

                continue;
            }

            array_push(answer, inputArray[i1]);
            array_push(answer, inputArray[i2]);
            array_push(answer, inputArray[i3]);
            array_push(answer, inputArray[i4]);

            low += 1;
            high -= 1;

        } else if(sum > targetSum){

            high -= 1;

        } else{

            low += 1;

        }
    }

    return answer;

}

void printDoubles(int* answerArray){

    size_t answerArrayLength = array_length(answerArray);

    if(answerArrayLength < 2 || answerArray == NULL){
        printf("Nie znaleziono żadnych dwójek...\n");
        return;
    }

    for(size_t i = 0 ; i < answerArrayLength ; i+=2){
        printf("Znaleziona dwójka: %d, %d\n", answerArray[i], answerArray[i+1]);
    }

}

void printTriples(int* answerArray){
    
    size_t answerArrayLength = array_length(answerArray);

    if(answerArrayLength < 3 || answerArray == NULL){
        printf("Nie znaleziono żadnych trójek...\n");
        return;
    }

    for(size_t i = 0 ; i < answerArrayLength ; i+=3){
        printf("Znaleziona trójka: %d, %d, %d\n", answerArray[i], answerArray[i+1], answerArray[i+2]);
    }
}

void printFours(int* answerArray){

    size_t answerArrayLength = array_length(answerArray);

    if(answerArrayLength < 4 || answerArray == NULL){
        printf("Nie znaleziono żadnych czwórek...\n");
        return;
    }

    for(size_t i = 0 ; i < answerArrayLength ; i+=4){
        printf("Znaleziona czwórka: %d, %d, %d, %d\n", answerArray[i], answerArray[i+1], answerArray[i+2], answerArray[i+3]);
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
  int foursTest3[6] = {10, 20, 30, 40, 1, 2};
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
  printDoubles(doublesAnswer1);

  printf("**** DWÓJKI - TEST 2 ****\n");
  int* doublesAnswer2 = sumOfTwoLinear(doubleTest2, doublesTargetSum2, 5);
  printDoubles(doublesAnswer2);

  printf("**** DWÓJKI - TEST 3 ****\n");
  int* doublesAnswer3 = sumOfTwoLinear(dobleTest3, doublesTargetSum3, 6);
  printDoubles(doublesAnswer3);

  printf("**** DWÓJKI - TEST 4 ****\n");
  int* doublesAnswer4 = sumOfTwoLinear(doubleTest4, doublesTargetSum4, 6);
  printDoubles(doublesAnswer4);

  printf("################## \n");
  
  printf("**** TRÓJKI - TEST 1 ****\n");
  int* triplesAnswer1 = findSumOfThree(tripletTest1, tripletTargetSum1, 6);
  printTriples(triplesAnswer1);

  printf("**** TRÓJKI - TEST 2 ****\n");
  int* triplesAnswer2 = findSumOfThree(tripletTest2, tripletTargetSum2, 5);
  printTriples(triplesAnswer2);

  printf("**** TRÓJKI - TEST 3 ****\n");
  int* triplesAnswer3 = findSumOfThree(tripletTest3, tripletTargetSum3, 6);
  printTriples(triplesAnswer3);

  printf("**** TRÓJKI - TEST 4 ****\n");
  int* triplesAnswer4 = findSumOfThree(tripletTest4, tripletTargetSum4, 7);
  printTriples(triplesAnswer4);

  printf("################## \n");

  printf("**** CZWÓRKI - TEST 1 ****\n");
  int* foursAnswer1 = findSumOfFours(foursTest1, foursTargetSum1, 8);
  printFours(foursAnswer1);
  
  printf("**** CZWÓRKI - TEST 2 ****\n");
  int* foursAnswer2 = findSumOfFours(foursTest2, foursTargetSum2, 8);
  printFours(foursAnswer2);

  printf("**** CZWÓRKI - TEST 3 ****\n");
  int* foursAnswer3 = findSumOfFours(foursTest3, foursTargetSum3, 6);
  printFours(foursAnswer3);

  printf("**** CZWÓRKI - TEST 4 ****\n");
  int* foursAnswer4 = findSumOfFours(foursTest4, foursTargetSum4, 6);
  printFours(foursAnswer4);

  printf("################## \n");

  printf("KONIEC TESTÓW...\n");

  printf("\n");

  return EXIT_SUCCESS;

}

