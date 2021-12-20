#include <stdbool.h>

#ifndef SUM_ITEM_H
#define SUM_ITEM_H

/* Tutaj znajduje się definicja struktury SumItem */
struct SumItem {
    /* Suma pary */
    long long int sum;

    /* Indeks (w tablicy) pierwszego elementu */
    size_t firstElementIndex;

    /* Indeks (w tablicy) drugiego elementu */
    size_t secondElementIndex;
};

/* Funkcja do tworzenia struktur SumItem */
struct SumItem* createSumItem(long long int sum, size_t firstElementIndex, size_t secondElementIndex);

/* Funkcja do sprawdzania, czy dwie sumy par, nie zawierają w sobie dokładnie tych samych
elementów */
bool checkIfSumItemsHaveCommonElements(struct SumItem* firstItem, struct SumItem* secondItem);

#endif