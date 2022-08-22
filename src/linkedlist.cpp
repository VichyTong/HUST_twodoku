//
// Created by ted on 2022/8/22.
//

#include "linkedlist.h"


void addHead(Head* &linked_list, Head* clause){
    if(linked_list == nullptr){
        linked_list = clause;
        return;
    }
    clause -> next_head = linked_list;
    clause -> next_data = nullptr;
    linked_list = clause;
}
void addData(Head* head, Data* literal){
    if(head -> next_data == nullptr){
        head -> next_data = literal;
        head -> num = 1;
    }
    else{
        Data* tmp = head -> next_data;
        head -> next_data = literal;
        literal -> next_data = tmp;
        head -> num ++;
    }
}
void deleteHead(Head* &linked_list, Head* clause){
    if(clause == nullptr){
        return;
    }
    if(clause == linked_list) {
        linked_list = clause -> next_head;
    }
    else{
        for(Head* pre = linked_list; pre != nullptr; pre = pre -> next_head){
            if(pre -> next_head == clause){
                pre -> next_head = clause -> next_head;
            }
        }
    }
}
void deleteData(Head* clause, Data* literal){
    if(literal == clause -> next_data){
        clause -> next_data = clause -> next_data;
    }
    else{
        for(Data* pre = clause -> next_data; pre != nullptr; pre = pre -> next_data){
            if(pre -> next_data == literal){
                pre -> next_data = literal -> next_data;
            }
        }
    }
    clause -> num --;
}

void printLinkedList(Head* linked_list){
    for(Head* clause = linked_list; clause != nullptr; clause = clause -> next_head){
        for(Data* literal = clause -> next_data; literal != nullptr; literal = literal -> next_data){
            printf("%d ",literal -> data);
        }
        printf("\n");
    }
}