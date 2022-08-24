//
// Created by ted on 2022/8/21.
//
#include "head/cnfparser.h"

//string cnf_file_path = R"(..\lib\ec-iso-ukn009.shuffled-as.sat05-3632-1584.cnf)";
Head* parse(int &var_num, const string& cnf_file_path){
    ifstream input;
    input.open(cnf_file_path,ios::in);
    if(!input.is_open()) {
        cout << "Failed to read cnf file." << endl;
        exit(-1);
    }
    char type;
    string line;
    input >> type;
    while(type != 'p'){
        getline(input, line);
        input >> type;
    }
    string tmp;
    int clause_num = 0;
    input >> tmp >> var_num >> clause_num;
    Head* linked_list = nullptr;
    for(int i = 1; i <= clause_num; i++){
        Head* new_clause = new Head;
        addHead(linked_list, new_clause);
        int literal = 0;
        input >> literal;
        while(literal != 0){
            Data* new_data = new Data;
            new_data -> data = literal;
            addData(new_clause, new_data);
            input >> literal;
        }
    }
    return linked_list;
}