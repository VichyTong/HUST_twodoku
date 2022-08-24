//
// Created by ted on 2022/8/22.
//

#include "head/initsudoku.h"
#include "head/head.h"
#include "head/cnfparser.h"
#include "head/linkedlist.h"
#include "head/solver.h"

bool row[10][10], col[10][10], block[10][10];
int board[10][10];
bool mark[2][10][10], twodoku_row[2][10][10], twodoku_col[2][10][10], twodoku_block[2][10][10];
int sudoku_A[10][10], sudoku_B[10][10];
const int las_vegas_param = 11;

void clearAll(){
    memset(row, 0, sizeof row);
    memset(col, 0, sizeof col);
    memset(block, 0, sizeof block);
    memset(board, 0, sizeof board);
}

int getRand(){
    random_device dev;
    mt19937 engine(dev());
    uniform_int_distribution<int> distribution(1, 9);
    return distribution(engine);
}

int blockNum(int x, int y){
    return (x - 1) / 3 * 3 + (y - 1) / 3 + 1;
}

bool checkLegal(int x, int y, int p){
    return (!row[x][p] && !col[y][p] && !block[blockNum(x, y)][p]);
}

void setNum(int x, int y, int p){
    row[x][p] = true;
    col[y][p] = true;
    block[blockNum(x, y)][p] = true;
    board[x][y] = p;
}

void fillBoard(const int* ans){
    for(int i = 1; i <= 729; i++){
        if(ans[i]){
            int x, y, z;
            z = (i - 1) % 9 + 1;
            y = ((i - 1) / 9) % 9 + 1;
            x = (((i - 1) / 9) / 9) % 9 + 1;
            board[x][y] = z;
        }
    }
}

void initLasVegas(){
    int k = las_vegas_param;
    while(k) {
        int x = getRand(), y = getRand();
        if (board[x][y]) {
            continue;
        }
        int p = getRand();
        if(checkLegal(x, y, p)){
            setNum(x, y, p);
            k --;
        }
    }
    int var_num = 0;
    Head* linked_list = parse(var_num, initSudokuCnfFile(11));
    int* ans = new int[var_num + 1];
    memset(ans, 0, sizeof(int) * (var_num + 1));
    if(!DPLL(linked_list, ans)){
        printf("Init failed.\n");
    }
    fillBoard(ans);
}

int getNaturalID(int cnt, int x, int y, int z){
    return (cnt - 1) * 729 + (x - 1) * 81 + (y - 1) * 9 + z;
}

void outputRestriction(int cnt, ofstream &output){
    //single cell

    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            for(int k = 1; k <= 9; k++){
                output << getNaturalID(cnt, i, j, k) << " ";
            }
            output << 0 << endl;
        }
    }
    for(int i = 1; i <= 9 ; i ++){
        for(int j = 1; j <= 9; j ++){
            for(int x = 1; x < 9; x ++){
                for(int y = x + 1; y <= 9; y ++){
                    output << "-" << getNaturalID(cnt, i, j, x) << " -" << getNaturalID(cnt, i, j, y) << " " << 0 << endl;
                }
            }
        }
    }

    // row

    for(int i = 1; i <= 9; i ++){
        for(int k = 1; k <= 9; k ++){
            for(int j = 1; j <= 9; j ++){
                output << getNaturalID(cnt, i, j, k) << " ";
            }
            output << 0 << endl;
        }
    }
    for(int i = 1; i <= 9; i ++){
        for(int k = 1; k <= 9; k++){
            for(int x = 1; x < 9; x ++){
                for(int y = x + 1; y <= 9 ; y ++){
                    output << "-" << getNaturalID(cnt, i, x, k) << " -" << getNaturalID(cnt, i, y, k) << " " << 0 << endl;
                }
            }
        }
    }

    //column

    for(int j = 1; j <= 9; j ++){
        for(int k = 1; k <= 9; k ++){
            for(int i = 1; i <= 9; i ++){
                output << getNaturalID(cnt, i, j, k) << " ";
            }
            output << 0 << endl;
        }
    }
    for(int j = 1; j <= 9; j ++){
        for(int k = 1; k <= 9; k++){
            for(int x = 1; x < 9; x ++){
                for(int y = x + 1; y <= 9 ; y ++){
                    output << "-" << getNaturalID(cnt, x, j, k) << " -" << getNaturalID(cnt, y, j, k)<< " " << 0 << endl;
                }
            }
        }
    }

    //block

    for(int blk = 1; blk <= 9 ; blk ++){
        for(int i = ((blk - 1) / 3) * 3 + 1; i <= ((blk - 1) / 3 + 1) * 3; i ++){
            for(int j = ((blk - 1) % 3) * 3 + 1; j <= ((blk - 1) % 3 + 1) * 3; j ++){
                for(int k = 1; k <= 9; k ++){
                    output << getNaturalID(cnt, i, j, k) << " ";
                }
                output << 0 << endl;
            }
        }
    }
    for(int blk = 1; blk <= 9 ; blk ++){
        int x0 = ((blk - 1) / 3) * 3 + 1, y0 = ((blk - 1) % 3) * 3 + 1;
        int x1 = x0 + 2, y1 = y0 + 2;
        for(int i = x0; i <= x1; i ++){
            for(int j = y0; j <= y1; j ++){
                for(int y = j + 1; y <= y1; y++) {
                    for (int k = 1; k <= 9; k++) {
                        output << "-" << getNaturalID(cnt, i, j, k)<< " -" << getNaturalID(cnt, i, y, k)<< " " << 0 << endl;
                    }
                }
                for(int x = i + 1; x <= x1; x++){
                    for(int y = y0; y <= y1; y++){
                        for(int k =1; k <= 9; k++){
                            output << "-" << getNaturalID(cnt, i, j, k) << " -" << getNaturalID(cnt, x, y, k) << " " << 0 << endl;
                        }
                    }
                }
            }
        }
    }

    //const numbers

    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            if(board[i][j]){
                output << getNaturalID(cnt, i, j, board[i][j]) << " " << 0 << endl;
            }
        }
    }
}

