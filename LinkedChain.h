#pragma once
#include<iostream>

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

class LinkedChain {
public:
	Node* head;
	LinkedChain() {
		head = NULL;
	}
	~LinkedChain();
	void Insert(int m);
	void Remove(Node* nd);
	void Output();
	bool isEmpty();
	int length();
	Node* Index(int i);
};

LinkedChain::~LinkedChain()
{
	Node* tmp = head;
	while (head) {
		tmp = head->next;
		delete head;
		head = tmp;
	}
}

void LinkedChain::Insert(int m)
{
	Node* tmp = new Node(m);
	if (isEmpty()) {
		head = tmp;
		return;
	}
	Node* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	
	tmp->next = curr->next;
	curr->next = tmp;
	return;
}

void LinkedChain::Remove(Node* nd)
{
	Node* curr = head;
	if (head == nd) {
		head = head->next;
		return;
	}
	while (curr->next != nd) {
		curr = curr->next;
	}
	curr->next = curr->next->next;
	return;
}

void LinkedChain::Output()
{
	Node* curr = head;
	while (curr) {
		std::cout << curr->num;
		curr = curr->next;
		if (curr != NULL) {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

bool LinkedChain::isEmpty()
{
	if (head == NULL) {
		return true;
	}
	return false;
}

int LinkedChain::length()
{
	int len = 0;
	Node* curr = head;
	while (curr) {
		len++;
		curr = curr->next;
	}
	return len;
}

Node* LinkedChain::Index(int i)
{
	Node* curr = head;
	int i0 = 0;
	while (i0 != i) {
		curr = curr->next;
		i0++;
	}
	return curr;
}