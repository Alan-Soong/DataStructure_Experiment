#include<iostream>
#include<queue>
#include<vector>

using namespace std;
int V, E, path;
vector<int> Graph[100], length;

bool bfsResearch(int v, int reach[], int label, int end, int parent[]) {
	queue<int> Q;
	path = 0;
	for (int i = 0; i < V; i++) {
		reach[i] = 0;
		parent[i] = -1;
	}
	reach[v] = label;
	Q.push(v);

	while (!Q.empty()) {
		int w = Q.front();
		Q.pop();
		
		for (int i = 0; i < Graph[w].size(); i++) {
			int u = Graph[w][i];
			if (reach[u] == 0) {
				Q.push(u);
				reach[u] = label;
				parent[u] = w;	//记录父节点;

				if (u == end) {
					return true;
				}
				
			}
		}
	}
	return false;
}

void printPath(int start, int end, int parent[]) {
	vector<int> pathVec;
	int current = end;
	while (current != -1) {
		pathVec.push_back(current);
		current = parent[current];
	}

	// 手动反转路径
	for (int i = 0; i < pathVec.size() / 2; i++) {
		swap(pathVec[i], pathVec[pathVec.size() - i - 1]);
	}

	cout << "The path from " << start << " to " << end << " is: ";
	for (int i = 0; i < pathVec.size(); i++) {
		cout << pathVec[i] << (i == pathVec.size() - 1 ? "\n" : " -> ");
	}
}

// 计算路径的长度
int getPathLength(int start, int end, int parent[]) {
	int length = 0;
	int current = end;
	while (current != start) {
		current = parent[current];
		length++;
	}
	return length;
}

int main() {
	cout << "Please input the number of E and V: " << endl;
	cin >> E >> V;
	int u, v;
	cout << "Please input every E: " << endl;
	for (int i = 0; i < E; i++) {
		cin >> u >> v;
		Graph[u].push_back(v);
		Graph[v].push_back(u);
	}

	int* isVisit = new int[V];
	int* parent = new int[V];  // 存储父节点的数组
	int start = 0, end = 0;

	cout << "Please input start and end: " << endl;
	cin >> start >> end;

	bool p = bfsResearch(start, isVisit, 1, end, parent);

	cout << "The record of visit: " << endl;
	for (int i = 0; i < V; i++) {
		cout << isVisit[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < V; i++) {
		cout << parent[i] << " ";
	}
	cout << endl;

	switch (p) {
	case 1: cout << "The path from " << start
		<< " to " << end << " is existed! " << endl;
		printPath(start, end, parent);  // 打印路径
		cout << "The length of path is: " 
			<< getPathLength(start, end, parent) << endl;
		break;
	case 0: cout << "The path from " << start
		<< " to " << end << " isn't existed! " << endl; 
		break;
	default:break;
	}
	cout << endl;
	
	delete[] isVisit;  // 清理动态分配的内存
	return 0;
}