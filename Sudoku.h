#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#endif //SUDOKU_SUDOKU_H

#include <vector>
#include <set>

using namespace std;

class Sudoku {
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

public:
    Sudoku() {
        // 数独合法数字集合初始化
        int numList[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        this->sudokuSet = set<int>(numList, numList + 9);
        // 数独棋盘初始化
        this->map = vector<vector<int>>(9, vector<int>(9));
    }

    void initialMap(int initialMap[9][9]);

    void printMap();

    void solveQuiz();

    // 全局冲突检查，调用行、列、块冲突检查实现
    bool checkConflict();

    // 行冲突检查
    bool checkRowConflict(int rowNum);

    // 列冲突检查
    bool checkColConflict(int colNum);

    // 块冲突检查
    bool checkBlockConflict(int rowNum, int colNum);
};

bool Sudoku::checkConflict() {

    return false;
}

bool Sudoku::checkRowConflict(int rowNum) {
    set<int> Num = this->sudokuSet;
    for (int i = 0; i < 9; ++i) {
        // 有0即暂无空位，不进行冲突检测
        if (this->map[rowNum][i] == 0)
            continue;

        // 当集合中存在检查的元素，则从集合中删去该数字，若不存在，则该数冲突
        if (Num.count(map[rowNum][i]))
            Num.erase(map[rowNum][i]);
        else
            return true;
    }

    return false;
}

bool Sudoku::checkColConflict(int colNum) {
    set<int> Num = this->sudokuSet;
    for (int i = 0; i < 9; ++i) {
        // 有0即暂无空位，不进行冲突检测
        if (this->map[i][colNum] == 0)
            continue;

        // 当集合中存在检查的元素，则从集合中删去该数字，若不存在，则该数冲突
        if (Num.count(map[i][colNum]))
            Num.erase(map[i][colNum]);
        else
            return true;
    }
    return false;
}

bool Sudoku::checkBlockConflict(int rowNum, int colNum) {
    set<int> Num = this->sudokuSet;
    vector<int> rowArray(3), colArray(3);
    if (rowNum <= 2)
        rowArray = {0, 1, 2};
    else if (rowNum <= 5)
        rowArray = {3, 4, 5};
    else
        rowArray = {6, 7, 8};

    if (colNum <= 2)
        colArray = {0, 1, 2};
    else if (colNum <= 5)
        colArray = {3, 4, 5};
    else
        colArray = {6, 7, 8};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->map[rowArray[i]][colArray[j]] == 0)
                continue;

            if (Num.count(map[rowArray[i]][colArray[j]]))
                Num.erase(map[rowArray[i]][colArray[j]]);
            else
                return true;
        }
    }

    return false;
}

void Sudoku::initialMap(int initialMap[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            this->map[i][j] = initialMap[i][j];
        }
    }
}

void Sudoku::printMap() {
    cout << "目前数独的状态如下：\n";
    cout << "┌─────────┬─────────┬─────────┐\n";
    cout << "│ " << this->map[0][0] << "  " << this->map[0][1] << "  " << this->map[0][2] << " │ ";
    cout << this->map[0][3] << "  " << this->map[0][4] << "  " << this->map[0][5] << " │ ";
    cout << this->map[0][6] << "  " << this->map[0][7] << "  " << this->map[0][8] << " " << "│\n";
    cout << "│ " << this->map[1][0] << "  " << this->map[1][1] << "  " << this->map[1][2] << " │ ";
    cout << this->map[1][3] << "  " << this->map[1][4] << "  " << this->map[1][5] << " │ ";
    cout << this->map[1][6] << "  " << this->map[1][7] << "  " << this->map[1][8] << " " << "│\n";
    cout << "│ " << this->map[2][0] << "  " << this->map[2][1] << "  " << this->map[2][2] << " │ ";
    cout << this->map[2][3] << "  " << this->map[0][4] << "  " << this->map[2][5] << " │ ";
    cout << this->map[2][6] << "  " << this->map[0][7] << "  " << this->map[2][8] << " " << "│\n";
    cout << "├─────────┼─────────┼─────────┤\n";
    cout << "│ " << this->map[3][0] << "  " << this->map[3][1] << "  " << this->map[3][2] << " │ ";
    cout << this->map[3][3] << "  " << this->map[3][4] << "  " << this->map[3][5] << " │ ";
    cout << this->map[3][6] << "  " << this->map[3][7] << "  " << this->map[3][8] << " " << "│\n";
    cout << "│ " << this->map[4][0] << "  " << this->map[4][1] << "  " << this->map[4][2] << " │ ";
    cout << this->map[4][3] << "  " << this->map[4][4] << "  " << this->map[4][5] << " │ ";
    cout << this->map[4][6] << "  " << this->map[4][7] << "  " << this->map[4][8] << " " << "│\n";
    cout << "│ " << this->map[5][0] << "  " << this->map[5][1] << "  " << this->map[5][2] << " │ ";
    cout << this->map[5][3] << "  " << this->map[5][4] << "  " << this->map[5][5] << " │ ";
    cout << this->map[5][6] << "  " << this->map[5][7] << "  " << this->map[5][8] << " " << "│\n";
    cout << "├─────────┼─────────┼─────────┤\n";
    cout << "│ " << this->map[6][0] << "  " << this->map[6][1] << "  " << this->map[6][2] << " │ ";
    cout << this->map[6][3] << "  " << this->map[6][4] << "  " << this->map[6][5] << " │ ";
    cout << this->map[6][6] << "  " << this->map[6][7] << "  " << this->map[6][8] << " " << "│\n";
    cout << "│ " << this->map[7][0] << "  " << this->map[7][1] << "  " << this->map[7][2] << " │ ";
    cout << this->map[7][3] << "  " << this->map[7][4] << "  " << this->map[7][5] << " │ ";
    cout << this->map[7][6] << "  " << this->map[7][7] << "  " << this->map[7][8] << " " << "│\n";
    cout << "│ " << this->map[8][0] << "  " << this->map[8][1] << "  " << this->map[8][2] << " │ ";
    cout << this->map[8][3] << "  " << this->map[8][4] << "  " << this->map[8][5] << " │ ";
    cout << this->map[8][6] << "  " << this->map[8][7] << "  " << this->map[8][8] << " " << "│\n";
    cout << "└─────────┴─────────┴─────────┘\n";
}

void Sudoku::solveQuiz() {

}
