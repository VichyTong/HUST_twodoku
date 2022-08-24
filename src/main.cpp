//
// Created by ted on 2022/8/21.
//

#include "head/head.h"
#include "head/cnfparser.h"
#include "head/solver.h"
#include "head/initsudoku.h"

void printAns(bool flag, int* ans,int var_num){
    printf("%d\n",flag);
    for(int i=1; i<=var_num; i++){
        printf("%d ", ans[i]);
    }
    printf("\n");
}

int main(){
//    string cnf_file_path = R"(..\lib\small\tst_v25_c100.cnf)";
//    clock_t start_time, end_time;
//    start_time = clock();
//    int var_num = 0;
//    Head* linked_list = parse(var_num, cnf_file_path);
//    int* ans = new int[var_num + 1];
//    memset(ans, 0, sizeof (int) * (var_num + 1));
//    printAns(DPLL(linked_list, ans), ans, var_num);
//    end_time = clock();
//    printf("time = %ld ms\n",end_time - start_time);
    initTwodoku();
    return 0;
}