//
// Created by ted on 2022/8/21.
//

#ifndef HUST_TWODOKU_LINKEDLIST_H
#define HUST_TWODOKU_LINKEDLIST_H

#include "head/heap.h"
#include "head/head.h"

void addData(Head &clause, Data* literal);
void deleteData(Head &clause, Data* literal);
void copyHeap(MinHeap &new_heap, const MinHeap& C);

#endif //HUST_TWODOKU_LINKEDLIST_H
