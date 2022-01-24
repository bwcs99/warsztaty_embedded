///@file tests.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define SET_LIST(ARRAY_NAME, LIST_NAME, TYPE) do{ for(size_t i = 0 ; i < sizeof(ARRAY_NAME)/sizeof(TYPE) ; ++i){ \
                                                    listInsert(&LIST_NAME, (void*)&ARRAY_NAME[i]); \
                                                } \
                                                }  \
                                                while(0);

void displayElement(void* element){

    printf("%d ", *(int*)element);

}

void copy(void* a, void* b, size_t elem_size){

    memcpy(a, b, elem_size);

}


int compare(void* a, void* b){

    if(*(int*)a > *(int*)b){
        return 1;
    } else if(*(int*)a == *(int*)b){
        return 0;
    } else{
        return -1;
    }

}

/**
 * Funkcja do sprawdzania, czy dana lista jest palindromem, ale nie zużywająca dodatkowej pamięci.
 * Funkcja dzieli listę na pół, po czym sprawdza, czy odwrotność drugiej połowy jest taka sama
 * jak pierwsza połowa (wtedy lista jest palindromem).
 * 
 * @param[in] list 
 * @return int 
 */
int testIfPalindrome(List* list){

    int result = 0;

    if(list == NULL){

        return 0;

    }

    if(listEmpty(*list)){

        return 1;

    }

    // jeśli lista ma nieparzystą liczbę elementów to usuwam środkowy
    size_t numberOfElements = listCount((*list));

    int tmp;

    if(numberOfElements % 2 != 0){

        listType runner = (*list)->firstRec;

        ssize_t position = (numberOfElements/2) + 1;

        while(position > 1){

            runner = runner->next;
            position -= 1;

        }

        tmp = *(int*)runner->storage;

        listRemove(list, runner->storage);
    }

    List secondHalf;

    // rozdzielam listę na dwie połowy
    splitListInHalf(list, &secondHalf);

    secondHalf = reverseList(secondHalf);

    if(listCompare((*list), secondHalf)){
        result = 1;
    }

    secondHalf = reverseList(secondHalf);

    concatenateLists(list, &secondHalf);

    // po sprawdzeniu czy lista jest palindromem, muszę ponownie umieścić usunięty element (dla nieparzystej liczby elementów na liście)
    if(numberOfElements % 2 != 0){

        ssize_t position = (numberOfElements - 1)/2;

        listType p = (*list)->firstRec;

        while(position > 1){

            p = p->next;
            position -= 1;

        }

        listType q = p->next;

        listType newNode = malloc(sizeof(struct ListRec));

        newNode->storage = malloc((*list)->elem_size);
        (*list)->copy(newNode->storage, &tmp, (*list)->elem_size);

        p->next = newNode;
        newNode->next = q;

    }

    return result;
}

/**
 * Główna funkcja testująca zaimplementowane funkcjonalności.
 * 
 * @return int 
 */
