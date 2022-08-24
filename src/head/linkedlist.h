//
// Created by ted on 2022/8/21.
//

#ifndef HUST_TWODOKU_LINKEDLIST_H
#define HUST_TWODOKU_LINKEDLIST_H

#include "head/head.h"

struct Data{
    int data = 0;
    Data *next_data{};
};
struct Head{
    int num = 0;
    Data *next_data{};
    Head *next_head{};
};


void addHead(Head* &linked_list, Head* clause);
void addData(Head* clause, Data* literal);
void deleteHead(Head* &linked_list, Head* clause);
void deleteData(Head* clause, Data* literal);
void printLinkedList(Head* linked_list);
void copyLinkedList(Head* old_linked_list, Head* &new_linked_list);

#endif //HUST_TWODOKU_LINKEDLIST_H
