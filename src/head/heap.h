//
// Created by ted on 2022/8/27.
//

#ifndef HUST_TWODOKU_HEAP_H
#define HUST_TWODOKU_HEAP_H

#include "head/head.h"

struct Data{
    int data = 0;
    Data *next_data{};
};

struct Head{
    int num = 0;
    Data *next_data{};

    bool operator < (const Head b) const{
        return this -> num < b.num;
    }
};

class MinHeap{
private:

    void filterDown(int start);
    void filterUp();
public:
    explicit MinHeap(int cap);
    ~MinHeap();

    void pop();
    Head top();
    void push(Head clause);
    bool empty() const;
    int cap() const;
    int size() const;
    void print();
    void del(int index);

    int cnt = 0;
    int capacity = 0;
    Head *heap = nullptr;
};

#endif //HUST_TWODOKU_HEAP_H
