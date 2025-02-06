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
            if (parent[i] == parent[j]) {
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
}