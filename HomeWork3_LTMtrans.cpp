#include<iostream>
using namespace std;

template<typename T>
class LTMatrix {
public:
	int size;
	T* elements;
	LTMatrix() {
		size = 0;
		elements = new T();
	}
	LTMatrix(int s){
		size = s;
		elements = new T[s * (s + 1) / 2];
	}
	void set(int i, int j, const T& newValue);
	LTMatrix<T> transpose();
	void print();
};

template<typename T>
void LTMatrix<T>::set(int i, int j, const T& newValue)
{
	if (i < 1 || j < 1 || i > size || j > size)
		cout << "Not vaild! " << endl;
	if (i >= j)
		elements[i * (i - 1) / 2 + j - 1] = newValue;
	else
		if (newValue != 0)
			cout << "Elements not in lower triangle must be zero! " << endl;
};

template<typename T>
LTMatrix<T> LTMatrix<T>::transpose()
{
	LTMatrix<T> trans(size);
	int k = 0;
	for (int j = 1; j < size + 1; j++) {
		for (int i = j; i < size + 1; i++) {
			trans.elements[k] = elements[i * (i - 1) / 2 + j - 1];
			k++;
		}
	}
	return trans;
}

template<typename T>
void LTMatrix<T>::print()
{
	for (int i = 0; i < size * (size + 1) / 2; i++) {
		cout << elements[i] << " ";
	}
	cout << endl;
}

int main() {
	int n = 0;
	cin >> n;
	LTMatrix<int> m0(n);

	// m0.print();

	for (int i = 0; i < n * (n + 1) / 2; i++) {
		*(m0.elements+i) = i;
	}
	m0.print();
	m0.transpose().print();
	
}