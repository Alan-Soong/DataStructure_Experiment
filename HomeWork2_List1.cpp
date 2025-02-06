#include<iostream>
using namespace std;

class Node {
public:
	int num;
	Node* next;
	Node() {
		num = 0;
		next = NULL;
	}
	Node(int n) {
		num = n;
		next = NULL;
	}
};

class extendedChain {
public:
	Node* head;
	extendedChain() {
		head = NULL;
	}
	void insert(int m);
	void print();
};

void extendedChain::insert(int m)
{
	Node* tmp = new Node(m);
	if (head == NULL) {
		head = tmp;
		return;
	}
	Node* curr = head;
	while (curr != NULL) {
		if (curr->next == NULL) {
			tmp->next = curr->next;
			curr->next = tmp;
			return;
		}
		curr = curr->next;
	}
	return;
}

void extendedChain::print()
{
	Node* curr = head;
	while (curr != NULL) {
		cout << curr->num;
		if (curr->next != NULL) {
			cout << " ";
		}
		curr = curr->next;
	}
	cout << endl;
	return;
}

extendedChain melt(extendedChain m, extendedChain n) {
	extendedChain k;
	k = m;
	Node* curr = k.head;
	while (curr != NULL) {
		if (n.head != NULL && curr->next == NULL) {
			curr->next = n.head;
			return k;
		}
		if (n.head == NULL && curr != NULL) {
			curr = curr->next;
			return k;
		}
		Node* curr0 = n.head;
		n.head = n.head->next;
		curr0->next = curr->next;
		curr->next = curr0;
		curr = curr->next->next;
	}
	return k;
}

int main() {
	int n = 0;
	cin >> n;
	extendedChain a, b, c, d, e, f;
	for (int i = 0; i < 2*n; i++) {
		a.insert(i);
	}
	a.print();
	for (int i = n; i > 0; i--) {
		b.insert(i);
	}
	b.print();
	melt(a, b).print();

	for (int i = 0; i < n; i++) {
		c.insert(i);
	}
	c.print();
	for (int i = 2*n; i > 0; i--) {
		d.insert(i);
	}
	d.print();
	melt(c,d).print();

	for (int i = 0; i < n; i++) {
		e.insert(i);
	}
	e.print();
	for (int i = n; i > 0; i--) {
		f.insert(i);
	}
	f.print();
	melt(e,f).print();
	return 0;
}