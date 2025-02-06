#include<iostream>
#include"OpenFile.h"
using namespace std;
int Maxsize = 100;

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

class RElinkedQuene {
	Node* L;
	int count;
public:
	RElinkedQuene() {
		L = new Node();
		L->prior = L;
		L->next = L;
		count = 0;
	}
	RElinkedQuene AddLeft(int m) {
		Node* tmp = new Node(m);
		if (IsEmpty()) {
			L->next = tmp;
			tmp->prior = L;
			tmp->next = L;
			L->prior = tmp;
		}
		else {
			Node* head = L->next;
			L->next = tmp;
			tmp->prior = L;
			tmp->next = head;
			head->prior = tmp;
		}
		count++;
		return *this;
	}
	RElinkedQuene AddRight(int m) {
		Node* tmp = new Node(m);
		if (IsEmpty()) {
			L->prior = tmp;
			tmp->next = L;
			tmp->prior = L;
			L->next = tmp;
		}
		else {
			Node* tail = L->prior;
			L->prior = tmp;
			tmp->next = L;
			tmp->prior = tail;
			tail->next = tmp;
		}
		count++;
		return *this;
	}
	RElinkedQuene DeleteLeft() {
		if (IsEmpty()) {
			cout << "Wrong!" << endl;
		}
		else {
			Node* curr = L->next;
			L->next = curr->next;
			curr->next->prior = L;
			delete curr;
			count--;
		}
		return *this;
	}
	RElinkedQuene DeleteRight() {
		if (IsEmpty()) {
			cout << "Wrong!" << endl;
		}
		else {
			Node* curr = L->prior;
			L->prior = curr->prior;
			curr->prior->next = L;
			delete curr;
			count--;
		}
		return *this;
	}
	bool IsEmpty() {
		if (L->next == L) {
			return true;
		}
		return false;
	}
	bool IsFull() {
		if(count != Maxsize) {
			return false;
		}
		return true;
	}
	void Print() {
		Node* curr = L->next;
		while (curr != L) {
			cout << curr->num;
			if (curr->next != L) {
				cout << " ";
			}
			curr = curr->next;
		}
		cout << endl;
	}
};

int main() {
	RElinkedQuene rq;

	ifstream input("input.txt");
	if (!input.is_open()) {
		cerr << "Error: Cannot open input file!" << endl;
		return 1;
	}

	string line, command;
	int param = 0;

	while (getline(input, line)) {
		stringstream ss(line);
		ss >> command;

		if (command == "AddLeft") {
			if (ss >> param) {
				rq.AddLeft(param).Print();
			}
			else {
				cout << "WRONG" << endl;
			}
		}
		else if (command == "AddRight") {
			if (ss >> param) {
				rq.AddRight(param).Print();
			}
			else {
				cout << "WRONG" << endl;
			}
		}
		else if (command == "DeleteLeft") {
			rq.DeleteLeft().Print();
		}
		else if (command == "DeleteRight") {
			rq.DeleteRight().Print();
		}
		else if (command == "IsEmpty") {
			cout << (rq.IsEmpty() ? "Yes" : "No") << endl;
		}
		else if (command == "IsFull") {
			cout << (rq.IsFull() ? "Yes" : "No") << endl;
		}
		else if (command == "End") {
			break;
		}
		else {
			cout << "WRONG" << endl;
		}
	}

	input.close();
	return 0;

}