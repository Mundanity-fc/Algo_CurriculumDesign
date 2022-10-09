#ifndef ALGO_CURRICULUMDESIGN_LOUVAIN_H
#define ALGO_CURRICULUMDESIGN_LOUVAIN_H

#include <vector>
#include <set>

using namespace std;

// 网络中的节点
struct Node{
    int ID;
    vector<int> Neighbor;
};

// 网络中的社区
struct Community{
    vector<Node> NodeList;
};

class Louvain {
private:
    // 节点列表，保存着网络中初始的节点信息
    vector<Node> nodeList;
    // 社区列表，在 Louvain 算法中不断地被更新
    vector<Community> communityList;

public:
    Louvain();
};


#endif
