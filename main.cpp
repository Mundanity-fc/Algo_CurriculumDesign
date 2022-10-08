#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> map;
    map = vector<vector<int>>(9, vector<int>(9));
    set<int> s;
    int a[] = {1,2,3,4,5,6,7,8,9};
    s = set<int>(a,a+9);
    set<int>::iterator x;
    x = s.find(99);
    map[0][0] = 1;
    map[0][1] = 1;
    map[0][2] = 1;
    map[1][0] = 2;
    map[2][0] = 2;
    vector<vector<int>>::iterator x1 = map.begin();
    vector<int>::iterator x2=(*x1).begin();
    cout << "0\n";
    return 0;
}
