//
// Created by ted on 2022/8/22.
//

#ifndef HUST_TWODOKU_INITSUDOKU_H
#define HUST_TWODOKU_INITSUDOKU_H

#include "head.h"

int getRand();
int blockNum(int x, int y);
bool checkLegal(int x, int y, int p);
void setNum(int x, int y, int p);
void initLasVegas();
int getNaturalID(int cnt, int x, int y, int z);
string initSudokuCnfFile(int num);
string initTwodokuCnfFile(int num);
void twodokuCreateRestriction();
bool twodokuCheckLegal(int p, int x, int y, int z);
void twodokuDelete(int p, int x, int y, int z);
void twodokuSet(int p, int x, int y, int z);
bool isOverlappingPart(int p, int x, int y);
void printBoard();
void initTwodoku();

#endif //HUST_TWODOKU_INITSUDOKU_H
