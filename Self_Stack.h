#pragma once
#include<cstddef>

class ArrayStack {
	int maxsize;
	int top_index;
	int* elements;
public:
	ArrayStack(int n) {
		maxsize = n;
		elements = new int(n);
		top_index = -1;
	}
	int top();
	void push(int m);
	void pop();
	bool isEmpty();
	bool isFull();
};

int ArrayStack::top()
{
	return elements[top_index];
}

void ArrayStack::push(int m)
{
	if (!isFull()) {
		elements[++top_index] = m;
	}
	return;
}

void ArrayStack::pop()
{
	elements[top_index--] = NULL;
}

bool ArrayStack::isEmpty()
{
	if (top_index == -1) {
		return true;
	}
	return false;
}

bool ArrayStack::isFull()
{
	if (top_index == maxsize) {
		return true;
	}
	return false;
}

template<typename T>
class Node {
public:
	T num;
	Node* next;
	Node(T n) {
		num = n;
		next = NULL;
	}
};

template<typename T>
class LinkedStack {
	Node<T>* head;
public:
	LinkedStack() {
		head = NULL;
	}
	T top();
	void push(T m);
	void pop();
	bool isEmpty();
};

template<typename T>
T LinkedStack<T>::top() {
	return head->num;
}

template<typename T>
void LinkedStack<T>::push(T m)
{
	Node<T>* tmp = new Node<T>(m);
	tmp->next = head;
	head = tmp;
}

template<typename T>
void LinkedStack<T>::pop()
{
	head = head->next;
}

template<typename T>
bool LinkedStack<T>::isEmpty()
{
	if (head == NULL) {
		return true;
	}
	return false;
}