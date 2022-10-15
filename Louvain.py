class Louvain:
    # 初始化
    def __init__(self, filename):
        self.answer = []
        # 节点指向自身的边数量
        self.phiIN = []
        # 节点集合
        self.nodes = {}
        # 边集合
        self.edges = []
        # 路径总数
        self.m = 0
        file = open(filename, 'r')
        contents = file.readlines()
        # 初始化网络中的节点与边
        for line in contents:
            nodes = line.split()
            # 标记节点存在
            self.nodes[int(nodes[0])] = 1
            self.nodes[int(nodes[1])] = 1
            # 插入一条边的记录
            self.edges.append(((int(nodes[0]), int(nodes[1])), 1))
            # 网络总边数增 1
            self.m += 1
        file.close()
        # 使用节点与边来构造初始的网络
        self.network = (self.nodes, self.edges)
        # 初始化节点的度数
        self.Ki = [0 for node in self.nodes]
        self.w = [0 for node in self.nodes]
        # 每个节点有关的边的集合
        self.edges_of_nodes = {}
        # 遍历所有的边
        for edge in self.edges:
            # 增加每条边指向的两个节点的度数
            self.Ki[edge[0][0]] += edge[1]
            self.Ki[edge[0][1]] += edge[1]
            # 对节点建立边表
            if edge[0][0] not in self.edges_of_nodes:
                # 某个节点信息不在节点有关的边的集合里，就在该节点位置新增一个边集合
                self.edges_of_nodes[edge[0][0]] = [edge]
            else:
                # 某个节点信息已在节点有关的边的集合里，在该位置插入一条边
                self.edges_of_nodes[edge[0][0]].append(edge)
            # 边两侧做同样操作
            if edge[0][1] not in self.edges_of_nodes:
                self.edges_of_nodes[edge[0][1]] = [edge]
            else:
                self.edges_of_nodes[edge[0][1]].append(edge)
        # 将所有节点都单独分配到一个社区，id 为节点编号，数值为节点所属社区标签
        self.communities = [n for n in self.nodes]
        self.top_community = []


    # 获取节点的邻居
    def get_neighbors(self, node):
        # 初始化邻居节点列表
        neighbors = []
        for edge in self.edges_of_nodes[node]:
            # 边的左右相同则跳过
            if edge[0][0] == edge[0][1]:
                continue
            # 边的左侧为节点时，插入边的右侧
            if edge[0][0] == node:
                neighbors.append(edge[0][1])
            # 边的右侧为节点时，插入边的左侧
            if edge[0][1] == node:
                neighbors.append(edge[0][0])
        return neighbors

    # 计算DeltaQ
    def calculate_delta_modularity(self, node, community, KiIn):
        m = self.m
        ki = self.Ki[node]
        phiTot = self.phiTot[community]
        phiIn = self.phiIN[community]
        qsep = phiIn / 2 / m - phiTot * phiTot / 4 / m / m - ki * ki / 4 / m / m
        qcomb = (phiIn + 2 * KiIn) / 2 / m - ((phiTot + ki) / 2 / m) * ((phiTot + ki) / 2 / m)
        return qcomb - qsep

    # 重新加载网络参数
    def setup_network(self, network):
        # 初始化当前网络的 Φin
        self.phiIN = [0 for node in network[0]]
        # 初始化当前网路的 Φtot
        self.phiTot = [self.Ki[node] for node in network[0]]
        # 查询所有指向自身的边，计算网络的 Φin
        for edge in network[1]:
            if edge[0] == edge[1]:
                # 对于无权图，权重为 1，对于指向自身的边，计数两次
                self.phiIN[edge[0]] += 1
                self.phiIN[edge[1]] += 1

    # 计算网络当前模块度
    def get_network_modularity(self, community):
        q = 0
        for i in range(len(community)):
            q += self.phiIN[i] / 2 / self.m - (self.phiTot[i] / 2 / self.m) * (self.phiTot[i] / 2 / self.m)
        return q

    # 阶段一，模块度检测
    def phase1(self, network):
        # 修改标记位
        is_changed = True
        # 初始化分割社区，此时每个社区当中只有一个节点
        division = [[node] for node in network[0]]
        while is_changed:
            is_changed = False
            # 搜索网络中所有节点
            for node in network[0]:
                max_delta_q = 0
                max_link = 0
                self_community = self.communities[node]
                # 移动目标社区，默认为初始社区，即不发生移动
                target_community = self_community
                # 寻找社区的邻居节点
                neighbors = self.get_neighbors(node)
                # 初始化邻居社区
                neighbors_communities = {}
                # 通过邻居节点寻找邻居社区
                for neighbor in neighbors:
                    # 选中节点所在的社区
                    community = self.communities[neighbor]
                    # 社区已在邻居社区列表中则跳过
                    if community in neighbors_communities:
                        continue
                    # 社区不在邻居社区中则将该位置置 1
                    neighbors_communities[community] = 1
                    # 开始检测目前节点与该社区的所有邻边
                    links = 0
                    for edge in self.edges_of_nodes[node]:
                        if edge[0][0] == edge[0][1]:
                            continue
                        # 节点一条边执指向的节点在社区内则将关联度增加上这条边的权重
                        if self.communities[edge[0][0]] == community or self.communities[edge[0][1]] == community:
                            links += edge[1]
                    delta_q = self.calculate_delta_modularity(node, community, links)
                    if delta_q > max_delta_q:
                        target_community = community
                        max_delta_q = delta_q
                        max_link = links
                # 归属未发生时，进行下一个点
                if target_community == self_community:
                    continue
                is_changed = True
                # 修改社区中的节点
                division[self_community].remove(node)
                division[target_community].append(node)
                # 修改节点的归属网络
                self.communities[node] = target_community
                # 移入新社区后，社区内部的边个数应当增加节点和社区之间的关联边数的两倍
                self.phiIN[target_community] += 2 * (max_link + self.w[node])
                # 移入新社区后，与社区有关联的边数应当增加上节点的度
                self.phiTot[target_community] += self.Ki[node]
            # 当没有进行更改时，跳出 while 循环
            if not is_changed:
                break
        # 将分割后的社区返回
        return division

    # 阶段二，社区合并
    def phase2(self, network, division):
        # 构建新的超级节点列表，长度为新的社区长度
        nodes = [i for i in range(len(division))]
        # 新的节点对于社区编号组，id 为节点编号，数值为节点所属社区标签
        communities = []
        # 新的编号标签集，id 为旧的标签内容，数值为新的标签数据
        label = {}
        # 新的编号计数器
        i = 0
        # 遍历所有社区标签
        for community in self.communities:
            if community in label:
                # 该节点旧的标签已在新的标签集中，则直接为该节点替换为对应新的节点编号，编号为旧标签在 label 的位置
                communities.append(label[community])
            else:
                # 该节点旧的标签不在新的标签集中，则为该标签建立新的编号 i
                label[community] = i
                # 该节点所属社区换为新的编号 i
                communities.append(i)
                # 编号计数器增加
                i += 1
        # 替换类中的社区标签集
        self.communities = communities
        # 新边记录表
        edges = {}
        for edge in network[1]:
            # 获取旧的边的左右两个节点的社区
            left = self.communities[edge[0][0]]
            right = self.communities[edge[0][1]]
            # 用两个社区表示边的两端
            if (left, right) in edges:
                # 当社区表示的边已经在新边记录表中，直接对原有记录的权重加上目前边的权值
                edges[(left, right)] += edge[1]
            else:
                # 当社区表示的边不经在新边记录表中，将这条边的权值令为目前检测的边的权值
                edges[(left, right)] = edge[1]
        # 将边重新转换为((i,j),w)的形式
        edges = [(n, w) for n, w in edges.items()]
        self.edges = edges
        # 初始化节点的度数
        self.Ki = [0 for node in nodes]

        self.w = [0 for n in nodes]
        # 初始化每个节点有关的边的集合
        self.edges_of_nodes = {}
        # 遍历所有的边
        for edge in self.edges:
            # 增加每条边指向的两个节点的度数
            self.Ki[edge[0][0]] += edge[1]
            self.Ki[edge[0][1]] += edge[1]

            if edge[0][0] == edge[0][1]:
                self.w[edge[0][0]] += edge[1]
            # 对节点建立边表
            if edge[0][0] not in self.edges_of_nodes:
                # 某个节点信息不在节点有关的边的集合里，就在该节点位置新增一个边集合
                self.edges_of_nodes[edge[0][0]] = [edge]
            else:
                # 某个节点信息已在节点有关的边的集合里，在该位置插入一条边
                self.edges_of_nodes[edge[0][0]].append(edge)
            # 边两侧做同样操作
            if edge[0][1] not in self.edges_of_nodes:
                self.edges_of_nodes[edge[0][1]] = [edge]
            else:
                self.edges_of_nodes[edge[0][1]].append(edge)
        # 将所有节点都单独分配到一个社区，id 为节点编号，数值为节点所属社区标签
        self.communities = [n for n in nodes]
        self.nodes = nodes
        # 更改目前的网络结构
        self.network = (nodes, edges)

    # 标签加载
    def getLabel(self, filename):
        file = open(filename, 'r')
        contents = file.readlines()
        result = {}
        list = []
        for line in contents:
            text = line.split()
            node = text[0]
            community = text[1]
            if community in result:
                result[community].append(node)
            else:
                result[community] = [node]
        file.close()
        for i in result:
            list.append(result[i])
        self.answer = list

    # 进行 Louvain 算法
    def do_louvain(self):
        old_modularity = -1
        while True:
            # 初始化网络参数
            self.setup_network(self.network)
            division = self.phase1(self.network)
            new_modularity = self.get_network_modularity(division)
            division = [c for c in division if c]

            if self.top_community:
                temp = []
                for p in division:
                    part = []
                    for n in p:
                        part.extend(self.top_community[n])
                    temp.append(part)
                self.top_community = temp
            else:
                self.top_community = division

            if new_modularity > old_modularity:
                # 调整网络结构
                self.phase2(self.network, division)
                # 更新最优的模块度
                old_modularity = new_modularity
            else:
                break
        return old_modularity

    def run(self):
        q = self.do_louvain()
        for i in range(len(self.top_community)):
            print(self.top_community[i])
        print("最终的模块度为 " + str(q))
    # def run_with_label(self):
    #     q = self.do_louvain()
    #     print()


