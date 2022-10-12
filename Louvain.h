#ifndef ALGO_CURRICULUMDESIGN_LOUVAIN_H
#define ALGO_CURRICULUMDESIGN_LOUVAIN_H

#include <vector>
#include <set>

using namespace std;

struct Edge{
    int ID;
    char Type;
};

// 网络中的社区
struct Community{
    set<int> Index;
    vector<int> NodeList;
};

// 网络中的节点
struct Node{
    int ID;
    Community *Belonging;
    vector<Edge> Neighbor;
};

class Louvain {
private:
    // 节点列表，保存着网络中初始的节点信息
    vector<Node> nodeList;
    // 社区列表，在 Louvain 算法中不断地被更新
    vector<Community*> communityList;
    // 网络中所有边的权重和（由于为无权图，每条边权重为1）
    unsigned int edgeCount;

    // 计算目标节点/社区的 Φtot
    int getPhiTot(Node node);
    int getPhiTot(Community commu);


    // 计算目标节点/社区之间的 ki,in
    int getKiin(Node node1, Community node2);
    int getKiin(Community node1, Community node2);

    // 计算目标节点/社区的 kin
    int getKin(Node node);
    int getKin(Community commu);

public:
    Louvain();
    void nodeCombine();
    void communityCombine();
    void runLouvain();
    void printNet();
    void test();
};


#endif
