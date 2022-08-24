//
// Created by ted on 2022/8/22.
//

#ifndef HUST_TWODOKU_SOLVER_H
#define HUST_TWODOKU_SOLVER_H

#include "head/linkedlist.h"

void simplify(Head* &linked_list, int num);
Head* findSingleClause(Head* linked_list);
bool hasEmptyClause(Head* linked_list);
Head* createSingleClause(int v);
bool DPLL(Head* linked_list, int* ans);

#endif //HUST_TWODOKU_SOLVER_H
