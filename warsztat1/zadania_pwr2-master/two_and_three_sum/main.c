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

/* Błażej Wróbel, Wydział Informatyki i Telekomunikacji, PWr */

/* Funkcja znajdująca wszystkie pary w tablicy, które sumują się do zadanego parametru. 
Funkcja działa w czasie O(n) */
/* Funkcja nie korzysta z array_length do pobrania długości tablicy, ponieważ dane testowe
są zwykłkymi tablicami z C (na początku tablicy z dynamic_array jest informacja o aktualnej
liczbie elementów oraz jej pojemności. W tablicach z C tego nie ma). */
int* sumOfTwoLinear(int* inputArray, long long int targetSum, size_t inputArrayLength){

    /* Jeśli przekazana tablica jest NULLem lub ma długość mniejszą niż 2, to kończymy */
    if(inputArray == NULL || inputArrayLength < 2){

        return NULL;

    }

    /* Tablica na znalezione dwójki */
    int* answer = NULL;

    /* Zmienna, w której jest przechowywana wartość, która jest potrzebna do utworzenia
    docelowej sumy */
    long long int necessaryValue;

    /* Potrzebne do sprawdzenia, czy istnieje element o danym kluczu w tablicy haszowej */
    struct DataItem* foundItem;

    /* Pętla do szukania par i dodawania ich do odpowiedzi */
    for(size_t i = 0 ; i < inputArrayLength ; i++){
        
        /* Sprawdzam, czy wartość do uzyskania docelowej sumy jest w tablicy haszowej */
        necessaryValue = targetSum - inputArray[i];
        foundItem = search(necessaryValue);

        if(foundItem != NULL){
            /* Jeśli jest, to oznacza, że mamy parę, która sumuje się do zadanego parametru */
            array_push(answer, inputArray[i]);
            array_push(answer, necessaryValue);

        }

        insert(inputArray[i], i);

    }

    /* Aby móc użyć tablicy haszowej w następnych testach, trzeba ją wyczyścić */
    for(size_t i = 0 ; i < inputArrayLength ; i++){

        foundItem = search(inputArray[i]);

        if(foundItem != NULL){

            delete(foundItem);

        }
    }

    return answer;

}

/* Komparator, potrzebny dp funkcji bibliotecznej qsort */
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

/* Funkcja znajdująca trójki sumujące się do zadanego parametru. Jej złożoność obliczeniowa
wynosi O(n^2). Zastosowano technikę dwóch wskaźników (two pointers method) */
int* findSumOfThree(int* inputArray, long long int targetSum, size_t arrayLength){

    /* Jeśli tablica jest NULLem lub ma mniej niż 3 elementy, to kończymy */
    if(inputArray == NULL || arrayLength <= 2){
        return NULL;
    }

    /* Tablica na znalezione trójki */
    int* answer = NULL;
    long long int currentSum;

    /* Wskaźniki używane w two pointers method */
    size_t low;
    long long int high;

    /* Aby móc użyć metody dwóch wskaźników, tablica musi być posortowana */
    qsort(inputArray, arrayLength, sizeof(int), compareIntegersFunction);

    for(size_t i = 0 ; i < arrayLength - 2 ; i++){

        low = i + 1;
        high = arrayLength - 1;

        while(low < high){

            currentSum = inputArray[i] + inputArray[low] + inputArray[high];
            
            /* Jeśli aktualna suma jest mniejsza niż zadana, to wskaźnik low jest przesuwany
            w prawo (w kierunku większych wartości) */
            if(currentSum < targetSum){

                low += 1;

            /* Jeśli aktualna suma jest większa niż zadana, to wskaźnik high jest przesuwany
            w lewo (w kierunku mniejszych wartości) */
            } else if(currentSum > targetSum){

                high -= 1;
              /* Jeśli aktualna suma jest równa zadanej, to znaleźliśmy odpowiednią trójkę.
              Przesuwam wskaźnik low w prawo i high w lewo - to powoduje, że mogę znaleźć jakieś
              inne rozwiązanie */
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

/* Kolejny komparator, potrzebny bibliotecznej funkcji qsort */
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

/* Funkcja sprawdzająca, czy znaleziona czwórka jest już w tablicy z odpowiedzią */
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

/* Funkcja znajdująca czwórki sumujące się do zadanego parametru. Jej złożoność obliczeniowa
to O((n^2)log(n)). Istnieje inne rozwiązanie - po wygenerowaniu wszystkich sum dwójek użyć
tablicy haszowej (problem redukuje się do znajdowania dwójek sumujących się do zadanego parametru).
W takim rozwiązaniu złożoność obliczeniowa wynosi O(n^2) */
int* findSumOfFours(int* inputArray, long long int targetSum, size_t arrayLength){

    if(inputArray == NULL || arrayLength <= 3){

        return NULL;

    }

    int* answer = NULL;

    /* Zmienne potrzebne do utworzenia tablicy sum wszystkich dwójek */
    size_t counter = 0;
    size_t sumItemsLength = (arrayLength*(arrayLength - 1))/2;

    /* Definicja struktury SumItem znajduje się w interfaces/sum_item/sum_item.h */
    /* W tej strukturze jest przechowywana suma danej dwójki i indeksy elementów tworzących
    tę dwójkę */
    struct SumItem* sumItems[sumItemsLength];

    long long int sum;

    /* Obliczam sumy wszystkich dwójek w tablicy i umieszczam je w tablicy sumItems */
    for(size_t i = 0 ; i < arrayLength - 1 ; i++){
        for(size_t j = i + 1 ; j < arrayLength ; j++){

            sum = inputArray[i] + inputArray[j];

            struct SumItem* newSumItem = createSumItem(sum, i, j);

            /* Jeśli nie udało się utworzyć struktury (malloc zwrócił NULL), to kończymy */
            if(newSumItem == NULL){

                return NULL;
                
            }

            sumItems[counter] = newSumItem;

            counter += 1;

        }

    }

    /* Wskaźniki do metody dwóch wskaźników */
    size_t low = 0;
    long long int high = sumItemsLength - 1;

    /* Znowu użyje metody dwóch wskaźników, więc trzeba posortować tablicę rosnąco, względem
    sum dwójek */
    qsort(sumItems, sumItemsLength, sizeof(struct SumItem*), compareSumItemsFunction);

    /* Metoda (prawie) identyczna jak w szukaniu trójek. Tutaj (dodatkowo) trzeba uważać, aby
    nie wliczyć do czwórki dwa razy tego samego elementu (dlatego w strukturze SumItem są pola
    na indeksy elementów tworzących sumę) - do sprawdzenia tego służy metoda 
    checkIfSumItemsHaveCommonElements */ 
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

/* Funkcja do drukowania na STDOUT dwójek */
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

/* Funkcja do drukowania na STDOUT trójek */
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

/* Funkcja do drukowania na STDOUT czwórek */
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

  /* Testy zaimplementowanych funkcji. Dla każdej z funkcji po cztery przypadki testowe */

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

