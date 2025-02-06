/*#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int V, E, label, path;
int isvisit[100];
vector<int> Graph[100];

void DFS(int v, int reach[], int label, int parent[]) {
    reach[v] = 1;
    parent[v] = label;
    for (int i = 0; i < Graph[v].size(); i++) {
        int y = Graph[v][i];
        //reach[v] = 1;
        if (reach[y] == 0) {
            DFS(y, reach, label, parent);
        }
    }
}

int labelComponents(int reach[], int parent[])
{
    //给无向图的构件做标记, 返回构件的个数
    //令 c[i] 是顶点i的构件号
    //确定是一个无向图

    //令所有顶点是非构件
    for (int i = 0; i < V; i++) {
        reach[i] = 0;
        parent[i] = -1;
    }

    label = 0; //最后一个构件的编号
    //确定构件
    for (int i = 0; i < V; i++) {
        if (reach[i] == 0) //顶点i未到达
        {//顶点i是一个新构件
            DFS(i, reach, label, parent);//给新构件做标记
        }
    } 
    return label;
    
}

int main() {
    
    //int n = 0; double P = 0;
    //cin >> n >> P;
    //printGraph(generateGraph(n, P));

    cin >> E >> V;
    for (int i = 0; i < E; i++) {
        int u = 0, v = 0;
        cin >> u >> v;
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }
    cout << labelComponents(isvisit);
    cout << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (flag[i] == flag[j] && i != j ) {
                cout << 1 << " ";
            }
            else {
                cout << 0 << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}*/

/*
#include <iostream>
#include <vector>

class graph {
public:
    int n;
    std::vector<std::vector<int>> adj;
    void dfs(int start, int current, std::vector<bool>& visited) {
        visited[current] = true;
        for (int i = 0; i < n; ++i) {
            if (adj[current][i] && !visited[i]) {
                dfs(start, i, visited);
            }
        }
    }

    graph(int vertices) : n(vertices), adj(vertices, std::vector<int>(vertices, 0)) {}

    void addEdge(int i, int j) {
        adj[i][j] = 1;
        adj[j][i] = 1;
    }

    std::vector<std::vector<int>> undirectedTC() {
        std::vector<std::vector<int>> tc(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            std::vector<bool> visited(n, false);
            dfs(i, i, visited);
            for (int j = 0; j < n; ++j) {
                if (visited[j]) {
                    if (i != j) {
                        tc[i][j] = 1;
                    }
                    else {
                        tc[i][j] = 0;
                    }
                }
            }
        }
        return tc;
    }
};

int main() {
    graph g(4);
    g.addEdge(0, 1);
    g.addEdge(2, 3);
    g.addEdge(2, 0);

    for (int k = 0; k < 4; k++) {
        for (int l = 0; l < 4; l++) {
            std::cout << g.adj[k][l] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::vector<std::vector<int>> result = g.undirectedTC();
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}*/

/*
#include <iostream>
#include <vector>
using namespace std;
int V, E;

// 深度优先搜索函数
void DFS(int v, vector<int>& reach, int label, vector<int>& parent, const vector<vector<int>>& Graph) {
    reach[v] = 1;
    parent[v] = label;
    for (int y : Graph[v]) {
        if (reach[y] == 0) {
            DFS(y, reach, label, parent, Graph);
        }
    }
}

// 给无向图的构件做标记
void labelComponents(int V, vector<int>& reach, vector<int>& parent, const vector<vector<int>>& Graph) {
    // 令所有顶点是非构件
    reach.assign(V, 0);
    parent.assign(V, -1);

    int label = 0; // 最后一个构件的编号
    // 确定构件
    for (int i = 0; i < V; i++) {
        if (reach[i] == 0) { // 顶点i未到达
            // 顶点i是一个新构件
            DFS(i, reach, label, parent, Graph);
            label++;
        }
    }
}

// 计算无向图的传递闭包
vector<vector<int>> undirectedTC(int V, const vector<vector<int>>& Graph) {
    vector<int> reach(V, 0);
    vector<int> parent(V, -1);
    labelComponents(V, reach, parent, Graph);

    vector<vector<int>> tc(V, vector<int>(V, 0));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (parent[i] == parent[j] && i != j) {
                tc[i][j] = 1;
            }
        }
    }
    return tc;
}

int main() {

    cout << "Please input the number of E and V: " << endl;
    cin >> E >> V;
    vector<vector<int>> Graph(V, vector<int>());
    int u, v;
    cout << "Please input every E: " << endl;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }

    vector<vector<int>> result = undirectedTC(V, Graph);
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}*/

#include <iostream>
#include <vector>
using namespace std;

int V, E;

// 深度优先搜索函数
void DFS(int v, int start, vector<vector<int>>& tc, vector<int>& visited, const vector<vector<int>>& Graph, int pathLength) {
    visited[v] = 1;

    // 如果路径长度大于 1，则更新传递闭包矩阵
    if (pathLength > 1) {
        tc[start][v] = 1;
    }

    for (int neighbor : Graph[v]) {
        if (!visited[neighbor]) {
            DFS(neighbor, start, tc, visited, Graph, pathLength + 1);
        }
    }
    visited[v] = 0; // 回溯时重置状态
}

// 计算无向图的传递闭包
vector<vector<int>> undirectedTC(int V, const vector<vector<int>>& Graph) {
    // 初始化传递闭包矩阵
    vector<vector<int>> tc(V, vector<int>(V, 0));

    // 遍历图中每个顶点，使用 DFS 查找路径长度大于 1 的可达节点
    for (int i = 0; i < V; i++) {
        vector<int> visited(V, 0); // 记录每次 DFS 的访问状态
        DFS(i, i, tc, visited, Graph, 0);
    }

    return tc;
}

int main() {
    cout << "Please input the number of E and V: " << endl;
    cin >> E >> V;
    vector<vector<int>> Graph(V, vector<int>());
    int u, v;
    cout << "Please input every E: " << endl;
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }

    // 计算传递闭包
    vector<vector<int>> result = undirectedTC(V, Graph);

    // 输出传递闭包矩阵
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
