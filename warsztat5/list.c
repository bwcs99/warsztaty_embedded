///@file list.c
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void listInitialize(List * list, int (*compare)(void*, void*), void (*copy)(void*, void*, size_t), size_t elem_size){

    *list = (List) malloc(sizeof(struct ListInfo));
    (*list)->firstRec = NULL;
    (*list)->compare = compare;
    (*list)->copy = copy;
    (*list)->elem_size = elem_size;

}

int listEmpty(List list){

    return list->firstRec == NULL;

}


void listInsert(List * list, void * elem){

    size_t elem_size = (*list)->elem_size;
    listType new_node = (listType)malloc(sizeof(struct ListRec));
    new_node->storage = malloc(elem_size);
    (*list)->copy(new_node->storage, elem, elem_size);
    new_node->next = NULL;

    if (listEmpty(*list)){

        (*list)->firstRec = new_node;

    }else{

        listType runner = (*list)->firstRec;

        while (runner->next != NULL){

            runner = runner->next;
        }

        runner->next = new_node;


    }


}

void * listFind(List * list, void* elem){ // potential problem here


    if (listEmpty(*list)) return NULL;

    listType runner = (*list)->firstRec;

    while(runner != NULL){
        
        if ((*list)->compare(runner->storage, elem) == 0){

            return runner->storage;
        }
        runner = runner->next;

    }

    return NULL;

}

void listRemove(List * list, void * elem){


    if (listEmpty(*list)) return;

    listType runner = (*list)->firstRec;
    listType prev = NULL;

    int found = 0;

    

    while (runner != NULL && !found){

        if ((*list)->compare(runner->storage, elem) == 0){

            found = 1;
            break;
        }
        prev = runner;
        runner = runner->next;

    }

    if (prev != NULL){

        prev->next = runner->next;
        free(runner->storage);
        free(runner);

       

    }else{

        (*list)->firstRec = (*list)->firstRec->next;
        free(runner->storage);
        free(runner);

    }


}

void listDestroy(List * list){

    while (!listEmpty(*list)){

        listType tmp = (*list)->firstRec;
        (*list)->firstRec = (*list)->firstRec->next;
        free(tmp->storage);
        free(tmp);

    }

    free(*list);

}

void listTraverse(List list, void (*visit)(void*)){

    if(listEmpty(list)) return;

    listType runner = list->firstRec;
    while (runner != NULL){

        visit(runner->storage);

        runner = runner->next;

    }

}

/**
 * Funkcja do odwracania listy w miejscu (bez tworzenia nowej listy).
 * 
 * @param[in] list 
 * @return List 
 */
List reverseList(List list){

    if (listEmpty(list)) return NULL;

    if (list->firstRec->next == NULL) return list;

    listType p = list->firstRec->next;
    listType q = list->firstRec;
    listType newHead = list->firstRec;

    while(p != NULL){

        if (q == list->firstRec) 
            q->next = NULL;
        else
            q->next = newHead;

        newHead = q;
        q = p;
        p = p->next;


    }

    q->next = newHead;
    newHead = q;

    list->firstRec = newHead;

    return list;

}

List copyList(List list){

    if (listEmpty(list)) return NULL;
    List newList;
    listInitialize(&newList, list->compare, list->copy, list->elem_size);
    listType runner = list->firstRec;

    while (runner != NULL){

        listInsert(&newList, runner->storage);
        runner = runner->next;
    }

    return newList;

}

List listReverse(List list){

    if (listEmpty(list)) return NULL;
    
    List newList = copyList(list);

    if (newList->firstRec->next == NULL) return newList;

    listType p = newList->firstRec->next;
    listType q = newList->firstRec;
    listType newHead = newList->firstRec;

    while(p != NULL){

        if (q == newList->firstRec) 
            q->next = NULL;
        else
            q->next = newHead;

        newHead = q;
        q = p;
        p = p->next;


    }

    q->next = newHead;
    newHead = q;

    newList->firstRec = newHead;

    return newList;
    


}

int listCount(List list){

    if (listEmpty(list)) return 0;

    listType runner = list->firstRec;
    int res = 0;
    while (runner != NULL){

        ++res;
        runner = runner->next;
    }

    return res;

}

int listCompare(List l1, List l2){

    int size1 = listCount(l1);
    int size2 = listCount(l2);

    if (size1 != size2){

        return 0;

    }else{

        listType runner1 = l1->firstRec;
        listType runner2 = l2->firstRec;

        while (runner1 != NULL){

            if (l1->compare(runner1->storage, runner2->storage) != 0) return 0;
            
            runner1 = runner1->next;
            runner2 = runner2->next;


        }
        return 1;
    }


}

/**
 * Funkcja do łączenia (konkatenowania) dwóch list.
 * 
 * @param[in] list1 
 * @param[in] list2 
 * 
 *  
 * */
