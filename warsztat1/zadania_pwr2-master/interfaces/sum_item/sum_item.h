#include <stdbool.h>

#ifndef SUM_ITEM_H
#define SUM_ITEM_H

struct SumItem {
    long long int sum;
    size_t firstElementIndex;
    size_t secondElementIndex;
};

struct SumItem* createSumItem(long long int sum, size_t firstElementIndex, size_t secondElementIndex);
bool checkIfSumItemsHaveCommonElements(struct SumItem* firstItem, struct SumItem* secondItem);

#endif