string initSudokuCnfFile(int num){
    int var_num = 729, clause_num = 11988 + num;
    ofstream output;
    output.open("../lib/sudoku.cnf", ios::out);
    output << "p cnf " << var_num << " " << clause_num << endl;
    outputRestriction(1, output);
    string file_path = "../lib/sudoku.cnf";
    output.close();
    return file_path;
}

string initTwodokuCnfFile(int num){
    int var_num = 1458, clause_num = 24138 + num;
    ofstream output;
    output.open("../lib/twodoku.cnf", ios::out);
    output << "p cnf " << var_num << " " << clause_num << endl;

    memcpy(board, sudoku_A, sizeof board);
    outputRestriction(1, output);
    memcpy(board, sudoku_B, sizeof board);
    outputRestriction(2, output);

    // overlapping part

    for(int i = 7; i <= 9; i ++){
        for(int j = 7; j <= 9; j ++){
            int x = i - 6, y = j - 6;
            for(int k = 1; k <= 9; k ++){
                int ID1 = getNaturalID(1, i, j, k);
                int ID2 = getNaturalID(2, x, y, k);
                output << -ID1 << " " << ID2 << " 0" << endl;
                output << ID1 << " " << -ID2 << " 0" << endl;
            }
        }
    }

    string file_path = "../lib/twodoku.cnf";
    return file_path;
}

bool isOverlappingPart(int p, int x, int y){
    if(p == 0){
        return (7 <= x && x <= 9 && 7 <= y && y <= 9);
    }
    else{
        return (1 <= x && x <= 3 && 1 <= y && y <= 3);
    }
}

void twodokuCreateRestriction(){
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j<= 9; j++){
            int data = sudoku_A[i][j];
            twodoku_row[0][i][data] = true;
            twodoku_col[0][j][data] = true;
            twodoku_block[0][blockNum(i, j)][data] = true;
        }
    }
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j<= 9; j++){
            int data = sudoku_B[i][j];
            twodoku_row[1][i][data] = true;
            twodoku_col[1][j][data] = true;
            twodoku_block[1][blockNum(i, j)][data] = true;
        }
    }
}

bool twodokuCheckLegal(int p, int x, int y, int z){
    return (!twodoku_row[p][x][z] && !twodoku_col[p][y][z] && !twodoku_block[p][blockNum(x, y)][z]);
}

void twodokuDelete(int p, int x, int y, int z){
    if(p == 0){
        sudoku_A[x][y] = 0;
    }
    else{
        sudoku_B[x][y] = 0;
    }
    twodoku_row[p][x][z] = false;
    twodoku_col[p][y][z] = false;
    twodoku_block[p][blockNum(x, y)][z] = false;
}

void twodokuSet(int p, int x, int y, int z){
    if(p == 0){
        sudoku_A[x][y] = z;
    }
    else{
        sudoku_B[x][y] = z;
    }
    twodoku_row[p][x][z] = true;
    twodoku_col[p][y][z] = true;
    twodoku_block[p][blockNum(x, y)][z] = true;
}

