//
// Created by ted on 2022/8/21.
//

#include "head/head.h"
#include "head/cnfparser.h"
#include "head/solver.h"
#include "head/initsudoku.h"
#include <head/heap.h>

void printAns(bool flag, int* ans,int var_num){
    printf("%d\n",flag);
    for(int i=1; i<=var_num; i++){
        printf("%d ", ans[i]);
    }
    printf("\n");
}

void functionSAT(const string& cnf_file_path){
    clock_t start_time, end_time;
    start_time = clock();
    int var_num = 0;
    MinHeap heap = parse(var_num, cnf_file_path);
    int* ans = new int[var_num + 1];
    memset(ans, 0, sizeof (int) * (var_num + 1));
    printAns(DPLL(heap, ans), ans, var_num);
    end_time = clock();
    printf("time = %ld ms\n",end_time - start_time);
}

void functionTwodoku(){
    initTwodoku();
}

void display(){
    while(true){
        printf("Please choose a function\n");
        printf("1.SAT          2.twodoku\n");
        string choose;
        cin >> choose;
        if(choose == "1"){
            printf("Please input a file_path\n");
            string file_path;
            cin >> file_path;
            functionSAT(file_path);
            break;
        }
        else if(choose == "2"){
            functionTwodoku();
            break;
        }
        else{
            printf("Invalid input\n");
            continue;
        }
    }
}

int main(){
//    string cnf_file_path = R"(..\lib\ec-iso-ukn009.shuffled-as.sat05-3632-1584.cnf)";
//    string cnf_file_path = R"(../lib/small/tst_v25_c100.cnf)";
//    ..\lib\test.cnf
    display();
//    initTwodoku();
    return 0;
}