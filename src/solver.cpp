//
// Created by ted on 2022/8/22.
//

#include "solver.h"

void simplify(Head* linked_list, int num){
    for(Head* clause = linked_list; clause != nullptr; clause = clause -> next_head){
        for(Data* literal = clause -> next_data; literal != nullptr; literal = literal -> next_data){
            int now_data = literal -> data;
            if(now_data == num){
                deleteHead(linked_list, clause);
            }
            else if (now_data == -num){
                deleteData(clause, literal);
            }
        }
    }
}