int main(void){

    int testArray1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int testArray2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int testArray3[] = {1, 1, 1, 1, 1, 1};
    int testArray4[] = {1, 2, 3, 4, 3, 2, 1};

    int sortTest1[] = {-7, 8, -10, 1, 8, 2, -1, 10};
    int sortTest2[] = {-10, -10, 1, 1, -17, 8, 3, 5, 6, 7, 8, 9};
    int sortTest3[] = {-4, 1, 1, 2, -3, 5, 5, 6, 7};
    int sortTest4[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int sortTest5[] = {7, 6, 5, 4, 3, 2, 1, 0};

    List list1, list2, list3, list4, sortList5, sortList6, sortList7, sortList8, sortList9;

    listInitialize(&list1, compare, copy, sizeof(int));
    listInitialize(&list2, compare, copy, sizeof(int));

    listInitialize(&list3, compare, copy, sizeof(int));
    listInitialize(&list4, compare, copy, sizeof(int));

    listInitialize(&sortList5, compare, copy, sizeof(int));
    listInitialize(&sortList6, compare, copy, sizeof(int));
    listInitialize(&sortList7, compare, copy, sizeof(int));
    listInitialize(&sortList8, compare, copy, sizeof(int));
    listInitialize(&sortList9, compare, copy, sizeof(int));

    SET_LIST(testArray1, list1, int);
    SET_LIST(testArray2, list2, int);
    SET_LIST(testArray3, list3, int);
    SET_LIST(testArray4, list4, int);

    SET_LIST(sortTest1, sortList5, int);
    SET_LIST(sortTest2, sortList6, int);
    SET_LIST(sortTest3, sortList7, int);
    SET_LIST(sortTest4, sortList8, int);
    SET_LIST(sortTest5, sortList9, int);

    printf("Pierwsza lista: \n");

    listTraverse(list1, displayElement);


    printf("\n");

    printf("Druga lista: \n");

    listTraverse(list2, displayElement);

    printf("\n");

    List secondHalf1;
    List secondHalf2;

    splitListInHalf(&list1, &secondHalf1);
    splitListInHalf(&list2, &secondHalf2);

    printf("Pierwsza połowa pierwszej listy: \n");

    listTraverse(list1, displayElement);

    printf("\n");

    printf("Druga połowa pierwszej listy: \n");

    listTraverse(secondHalf1, displayElement);

    printf("\n");

    printf("Pierwsza połowa drugiej listy: \n");

    listTraverse(list2, displayElement);

    printf("\n");

    printf("Druga połowa drugiej listy: \n");

    listTraverse(secondHalf2, displayElement);

    printf("\n");

    printf("Łączę rozdzielone listy: \n");

    concatenateLists(&list1, &secondHalf1);
    concatenateLists(&list2, &secondHalf2);

    printf("Wynik działania łączenia: \n");

    printf("Pierwsza lista: \n");

    listTraverse(list1, displayElement);

    printf("\n");

    printf("Druga lista: \n");

    listTraverse(list2, displayElement);

    printf("\n");

    printf("Testy działania testIfPalindrome: \n");

    printf("%s \n", testIfPalindrome(&list1) ? "TAK":"NIE");

    printf("%s \n", testIfPalindrome(&list2) ? "TAK":"NIE");

    printf("%s \n", testIfPalindrome(&list3) ? "TAK":"NIE");

    printf("%s \n", testIfPalindrome(&list4) ? "TAK":"NIE");

    printf("\n");

    printf("Wszystkie listy po sprawdzeniu palindromów: \n");

    listTraverse(list1, displayElement);
    printf("\n");

    listTraverse(list2, displayElement);
    printf("\n");

    listTraverse(list3, displayElement);
    printf("\n");

    listTraverse(list4, displayElement);
    printf("\n");

    printf("\n");

    printf("Testy czyszczenia listy: \n");

    listClear(&list1);
    listClear(&list2);
    listClear(&list3);

    printf("Lista 1: \n");
    listTraverse(list1, displayElement);
    printf("\n");

    printf("Lista 2: \n");
    listTraverse(list2, displayElement);
    printf("\n");

    printf("Lista 3: \n");
    listTraverse(list3, displayElement);
    printf("\n");

    printf("\n");

    printf("Testy sortowania: \n");

    printf("Sortowanie listy 1 ! \n");
    listSort(&sortList5);

    printf("Sortowanie listy 2 ! \n");
    listSort(&sortList6);

    printf("Sortowanie listy 3 ! \n");
    listSort(&sortList7);

    printf("Sortowanie listy 4 ! \n");
    listSort(&sortList8);

    printf("Sortowanie listy 5 ! \n");
    listSort(&sortList9);

    printf("Wynik sortowania: \n");

    listTraverse(sortList5, displayElement);
    printf("\n");

    listTraverse(sortList6, displayElement);
    printf("\n");

    listTraverse(sortList7, displayElement);
    printf("\n");

    listTraverse(sortList8, displayElement);
    printf("\n");

    listTraverse(sortList9, displayElement);
    printf("\n");

    printf("\n");

    printf("Koniec testów ! \n");

    printf("\n");
    
    return 0;
}