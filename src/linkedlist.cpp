//
// Created by ted on 2022/8/22.
//

#include "head/linkedlist.h"



void addData(Head &clause, Data* literal){
    if(clause.next_data == nullptr){
        clause.next_data = literal;
        clause.num = 1;
    }
    else{
        Data* tmp = clause.next_data;
        clause.next_data = literal;
        literal -> next_data = tmp;
        clause.num ++;
    }
}

void deleteData(Head &clause, Data* literal){
    if(literal == clause.next_data){
        clause.next_data = literal -> next_data;
    }
    else{
        for(Data* pre = clause.next_data; pre != nullptr; pre = pre -> next_data){
            if(pre -> next_data == literal){
                pre -> next_data = literal -> next_data;
            }
        }
    }
    clause.num --;
}

void copyHeap(MinHeap &new_heap, const MinHeap& C) {
    new_heap.cnt = C.cnt;
    new_heap.capacity = C.capacity;
    new_heap.heap = new Head[C.capacity];
    for(int i = 1; i <= C.cnt; i ++){
        Head clause = C.heap[i];
        Head new_clause;
        for(Data* literal = clause.next_data; literal != nullptr; literal = literal -> next_data){
            Data *new_literal = new Data;
            new_literal -> data = literal -> data;
            addData(new_clause, new_literal);
        }
        new_heap.heap[i] = new_clause;
    }
}