#include <stdbool.h>

#ifndef SUM_ITEM_H
#define SUM_ITEM_H

struct SumItem {
    int sum;
    int firstElementIndex;
    int secondElementIndex;
};

struct SumItem* createSumItem(int sum, int firstElementIndex, int secondElementIndex);
bool checkIfSumItemsHaveCommonElements(struct SumItem* firstItem, struct SumItem* secondItem);

#endif