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
        (*commu).Index.insert(this->nodeList[i].ID);
        // 修改节点的归属指针，便于所属社区的查找
        this->nodeList[i].Belonging = commu;
        this->communityList.push_back(commu);
    }
    // 由于每条边在每个节点都有出、入边的存在，所以总边数被扩大了一倍，需要处理
    this->edgeCount /= 2;
    dataFile.close();
}

void Louvain::printNet() {
    int count = 0;
    cout << "目前，网络中有 " << this->nodeList.size() << " 个节点，" << "有 " << this->communityList.size()
         << " 个社区，其中所有的社区情况如下：\n";
    for (int i = 0; i < this->communityList.size(); ++i) {
        cout << "第 " << i << " 号网络中有 " << this->communityList[i]->NodeList.size() << " 个节点，分别为：";
        for (auto &j: this->communityList[i]->NodeList)
        {
            cout << " " << j;
            ++count;
        }
        cout << endl;
    }
    cout << "本次共检测到了 " << count << " 个节点，怎么回事呢？";
}


void Louvain::nodeCombine() {
    bool isChanged = true;
    while (isChanged) {
        isChanged = false;
        // 在所有网络中不断搜索
        for (int i = 0; i < this->communityList.size(); ++i) {
            // 对单节点社区进行操作
            if (this->communityList[i]->Index.size() == 1) {
                Node node = this->nodeList[this->communityList[i]->NodeList[0]];
                // 记录最大的 DeltaQ
                double maxQ = 0;
                // 记录有最大 DeltaQ 时移动到的邻居节点 ID
                int targetID = 0;
                // 检索所有邻边
                for (int j = 0; j < node.Neighbor.size(); ++j) {
                    int ID;
                    // 非自身指向邻边
                    ID = node.Neighbor[j].ID;
                    if (ID == node.ID)
                        continue;
                    // 获取计算参数
                    double m = this->edgeCount;
                    double ki = this->getKin(node);
                    double kiin = this->getKiin(node, *(this->nodeList[ID].Belonging));
                    double phitot = this->getPhiTot(node);
                    double deltaQ = kiin / m + 2 * ki * phitot / 4 * m * m;
                    if (deltaQ > maxQ) {
                        maxQ = deltaQ;
                        targetID = ID;
                    }
                }
                // 存在 DeltaQ 为正的情况
                if (maxQ > 0) {
                    // 修改变更标志
                    isChanged = true;
                    // 修改节点的归属指针
                    node.Belonging = this->nodeList[targetID].Belonging;
                    // 在新的社区 Index 目录中增加该节点
                    node.Belonging->Index.insert(node.ID);
                    // 在新的社区 NodeList 堆栈中增加该节点
                    node.Belonging->NodeList.push_back(node.ID);
                    // 将节点变更保存到 nodeList
                    this->nodeList[this->communityList[i]->NodeList[0]] = node;
                    // 从 communityList 中删除目前的空社区
                    vector<Community *>::iterator itor = this->communityList.begin() + i;
                    this->communityList.erase(itor);
                    // 由于变更了 communityList 结构，重新循环
                    break;
                }
                /*
                 * else continue;
                 */
            }
        }
    }
}

void Louvain::communityCombine() {
    bool isChanged = true;
    while (isChanged) {
        isChanged = false;
        // 在所有网络中不断搜索
        for (int i = 0; i < this->communityList.size(); ++i) {
            // 建立相邻社区集
            set<Community *> commuSet;
            // 查询社区的所有节点
            for (int j = 0; j < this->communityList[i]->NodeList.size(); ++j) {
                // 查询节点的所有邻居节点
                Node node = this->nodeList[this->communityList[i]->NodeList[j]];
                for (int k = 0; k < node.Neighbor.size(); ++k) {
                    // 邻居节点所属不是目前的社区，加入待查社区集合
                    if (this->nodeList[node.Neighbor[k].ID].Belonging != this->communityList[i])
                        commuSet.insert(this->nodeList[node.Neighbor[k].ID].Belonging);
                }
            };
        }
    }
}

void Louvain::runLouvain() {
    this->nodeCombine();
    cout << endl;
    cout << endl;
    cout << "完成了网络的第一阶段合并\n";
    this->printNet();
    //this->communityCombine();
}

int Louvain::getPhiTot(Node node) {
    // 节点的 Φtot 就是节点本身的度
    return node.Neighbor.size();
}

int Louvain::getPhiTot(Community commu) {
    // 对于社区计算 Φtot
    int count = 0;
    // 社区内的所有节点
    for (int i = 0; i < commu.NodeList.size(); ++i)
        // 节点的邻边
        for (int j = 0; j < this->nodeList[commu.NodeList[i]].Neighbor.size(); ++j)
            // 不在本社区内的邻边
            if (!commu.Index.count(this->nodeList[commu.NodeList[i]].Neighbor[j].ID))
                ++count;
    return count;
};

int Louvain::getKiin(Node node1, Community node2) {
    // 计算节点 node1、节点/社区 node2 的 Ki,in
    int count = 0;
    // 节点 node1 中所有邻边
    for (int i = 0; i < node1.Neighbor.size(); ++i) {
        // 关联到社区 node2 的邻边
        if (node2.Index.count(node1.Neighbor[i].ID))
            ++count;
    }
    return count;

}

int Louvain::getKiin(Community node1, Community node2) {
    // 计算社区 node1、社区 node2 的 Ki,in
    int count = 0;
    // 社区 node1 内的所有节点
    for (int i = 0; i < node1.NodeList.size(); ++i)
        // 节点的邻边
        for (int j = 0; j < this->nodeList[node1.NodeList[i]].Neighbor.size(); ++j)
            // 在社区 node2 内的邻边
            if (node2.Index.count(this->nodeList[node1.NodeList[i]].Neighbor[j].ID))
                ++count;
    return count;
}

int Louvain::getKin(Node node) {
    // 节点的 kin 是节点的度
    return node.Neighbor.size();
}

int Louvain::getKin(Community commu) {
    // 社区的 kin 是社区内节点度的和
    int count = 0;
    for (int i = 0; i < commu.NodeList.size(); ++i)
        count += this->nodeList[commu.NodeList[i]].Neighbor.size();
    return count;

}

void Louvain::test() {
    int targetID = 1;
    int i = 0;
    Node node = this->nodeList[0];
    node.Belonging = this->nodeList[targetID].Belonging;
    // 在新的社区 Index 目录中增加该节点
    node.Belonging->Index.insert(node.ID);
    // 在新的社区 NodeList 堆栈中增加该节点
    node.Belonging->NodeList.push_back(node.ID);
    // 从 communityList 中删除目前的空社区
    vector<Community *>::iterator itor = this->communityList.begin() + i;
    this->communityList.erase(itor);
    ;
}