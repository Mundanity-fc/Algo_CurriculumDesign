#ifndef ALGO_CURRICULUMDESIGN_SUDOKU_H
#define ALGO_CURRICULUMDESIGN_SUDOKU_H

#include <vector>
#include <set>

using namespace std;

class Sudoku {
    /* 数独棋盘定义
     *  Col                  ┌─────────────────────┐
     *   │                   │                     │
     *   │                   │                     │
     *   v                   v                     │
     * ┌─────────┬─────────┬─────────┐             │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │ <─── Row    │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │             │
     * │ 0  0  0 │ 0  0  0 │ 0  0  0 │ <───────────┴──────── Block
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
    // 结果数组
    vector<vector<vector<int>>> result;
    // 全局计数器
    int count;
    // 从数集num中去除该行、列、块下所有已有数字
    void deduplication(int rowNum, int colNum, set<int> &num);
    // 数独内容输出标准
    void SudokuOut(vector<vector<int>> outMap);

public:
    Sudoku();

    // 加载数独内容
    void initialMap(int initialMap[9][9]);
    // 输出当前数独内容
    void printMap();
    // 搜索回溯算法
    bool search();
    // 全局冲突检查，调用行、列、块冲突检查实现
    bool checkConflict();
    // 行冲突检查
    bool checkRowConflict(int rowNum);
    // 列冲突检查
    bool checkColConflict(int colNum);
    // 块冲突检查
    bool checkBlockConflict(int rowNum, int colNum);
    // 数独完成检测
    bool checkFinish();
    // 结果输出
    void output();
};

#endif