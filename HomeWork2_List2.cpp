#include<iostream>
using namespace std;

class Node {
public:
	int num;
	Node* prior;
	Node* next;
	Node() {
		num = 0;
		prior = NULL;
		next = NULL;
	}
	Node(int n) {
		num = n;
		prior = NULL;
		next = NULL;
	}
};

class extendedChain {
public:
	Node* dummyhead;
	extendedChain() {
		dummyhead = new Node(); 
		dummyhead->next = dummyhead;
		dummyhead->prior = dummyhead;
	}
	void insert(int m);
	void print();
	void split0(extendedChain& a, extendedChain& b);
};

void extendedChain::insert(int m)
{
	Node* tmp = new Node(m);
	if (dummyhead->next == dummyhead) {  
		dummyhead->next = tmp;
		tmp->prior = dummyhead;
		tmp->next = dummyhead;
		dummyhead->prior = tmp;
	}
	else {
		Node* tail = dummyhead->prior;
		tail->next = tmp;
		tmp->prior = tail;
		tmp->next = dummyhead;
		dummyhead->prior = tmp;
	}
}

void extendedChain::print()
{
	Node* curr = dummyhead->next;
	while (curr != dummyhead) {
		cout << curr->num;
		if (curr->next != dummyhead) {
			cout << " ";
		}
		curr = curr->next;
	}
	cout << endl;
}

void split(extendedChain c,extendedChain& a, extendedChain& b) {
	Node* curr = c.dummyhead->next;
	while (curr != c.dummyhead) {
		a.insert(curr->num);
		curr = curr->next;
		if (curr == c.dummyhead) break;
		b.insert(curr->num);
		curr = curr->next;
	}
	return;
}

void extendedChain::split0(extendedChain& a, extendedChain& b)
{
	Node* curr = dummyhead->next;
	while (curr != dummyhead) {
		a.insert(curr->num);
		curr = curr->next;
		if (curr == dummyhead) break;
		b.insert(curr->num);
		curr = curr->next;
	}
	return;
}

int main() {
	int n = 0;
	cin >> n;
	extendedChain c;
	for (int i = 0; i < n; i++) {
		c.insert(i);
	}
	c.print();
	extendedChain a, b, o, p;
	split(c, a, b);
	a.print();
	b.print();
	c.split0(o, p);
	o.print();
	p.print();
}