#include<iostream>
#include"LinearArray.h"
#include"LinkedChain.h"
using namespace std;

void LAJos(LinearArray la, int m) {
	int i = 0;
	while (!la.isEmpty()) {
		i = (i + m - 1) % la.length;
		cout << la.elements[i];
		la.Remove(i+1);
		if (!la.isEmpty()) {
			cout << " ";
		}
	}
	cout << endl;
	return;
}

void LCJos(LinkedChain lc, int m) {
	int i = 0;
	while (!lc.isEmpty()) {
		i = (i + m - 1) % lc.length();
		Node* tmp = lc.Index(i);
		cout << tmp->num;
		lc.Remove(tmp);
		if (!lc.isEmpty()) {
			cout << " ";
		}
	}
	cout << endl;
}

int main() {
	int n = 0, m = 0;
	cin >> n >> m;
	LinearArray jok;
	for (int i = 1; i < n + 1; i++) {
		jok.Insert(i);
	}
	//jok.Output();
	LAJos(jok, m);

	LinkedChain jos;
	for (int i = 1; i < n + 1; i++) {
		jos.Insert(i);
	}
	//jos.Output();
	LCJos(jos, m);
	return 0;
}

