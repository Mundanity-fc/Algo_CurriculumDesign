#include <iostream>
#include <set>
#include <vector>
#include "Sudoku.h"

using namespace std;

int main() {
    set<int> s;
    int a[] = {1,2,3,4,5,6,7,8,9};
    s = set<int>(a,a+9);
    bool f = s.count(1);
    s.erase(1);
    f = s.count(1);
    s.erase(1);
    set<int>::iterator x;
    x = s.find(99);
    int su[9][9] = {{3,0,6,5,0,8,4,0,1},
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

    return 0;
}
