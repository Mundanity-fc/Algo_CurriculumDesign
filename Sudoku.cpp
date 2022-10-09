#include <iostream>
#include <vector>
#include <set>
#include "Sudoku.h"

using namespace std;

void Sudoku::initialMap(int initialMap[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            this->map[i][j] = initialMap[i][j];
        }
    }
}

bool Sudoku::checkConflict() {
    // 总体冲突检测
    for (int i = 0; i < 9; ++i) {
        // 行列冲突
        if (this->checkRowConflict(i))
            return true;
        if (this->checkColConflict(i))
            return true;

        // 块冲突
        if (i % 3 == 0) {
            if (this->checkBlockConflict(i, 0))
                return true;
            if (this->checkBlockConflict(i, 3))
                return true;
            if (this->checkBlockConflict(i, 6))
                return true;
        }
    }
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

    // 确认块坐标
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

    // 进行块检测
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

bool Sudoku::checkFinish() {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (this->map[i][j] == 0)
                return false;
    return true;
}

void Sudoku::SudokuOut(vector<vector<int>> outMap) {
    cout << "┌─────────┬─────────┬─────────┐\n";
    cout << "│ " << outMap[0][0] << "  " << outMap[0][1] << "  " << outMap[0][2] << " │ ";
    cout << outMap[0][3] << "  " << outMap[0][4] << "  " << outMap[0][5] << " │ ";
    cout << outMap[0][6] << "  " << outMap[0][7] << "  " << outMap[0][8] << " " << "│\n";
    cout << "│ " << outMap[1][0] << "  " << outMap[1][1] << "  " << outMap[1][2] << " │ ";
    cout << outMap[1][3] << "  " << outMap[1][4] << "  " << outMap[1][5] << " │ ";
    cout << outMap[1][6] << "  " << outMap[1][7] << "  " << outMap[1][8] << " " << "│\n";
    cout << "│ " << outMap[2][0] << "  " << outMap[2][1] << "  " << outMap[2][2] << " │ ";
    cout << outMap[2][3] << "  " << outMap[2][4] << "  " << outMap[2][5] << " │ ";
    cout << outMap[2][6] << "  " << outMap[2][7] << "  " << outMap[2][8] << " " << "│\n";
    cout << "├─────────┼─────────┼─────────┤\n";
    cout << "│ " << outMap[3][0] << "  " << outMap[3][1] << "  " << outMap[3][2] << " │ ";
    cout << outMap[3][3] << "  " << outMap[3][4] << "  " << outMap[3][5] << " │ ";
    cout << outMap[3][6] << "  " << outMap[3][7] << "  " << outMap[3][8] << " " << "│\n";
    cout << "│ " << outMap[4][0] << "  " << outMap[4][1] << "  " << outMap[4][2] << " │ ";
    cout << outMap[4][3] << "  " << outMap[4][4] << "  " << outMap[4][5] << " │ ";
    cout << outMap[4][6] << "  " << outMap[4][7] << "  " << outMap[4][8] << " " << "│\n";
    cout << "│ " << outMap[5][0] << "  " << outMap[5][1] << "  " << outMap[5][2] << " │ ";
    cout << outMap[5][3] << "  " << outMap[5][4] << "  " << outMap[5][5] << " │ ";
    cout << outMap[5][6] << "  " << outMap[5][7] << "  " << outMap[5][8] << " " << "│\n";
    cout << "├─────────┼─────────┼─────────┤\n";
    cout << "│ " << outMap[6][0] << "  " << outMap[6][1] << "  " << outMap[6][2] << " │ ";
    cout << outMap[6][3] << "  " << outMap[6][4] << "  " << outMap[6][5] << " │ ";
    cout << outMap[6][6] << "  " << outMap[6][7] << "  " << outMap[6][8] << " " << "│\n";
    cout << "│ " << outMap[7][0] << "  " << outMap[7][1] << "  " << outMap[7][2] << " │ ";
    cout << outMap[7][3] << "  " << outMap[7][4] << "  " << outMap[7][5] << " │ ";
    cout << outMap[7][6] << "  " << outMap[7][7] << "  " << outMap[7][8] << " " << "│\n";
    cout << "│ " << outMap[8][0] << "  " << outMap[8][1] << "  " << outMap[8][2] << " │ ";
    cout << outMap[8][3] << "  " << outMap[8][4] << "  " << outMap[8][5] << " │ ";
    cout << outMap[8][6] << "  " << outMap[8][7] << "  " << outMap[8][8] << " " << "│\n";
    cout << "└─────────┴─────────┴─────────┘\n";
}

void Sudoku::printMap() {
    cout << "目前数独的状态如下：\n";
    this->SudokuOut(this->map);
}

bool Sudoku::search() {
    cout << "第" << ++this->count << "次执行search\n";
    // 每次开始前进行完成度检测，避免无效遍历
    if (this->checkFinish()) {
        // 数独完成且无冲突情况，记录为正确结果，进行结果输出并保存
        if (not this->checkConflict()) {
            cout << "发现一个结果\n";
            this->result.push_back(this->map);
            this->printMap();
            /*
             * cout << "键入回车以继续：";
             * getchar();
             */
        }
        // 数独完成时，该次搜索不进行，直接返回上层递归
        return false;
    }

    // 搜索主体
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            // 跳过已有数字，寻找上层遍历进行后数独中存在的第一个空位
            if (this->map[i][j] != 0)
                continue;

            // 数字为 0 时，表示为空格，开始建立搜索环境

            // 建立一个数字集合
            set<int> num = this->sudokuSet;

            // 从数字集中去除该坐标同行、同列、同块下所有已有数字
            this->deduplication(i, j, num);

            // 递归执行该位置剩余所有可能数字
            while (!num.empty()) {
                // 取出集合中第一个元素
                this->map[i][j] = *num.begin();
                // 从集合中去除取出的数字
                num.erase(num.begin());
                // 进行下次递归
                this->search();
            }

            // 搜索结束返回上层时，需要将本层搜索结果清除
            this->map[i][j] = 0;

            // 返回上层递归
            return false;
        }
    }
    return false;
}

void Sudoku::deduplication(int rowNum, int colNum, set<int> &num) {
    vector<int> rowArray(3), colArray(3);
    // 确定块坐标
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

    // 去除行列内重复元素
    for (int i = 0; i < 9; ++i) {
        if (num.count(this->map[rowNum][i]))
            num.erase(this->map[rowNum][i]);
        if (num.count(this->map[i][colNum]))
            num.erase(this->map[i][colNum]);
    }

    // 去除块内重复元素
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (num.count(this->map[rowArray[i]][colArray[j]]))
                num.erase(this->map[rowArray[i]][colArray[j]]);
}

void Sudoku::output() {
    cout << "共找到 " << this->result.size() << " 个结果，结果如下：\n";
    // 依次输出所有结果
    for (auto &i: this->result) {
        this->SudokuOut(i);
        cout << endl;
    }
}