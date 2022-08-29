//
// Created by ted on 2022/8/27.
//

#include "head/heap.h"

MinHeap::MinHeap(int cap) {
    cnt = 0;
    capacity = cap;
    heap = new Head[cap];
//    memset(heap, 0 ,sizeof (Head *) * cap);
}

MinHeap::~MinHeap() {
    cnt = 0;
    capacity = 0;
    delete[] heap;
}

void MinHeap::filterDown(int start) {
    int now = start;
    while((now << 1) <= cnt){
        int left_son = now << 1, right_son = now << 1 | 1;
        int nxt = left_son;
        if(right_son <= cnt && heap[right_son] < heap[left_son]){
            nxt = right_son;
        }
        if(heap[nxt] < heap[now]){
            swap(heap[now], heap[nxt]);
        }
        else{
            break;
        }
        now = nxt;
    }
}

void MinHeap::filterUp() {
    int now = cnt;
    while(now > 1){
        int nxt = now >> 1;
        if(heap[now] < heap[nxt]){
            swap(heap[nxt], heap[now]);
        }
        else{
            break;
        }
        now = nxt;
    }
}

void MinHeap::pop() {
    swap(heap[1], heap[cnt]);
    cnt --;
    filterDown(1);
}

void MinHeap::push(Head clause) {
    cnt++;
    heap[cnt] = clause;
    filterUp();
}

Head MinHeap::top() {
    return heap[1];
}

bool MinHeap::empty() const {
    return !cnt;
}

int MinHeap::size() const {
    return cnt;
}

int MinHeap::cap() const{
    return capacity;
}

void MinHeap::print(){
    printf("\n\n****************************\n");
    for(int i = 1; i <= cnt; i++){
        printf("%d: ", heap[i].num);
        for(Data *j = heap[i].next_data; j != nullptr; j = j ->next_data){
            printf("%d ", j -> data);
        }
        printf("\n");
    }
    printf("\n****************************\n\n");
}

void MinHeap::del(int index){
    swap(heap[index], heap[cnt]);
    cnt --;
    filterDown(index);
}
