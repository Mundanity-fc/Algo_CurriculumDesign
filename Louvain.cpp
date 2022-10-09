#include "Louvain.h"
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

Louvain::Louvain() {
    ifstream dataFile;
    dataFile.open("nodelist.txt", ios::in);
    set<int> nodeIndex;
    int node1 = 0;
    int node2 = 0;
    while (!dataFile.eof()) {
        dataFile >> node1;
        dataFile >> node2;

        // 建立/更新节点 1
        if (nodeIndex.count(node1) == 0) {
            Node node;
            // 将节点 id 塞入集合
            nodeIndex.insert(node1);
            // 建立新节点
            node.ID = node1;
            node.Neighbor.push_back(vector<int>{node2,1});
            // 将节点塞入节点列表中
            this->nodeList.push_back(node);
        } else {
            for (auto &i: this->nodeList) {
                if (i.ID == node1) {
                    // 若 node 2 已经在 node1 的邻表中，对边权重加 1
                    for (auto & j : i.Neighbor) {
                        if (j[0] == node2) {
                            j[1]++;
                            goto EstablishAnotherNode;
                        }
                    }
                    // 若不在，则建立新邻居
                    i.Neighbor.push_back(vector<int>{node2,1});
                    goto EstablishAnotherNode;
                }
            }
        }
        
        EstablishAnotherNode:
        // 建立/更新节点 2
        if (nodeIndex.count(node2) == 0) {
            Node node;
            // 将节点 id 塞入集合
            nodeIndex.insert(node2);
            // 建立新节点
            node.ID = node2;
            // 将节点加入其邻表中，且权重设为 1
            node.Neighbor.push_back(vector<int>{node1,1});
            // 将节点塞入节点列表中
            this->nodeList.push_back(node);
        } else {
            for (auto &i: this->nodeList) {
                if (i.ID == node2) {
                    // 若 node 1 已经在 node2 的邻表中，对边权重加 1
                    for (auto & j : i.Neighbor) {
                        if (j[0] == node1) {
                            j[1]++;
                            goto NextRead;
                        }
                    }
                    // 若不在，则建立新邻居
                    i.Neighbor.push_back(vector<int>{node1,1});
                    goto NextRead;
                }
            }
        }
        NextRead:
        continue;
    }
    for (auto &i: this->nodeList) {
        sort(i.Neighbor.begin(), i.Neighbor.end());
        Community commu;
        commu.NodeList.push_back(i);
        this->communityList.push_back(commu);
    }
    dataFile.close();
}

void Louvain::printNet() {
    cout << "目前，网络中有 " << this->communityList.size() << " 个社区，其中所有的社区情况如下：\n";
    for (int i = 0; i < this->communityList.size(); ++i) {
        cout << "第 " << i << " 号网络中有 " << this->communityList[i].NodeList.size() << "个节点，分别为：";
        for (auto &j: this->communityList[i].NodeList)
            cout << " " << j.ID;
        cout << endl;
    }
}
