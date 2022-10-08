#include <iostream>
#include <set>
#include "Sudoku.h"

using namespace std;

int main() {
    int su[9][9] = {{3,0,6,5,0,8,4,0,0},
                    {5,2,0,0,0,0,0,0,0},
                    {0,8,7,0,0,0,0,3,1},
                    {0,0,3,0,1,0,0,8,0},
                    {9,0,0,8,6,3,0,0,5},
                    {0,5,0,0,9,0,6,0,0},
                    {1,3,0,0,0,0,2,5,0},
                    {0,0,0,0,0,0,0,7,4},
                    {0,0,5,2,0,6,3,0,0}};
    Sudoku Su;
    Su.initialMap(su);
    Su.printMap();
    cout << "键入回车开始搜索：\n";
    getchar();
    Su.search();
    Su.output();
    return 0;
}