void concatenateLists(List* list1, List* list2){

    if(list1 == NULL || list2 == NULL){

        return;

    }

    listType runner = (*list1)->firstRec;

    while(runner->next != NULL){

        runner = runner->next;
        
    }

    runner->next = (*list2)->firstRec;

    // chcę usunąć info o drugiej liście, ale nie jej elementy (dlatego nie ma listDestroy)
    free(*list2);

}

/**
 * Funkcja do dzielenia listy na pół (z jednej listy tworzy dwie o rozmiarze połowy wejściowej listy)
 * 
 * @param[in] originalList 
 * @param[in] secondHalf 
 * @return List* 
 */
List* splitListInHalf(List* originalList, List* secondHalf){

    if(originalList == NULL){

        return NULL;

    }

    if(listEmpty(*originalList)){

        return NULL;

    }

    int numberOfElements = listCount(*originalList);

    if(numberOfElements == 1){

        return originalList;

    }

    // przesuwam się do środkowego elementu listy. Tam będzie robiony podział.
    listType listHead = (*originalList)->firstRec;
    listType runner = listHead;

    size_t position = (ssize_t)(numberOfElements/2);

    while(position > 1){

        runner = runner->next;
        position -= 1;

    }

    // Nowa lista będzie miała nową głowę
    listType secondHalfHead = runner->next;

    runner->next = NULL;

    // Druga połowa jest już inną listą, więc dlatego trzeba zrobić listInitialize
    listInitialize(secondHalf, (*originalList)->compare, (*originalList)->copy, (*originalList)->elem_size);

    (*secondHalf)->firstRec = secondHalfHead;

    return secondHalf;

}

/**
 * Funkcja do usuwania wszytkich elementów z listy (czyszczenie listy), ale nie niszcząca jej.
 * 
 * @param[in] list 
 */
void listClear(List* list){

    if(list == NULL){

        return;

    }

    if(listEmpty(*list)){

        return;

    }

    listType listHead = (*list)->firstRec;

    while(listHead != NULL){

        listType tmp = listHead;

        listHead = tmp->next;

        free(tmp->storage);
        free(tmp);

    }

    (*list)->firstRec = NULL;

}

/**
 * Funkcja do łączenia dwóch posortowanych list w jedną (również posortowaną).
 * 
 * @param[in] firstList 
 * @param[in] secondList 
 */
void mergeSortedLists(List* firstList, List* secondList){

    if(firstList == NULL || secondList == NULL){

        return;

    }

    if(listEmpty(*firstList) && listEmpty(*secondList)){

        return;

    } else if(!listEmpty(*firstList) && listEmpty(*secondList)){

        return;

    } else if(listEmpty(*firstList) && !listEmpty(*secondList)){

        firstList = secondList;

    } 

    List firstListCopy = copyList(*firstList);

    listClear(firstList);

    listType firstListRunner = firstListCopy->firstRec;
    listType secondListRunner = (*secondList)->firstRec;

    while(firstListRunner != NULL && secondListRunner != NULL){

        if((*firstList)->compare(firstListRunner->storage, secondListRunner->storage) > 0){

            listInsert(firstList, secondListRunner->storage);
            secondListRunner = secondListRunner->next;

        } else if((*firstList)->compare(firstListRunner->storage, secondListRunner->storage) < 0){

            listInsert(firstList, firstListRunner->storage);
            firstListRunner = firstListRunner->next;

        } else{

            listInsert(firstList, firstListRunner->storage);
            listInsert(firstList, secondListRunner->storage);

            firstListRunner = firstListRunner->next;
            secondListRunner = secondListRunner->next;
        }
    }

    if(firstListRunner == NULL){

        while(secondListRunner != NULL){

            listInsert(firstList, secondListRunner->storage);
            secondListRunner = secondListRunner->next;

        }
    }

    if(secondListRunner == NULL){

        while(firstListRunner != NULL){

            listInsert(firstList, firstListRunner->storage);
            firstListRunner = firstListRunner->next;

        }
    } 

    listDestroy(&firstListCopy);
    listDestroy(secondList);
    
} 

/**
 * Funkcja do sortowania listy jednokierunkowej. Wykorzystano algorytm MergeSort. Złożoność obliczeniowa
 * zaimplementowanego rozwiązania wynosi O(nlog(n)).
 * 
 * @param[in] list 
 */
void listSort(List* list){


    if(list == NULL){
        return;
    }


    if(listCount(*list) == 1){
        return;
    }

    if(listEmpty(*list)){
        return;
    }

    List secondHalf;

    splitListInHalf(list, &secondHalf);

    listSort(list);
    listSort(&secondHalf);

    mergeSortedLists(list, &secondHalf);

}