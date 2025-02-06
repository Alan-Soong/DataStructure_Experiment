#include <iostream>
#include <vector>
using namespace std;
int V, E;

// ���������������
void DFS(int v, vector<int>& reach, int label, vector<int>& parent, const vector<vector<int>>& Graph) {
    reach[v] = 1;
    parent[v] = label;
    for (int y : Graph[v]) {
        if (reach[y] == 0) {
            DFS(y, reach, label, parent, Graph);
        }
    }
}

// ������ͼ�Ĺ��������
void labelComponents(int V, vector<int>& reach, vector<int>& parent, const vector<vector<int>>& Graph) {
    // �����ж����Ƿǹ���
    reach.assign(V, 0);
    parent.assign(V, -1);

    int label = 0; // ���һ�������ı��
    // ȷ������
    for (int i = 0; i < V; i++) {
        if (reach[i] == 0) { // ����iδ����
            // ����i��һ���¹���
            DFS(i, reach, label, parent, Graph);
            label++;
        }
    }
}

// ��������ͼ�Ĵ��ݱհ�
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