bool tryDig(int p, int x, int y, int left_cell){
    if(p == 0){
        int data = sudoku_A[x][y];
        twodokuDelete(p, x, y, data);
        for(int i = 1; i <= 9; i ++){
            if(i == data){
                continue;
            }
            if(!twodokuCheckLegal(p, x, y, i)){
                continue;
            }
            sudoku_A[x][y] = i;
            int var_num;
            Head* linked_list = parse(var_num, initTwodokuCnfFile(left_cell));
            int* ans = new int[var_num + 1];
            memset(ans, 0, sizeof (int) * (var_num + 1));
            if(DPLL(linked_list, ans)){
                twodokuSet(0, x, y, data);
                return false;
            }
            sudoku_A[x][y] = 0;
        }
    }
    else{
        int data = sudoku_B[x][y];
        twodokuDelete(p, x, y, data);
        for(int i = 1; i <= 9; i ++){
            if(i == data){
                continue;
            }
            if(!twodokuCheckLegal(p, x, y, i)){
                continue;
            }
            sudoku_B[x][y] = i;
            int var_num;
            Head* linked_list = parse(var_num, initTwodokuCnfFile(left_cell));
            int* ans = new int[var_num + 1];
            memset(ans, 0, sizeof (int) * (var_num + 1));
            if(DPLL(linked_list, ans)){
                twodokuSet(0, x, y, data);
                return false;
            }
            sudoku_B[x][y] = 0;
        }
    }
    return true;
}

void digHole(int num){
    int cnt = 0, left_cell = 162;
    twodokuCreateRestriction();
    while(num > 0){
        if(cnt == 162){
            break;
        }
        int p = getRand() % 2, x = getRand(), y = getRand();
        if(p == 0 && !sudoku_A[x][y]){
            continue;
        }
        if(p == 1 && !sudoku_B[x][y]){
            continue;
        }
        if(mark[p][x][y]){
            continue;
        }
        if(tryDig(p, x, y, left_cell)){
            if(isOverlappingPart(p, x, y)){
                if(p == 0){
                    twodokuDelete(1, x - 6, y - 6, sudoku_B[x - 6][y - 6]);
                }
                else{
                    twodokuDelete(0, x + 6, y + 6, sudoku_A[x + 6][y + 6]);
                }
                num -= 2;
                cnt += 2;
                left_cell -= 2;
            }
            else{
                num --;
                cnt ++;
                left_cell --;
            }
        }
        else{
            if(isOverlappingPart(p, x, y)){
                if(p == 0){
                    mark[0][x][y] = true;
                    mark[1][x - 6][y - 6] = true;
                }
                else{
                    mark[0][x + 6][y + 6] = true;
                    mark[1][x][y] = true;
                }
                cnt += 2;
            }
            else{
                mark[p][x][y] = true;
                cnt ++;
            }
        }
    }
}

void outputTwodoku(){
    ofstream output;
    output.open("../lib/twodoku/puzzle.txt", ios::out);
    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            output << sudoku_A[i][j] << " ";
        }
        output << endl;
    }
    output << endl;
    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            output << sudoku_B[i][j] << " ";
        }
        output << endl;
    }
    output.close();
}

void outputAnswer(){
    ofstream output;
    output.open("../lib/twodoku/answer.txt", ios::out);
    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            output << sudoku_A[i][j] << " ";
        }
        output << endl;
    }
    output << endl;
    for(int i = 1; i <= 9; i ++){
        for(int j = 1; j <= 9; j ++){
            output << sudoku_B[i][j] << " ";
        }
        output << endl;
    }
    output.close();
}
void initTwodoku(){
    clearAll();
    initLasVegas();
    memcpy(sudoku_A, board, sizeof board);
    clearAll();
    for(int i = 7; i <= 9; i++){
        for(int j = 7; j <= 9; j++){
            board[i - 6][j - 6] = sudoku_A[i][j];
        }
    }
    int var_num = 0;
    Head* linked_list = parse(var_num, initSudokuCnfFile(9));
    int* ans = new int[var_num + 1];
    memset(ans, 0, sizeof(int) * (var_num + 1));
    if(!DPLL(linked_list, ans)){
        printf("Init failed.\n");
    }
    fillBoard(ans);
    memcpy(sudoku_B, board, sizeof board);
    outputAnswer();
    digHole(92);
    outputTwodoku();
}