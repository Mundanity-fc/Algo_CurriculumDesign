#include "Louvain.h"
#include <set>
#include <fstream>
#include <iostream>

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

        // 建立\更新节点 1
        if (nodeIndex.count(node1) == 0) {
            Node node;
            Edge edge;
            // 将节点 id 塞入集合
            nodeIndex.insert(node1);
            // 建立新节点与边
            node.ID = node1;
            edge.ID = node2;
            edge.Type = 'O';
            node.Neighbor.push_back(edge);
            // 将节点塞入节点列表中
            this->nodeList.push_back(node);
        } else {
            for (auto &i: this->nodeList) {
                if (i.ID == node1) {
                    Edge edge;
                    edge.ID = node2;
                    edge.Type = 'O';
                    i.Neighbor.push_back(edge);
                    break;
                }
            }
        }

        // 建立\更新节点 2
        if (nodeIndex.count(node2) == 0) {
            Node node;
            Edge edge;
            // 将节点 id 塞入集合
            nodeIndex.insert(node2);
            // 建立新节点与边
            node.ID = node2;
            edge.ID = node1;
            edge.Type = 'I';
            node.Neighbor.push_back(edge);
            // 将节点塞入节点列表中
            this->nodeList.push_back(node);
        } else {
            for (auto &i: this->nodeList) {
                if (i.ID == node2) {
                    Edge edge;
                    edge.ID = node1;
                    edge.Type = 'I';
                    i.Neighbor.push_back(edge);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < this->nodeList.size(); ++i) {
        // 增加全图的权重合
        this->edgeCount += this->nodeList[i].Neighbor.size();
        // 初始化一个社区
        Community *commu = new Community();
        // 将每个节点放入初始化社区中
        (*commu).NodeList.push_back(i);
        // 修改节点的归属指针，便于所属社区的查找
        this->nodeList[i].Belonging = commu;
        this->communityList.push_back(*commu);
    }
    // 由于每条边在每个节点都有出、入边的存在，所以总边数被扩大了一倍，需要处理
    this->edgeCount /= 2;
    dataFile.close();
}

void Louvain::printNet() {
    cout << "目前，网络中有 "<< this->nodeList.size() << " 个节点，" << "有" << this->communityList.size() << " 个社区，其中所有的社区情况如下：\n";
    for (int i = 0; i < this->communityList.size(); ++i) {
        cout << "第 " << i << " 号网络中有 " << this->communityList[i].NodeList.size() << "个节点，分别为：";
        for (auto &j: this->communityList[i].NodeList)
            cout << " " << j;
        cout << endl;
    }
}


void Louvain::nodeCombine() {
    bool isChanged = true;
    while (isChanged){
        isChanged = false;
        for (int i = 0; i < this->nodeList.size(); ++i) {
            double preQ = this->getPreviousQ(this->nodeList[i]);
        }
    }
}

void Louvain::communityCombine() {

}

void Louvain::runLouvain() {
    this->nodeCombine();
    this->communityCombine();
}

template<typename Target>
int Louvain::getPhiTot(Target node){
    // 对于节点计算 Φtot
    if (typeid(node).name() == typeid(Node).name())
    {

        return 0;
    }

    // 对于社区计算 Φtot
    if (typeid(node).name() == typeid(Community).name()){
        return 0;
    }
};

template<typename Target>
int Louvain::getPhiIn(Target node){
    // 对于节点计算 Φin
    if (typeid(node).name() == typeid(Node).name())
    {

        return 0;
    }

    // 对于社区计算 Φin
    if (typeid(node).name() == typeid(Community).name()){
        return 0;
    }
};

template<typename Target>
int Louvain::getKiin(Node node, Target node2) {
    return 0;
}

int Louvain::getKin(Node node) {
    return 0;
}

template<typename Target>
double Louvain::getPreviousQ(Target node) {
    // 对于节点计算 Modularity
    if (typeid(node).name() == typeid(Node).name())
    {
        int Phi_In;
        for(int i = 0; i < node.Neighbor.size(); ++i)
            if (node.Neighbor[i].ID == node.ID)
                ++Phi_In;
        // 对于自身环，定义了出入两条边，所以总数需要除以 2
        Phi_In /= 2;

        return 0;
    }

    // 对于社区计算 Modularity
    if (typeid(node).name() == typeid(Community).name()){
        return 0;
    }
}



