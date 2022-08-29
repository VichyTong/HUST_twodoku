//
// Created by ted on 2022/8/22.
//

#include "head/solver.h"

void simplify(MinHeap &heap, int data){
    Head *tmp = new Head[heap.size() + 1];
    int cnt = 0;
    while(!heap.empty()){
        Head clause = heap.top();
        heap.pop();
        bool flag = true;
        for(Data* literal = clause.next_data; literal != nullptr; literal = literal -> next_data){
            int now_data = literal -> data;
            if(now_data == data){
                flag = false;
                break;
            }
            else if (now_data == -data){
                flag = true;
                deleteData(clause, literal);
            }
        }
        if(flag){
            tmp[++cnt] = clause;
        }
    }
    for(int i = 1; i <= cnt; i++){
        heap.push(tmp[i]);
    }
    delete[] tmp;
}

Head createSingleClause(int v){
    Head new_single_clause;
    Data* new_literal = new Data;
    new_literal -> data = v;
    addData(new_single_clause, new_literal);
    return new_single_clause;
}

bool DPLL(MinHeap &heap, int* ans){
    while(heap.top().num == 1){
        Head single_clause = heap.top();
        int data = single_clause.next_data -> data;
        if(data > 0){
            ans[abs(data)] = 1;
        }
        else{
            ans[abs(data)] = 0;
        }
        heap.pop();
        simplify(heap, data);
        if(heap.empty()){
            return true;
        }
        else if(heap.top().num == 0){
            return false;
        }
    }
    int v = heap.top().next_data -> data;
    MinHeap new_heap (heap.cap());
    copyHeap(new_heap, heap);
    heap.push(createSingleClause(v));
    new_heap.push(createSingleClause(-v));

    if(DPLL(heap, ans)){
        return true;
    }
    else{
        return DPLL(new_heap, ans);
    }

}