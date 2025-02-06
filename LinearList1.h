#pragma once
#include<iostream>

template<typename T>
class ChainNode {
	T num;
	ChainNode<T>* next;
public:
	ChainNode() {
		num = 0;
		next = 0;
	}
	ChainNode(T n) {
		num = n;
		next = 0;
	}
};

template<typename T>
class Chain {
	ChainNode<T>* head;
public:
	Chain<T>() {head = 0;}
	~Chain();
	bool IsEmpty() const { return head == 0; }
	int Length() const;
	bool Find(int k, T& x) const;
	int Search(const T& x);
	Chain<T>& Insert(int k, T& m);
	Chain<T>& Delete(int k, T& m);
	Chain<T>& Append(const T& x);
	void Print();
	void print(int k);
};

template<typename T>
Chain<T>::~Chain()
{
	ChainNode<T>* curr;
	while (head) {
		curr = head->next;
		delete head;
		head = curr;
	}
}

template<typename T>
int Chain<T>::Length() const
{
	int len = 0;
	ChainNode<T>* curr = head;
	while (curr) {
		len++;
		curr = curr->next;
	}
	return len;
}

template<typename T>
bool Chain<T>::Find(int k, T& x) const
{
	if (k > Length() || k < 1) return false;
	ChainNode<T>* curr = head;
	for (int i = 0; (i < k) && curr; i++) {
		curr = curr->next;
	}
	if (curr) {
		x = curr->num;
		return true;
	}
	return false;
}

template<typename T>
int Chain<T>::Search(const T& x)
{
	int index = 0;
	ChainNode<T>* curr = head;
	while (curr && curr->num != x) {
		index++;
		curr = curr->next;
	}
	if (curr) return index;
	return 0;
}

template<typename T>
Chain<T> &Chain<T>::Insert(int k, T& m)
{
	if (k > Length() || k < 0) {
		throw OutOfBounds();
	}
	ChainNode<T>* curr = head;
	for (int i = 0; (i < k - 1) && curr; i++) {
		curr = curr->next;
	}
	ChainNode<T>* tmp = new ChainNode(m);
	if (k) {
		tmp->next = curr->next;
		curr->next = tmp;
	}
	else {
		tmp->next = head;
		head = tmp;
	}
	return *this;
}

template<typename T>
Chain<T>& Chain<T>::Delete(int k, T& m)
{
	if (k < 1 || !head) {
		throw OutOfBounds();
	}
	ChainNode<T>* curr = head;
	if (k == 1) {
		head = head->next;
	}
	else {
		ChainNode<T>* curr0 = head;
		for (int i = 1; i < k - 1; i++) {
			curr0 = curr0->next;
		}
		if (!curr0 || !curr0->head) {
			throw OutOfBounds();
		}
		curr = curr0->next;
		curr0->next = curr->next;
	}
	x = curr->num;
	delete p;
	return *this;
}

template<typename T>
Chain<T>& Chain<T>::Append(const T& x)
{
	ChainNode<T>* tmp = new ChainNode(m);
	if (head) {
		ChainNode<T>* curr = head;
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = tmp;
	}
	else {
		head = tmp;
	}
	return *this;
}

template<typename T>
void Chain<T>::Print()
{
	ChainNode* curr = head;
	while (curr) {
		cout << curr->num << " ";
		curr = curr->next;
	}
}

template<typename T>
void Chain<T>::print(int k)
{
	ChainNode* curr = head;
	for (int i = 0; (i < k) && curr; i++) {
		curr = curr->next;
	}
	if (curr) {
		cout << curr->num << endl;
	}
	else {
		return;
	}
}
