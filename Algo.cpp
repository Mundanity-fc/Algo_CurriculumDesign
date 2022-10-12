#include <iostream>
#include "Sudoku.h"
#include "Louvain.h"

using namespace std;

int run_Sudoku() {
//    int su[9][9] = {{3,0,6,5,0,8,4,0,0},
//                    {5,2,0,0,0,0,0,0,0},
//                    {0,8,7,0,0,0,0,3,1},
//                    {0,0,3,0,1,0,0,8,0},
//                    {9,0,0,8,6,3,0,0,5},
//                    {0,5,0,0,9,0,6,0,0},
//                    {1,3,0,0,0,0,2,5,0},
//                    {0,0,0,0,0,0,0,7,4},
//                    {0,0,5,2,0,6,3,0,0}};
    int su[9][9] = {{0,0,0,3,0,1,0,0,0},
                    {0,1,2,0,0,0,9,3,0},
                    {9,8,0,0,0,0,0,6,1},
                    {0,0,9,1,7,2,3,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,7,5,6,9,8,0,0},
                    {5,9,0,0,0,0,0,7,3},
                    {0,6,1,0,0,0,5,4,0},
                    {0,0,0,9,0,3,0,0,0}};
    Sudoku Su;
    Su.initialMap(su);
    Su.printMap();
    cout << "键入回车开始搜索：\n";
    getchar();
    Su.search();
    Su.output();
    return 0;
}

int run_Louvain(){
    Louvain louvain;
    louvain.printNet();
    louvain.runLouvain();
    return 0;
}


int main(){
    //run_Sudoku();
    run_Louvain();
    return 0;
}
