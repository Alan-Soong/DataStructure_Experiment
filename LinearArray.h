#pragma once
#include<iostream>

class LinearArray {
public:
	int length;
	int* elements;
	int maxsize = 100;
	LinearArray() {
		elements = new int();
		length = 0;
	}
	LinearArray(int n) {
		elements = new int(n);
		length = n;
	}
	void Insert(int m);
	bool Find(int m);
	void Remove(int m);
	void Output();
	bool isEmpty();
};

void LinearArray::Insert(int m)
{
	elements[length++] = m;
}

bool LinearArray::Find(int m)
{
	for (int i = 0; i < length; i++) {
		if (elements[i - 1] == m) {
			return true;
		}
	}
	return false;
}

void LinearArray::Remove(int m)
{
	for (int i = m - 1; i < length - 1; i++) {
		elements[i] = elements[i + 1];
	}
	length--;
}

void LinearArray::Output()
{
	for (int i = 0; i < length; i++) {
		std::cout << elements[i];
		if (i != length) {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

bool LinearArray::isEmpty()
{
	if (length == 0) {
		return true;
	}
	return false;
}