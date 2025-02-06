#include<iostream>
#include<vector>
#include<ctime>
#include<cmath>
using namespace std;

template<typename K, typename E>
struct Node {
	K key;
	E element;
	Node<K, E>* next;
	Node() {
		next = NULL;
	}
	Node(K k, E e) {
		key = k;
		element = e;
		next = NULL;
	}
};

template<typename K, typename E>
class hashChainsWithTail {
	vector<Node<K, E>*> hashTable;
	Node<K, E>* tail;
	int hash(K k) {
		return abs(k) % hashTable.size();
	}
public:
	hashChainsWithTail(int size) {
		hashTable.resize(size, NULL);
		tail = NULL;
	}
	void insert(K k, E e) {
		int index = hash(k);
		Node<K, E>* newNode = new Node<K, E>(k, e);
		if (hashTable[index] == NULL) {
			hashTable[index] = newNode;
			if (tail == NULL) {
				tail = newNode;
			}
		}
		else {
			Node<K, E>* p = hashTable[index];
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = newNode;
		}
	}
	void erase(K k) {
		int index = hash(k);
		Node<K, E>* prev = NULL;
		Node<K, E>* p = hashTable[index];
		while (p != NULL && p->key != k) {
			prev = p;
			p = p->next;
		}
		if (p != NULL) {
			if (prev == NULL) {
				hashTable[index] = p->next;
			}
			else {
				prev->next = p->next;
			}
			if (p == tail) {
				tail = prev;
			}
			delete p;
		}
	}
	void print() {
		for (int i = 0; i < hashTable.size(); i++) {
			Node<K, E>* current = hashTable[i];
			while (current != nullptr) {
				cout << "(" << current->key << "," << current->element << ")" << " ";
				current = current->next;
			}
			if (current == nullptr) {
				cout << "NULL ";
			}
			cout << endl;
		}
	}
};

int main() {
	int n = 0;
	cin >> n;
	clock_t start = clock();
	srand(time(0));
	hashChainsWithTail<int, int> hct(n);
	for (int i = 0; i < n; i++) {
		hct.insert(rand()%1000, rand()%1000);
	}
	hct.print();
	clock_t end = clock();
	cout << "It takes: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
}