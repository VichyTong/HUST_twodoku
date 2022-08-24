//
// Created by ted on 2022/8/22.
//

#include "head/solver.h"

void simplify(Head* &linked_list, int data){
    for(Head* clause = linked_list; clause != nullptr; clause = clause -> next_head){
        for(Data* literal = clause -> next_data; literal != nullptr; literal = literal -> next_data){
            int now_data = literal -> data;
            if(now_data == data){
                deleteHead(linked_list, clause);
            }
            else if (now_data == -data){
                deleteData(clause, literal);
            }
        }
    }
}

Head* findSingleClause(Head* linked_list){
    for(Head* clause = linked_list; clause != nullptr; clause = clause -> next_head){
        if(clause -> num == 1){
            return clause;
        }
    }
    return nullptr;
}

bool hasEmptyClause(Head* linked_list){
    for(Head* clause = linked_list; clause != nullptr; clause = clause -> next_head){
        if(clause -> num == 0){
            return true;
        }
    }
    return false;
}

Head* createSingleClause(int v){
    Head* new_single_clause = new Head;
    Data* new_literal = new Data;
    new_literal -> data = v;
    addData(new_single_clause, new_literal);
    return new_single_clause;
}

bool DPLL(Head* linked_list, int* ans){
    Head* single_clause = findSingleClause(linked_list);
    while(single_clause != nullptr){
        int data = single_clause -> next_data -> data;
        if(data > 0){
            ans[abs(data)] = 1;
        }
        else{
            ans[abs(data)] = 0;
        }
        deleteHead(linked_list, single_clause);
        simplify(linked_list, data);
        if(linked_list == nullptr){
            return true;
        }
        else if(hasEmptyClause(linked_list)){
            return false;
        }
        single_clause = findSingleClause(linked_list);
    }
    if(linked_list->next_data == nullptr){
//        printLinkedList(linked_list);
        printf("%d\n",linked_list->num);
        printf("%d\n", hasEmptyClause(linked_list));
        printf("FUCK\n");
    }
    int v = linked_list -> next_data -> data;
    Head* linked_list_s1 = nullptr;
    Head* linked_list_s2 = nullptr;
    copyLinkedList(linked_list, linked_list_s1);
    copyLinkedList(linked_list, linked_list_s2);
    addHead(linked_list_s1, createSingleClause(v));
    addHead(linked_list_s2, createSingleClause(-v));
    if(DPLL(linked_list_s1, ans)){
        return true;
    }
    else{
        return DPLL(linked_list_s2, ans);
    }
}