#include "Louvain.h"
#include <set>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Louvain::Louvain(){
    ifstream dataFile;
    dataFile.open("nodelist.txt", ios::in);
    set<int> nodeIndex;
    char x;
    dataFile >> x;
    dataFile.close();
}