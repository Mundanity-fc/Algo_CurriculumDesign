//
// Created by mundanity on 22-8-27.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#endif //SUDOKU_SUDOKU_H

#include <vector>
#include <set>
using namespace std;

class Sudoku{
    /* 数独棋盘定义
     *  Col                  ┌─────────────────────┐
     *   │                   │                     │
     *   │                   │                     │
     *   ↓                   ↓                     │
     * ┌─────────┬─────────┬─────────┐             │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │ ←─── Row    │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │             │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │ ←───────────┴──────── Block
     * ├─────────┼─────────┼─────────┤
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │
     * ├─────────┼─────────┼─────────┤
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │
     * └─────────┴─────────┴─────────┘
     */
private:
    // 数独合法数字集合，即 1~9 的数字集合
    set<int> sudokuSet;
    // 数独棋盘
    vector<vector<int>> map;
    // 全局冲突检查，调用行、列、块冲突检查实现
    bool checkConflict();
    // 行冲突检查
    bool checkRowConflict(int rowNum);
    // 列冲突检查
    bool checkColConflict(int colNum);
    // 块冲突检查
    bool checkBlockConflict(int rowNum, int colNum);
    Sudoku(){
        // 数独合法数字集合初始化
        int numList[] = {1,2,3,4,5,6,7,8,9};
        this->sudokuSet = set<int>(numList, numList+9);
        // 数独棋盘初始化
        this->map = vector<vector<int>>(9, vector<int>(9));
    }

public:
    void initialMap();
    void printMap();
    void solveQuiz();
};

bool Sudoku::checkConflict() {

    return false;
}

bool Sudoku::checkRowConflict(int rowNum) {

    return false;
}

bool Sudoku::checkColConflict(int colNum) {

    return false;
}

bool Sudoku::checkBlockConflict(int rowNum, int colNum) {

    return false;
}

void Sudoku::initialMap() {

}

void Sudoku::printMap() {

}

void Sudoku::solveQuiz() {

}
