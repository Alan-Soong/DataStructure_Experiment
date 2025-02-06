#include<iostream>
using namespace std;

template <class T>
class Term {
public:
	int row, col;
	T value;
};

template<typename T>
class SMatrix {
public:
	int rows, cols;
	int terms;
	Term<T>* elements;
	int MaxTerms;
	SMatrix(int maxTerms) {
		MaxTerms = maxTerms;
		elements = new Term<T>[MaxTerms];
		terms = rows = cols = 0;
		for (int i = 0; i < MaxTerms; i++) {
			elements[i].value = 0;
		}
	}
	void append(int p, int q, T con);
	void input();
	SMatrix<T> mul(SMatrix<T> M0);
	void print();
	bool isEmpty();
};

template<typename T>
void SMatrix<T>::append(int p, int q, T con)
{
	elements[terms].row = p;
	elements[terms].col = q;
	elements[terms].value = con;

	int i = 0;
	while (i != terms) {
		if ((elements[i].row == elements[terms].row) && (elements[i].col == elements[terms].col)) {
			elements[i].value += elements[terms].value;
			return;
		}
		i++;
	}
	terms++;
	return;
}

template<typename T>
void SMatrix<T>::input()
{
	cout << "Please enter the size of non-zero and the number of terms: " << endl;
	cin >> rows >> cols >> terms;
	for (int i = 0; i < terms; i++) {
		cout << "Enter the row and the column of the term "
			<< (i + 1) <<endl;
		cin >> elements[i].row >> elements[i].col;
		cout << "Enter the value of the term (" << elements[i].row << "," << elements[i].col << ")" << endl;
		cin >> elements[i].value;
	}
	cout << endl;
	return;
}

template<typename T>
SMatrix<T> SMatrix<T>::mul(SMatrix<T> M0)
{
	SMatrix<T> MF(100);
	if (cols != M0.rows) {
		cout << "Wrong!" << endl;
		return MF;
	}
	MF.rows = rows;	MF.cols = M0.cols;
	T tmp = 0;
	for (int i = 0; i < terms; i++) {
		for (int j = 0; j < M0.terms; j++) {
			if ((elements[i].col == M0.elements[j].row)
				&&(elements[i].value != 0 && M0.elements[j].value != 0)) {
				tmp = elements[i].value * M0.elements[j].value;
				MF.append(elements[i].row, M0.elements[j].col, tmp);
			}
		}
	}
	return MF;
}

template<typename T>
void SMatrix<T>::print()
{
	cout << "terms = " << terms <<
		" rows = " << rows << 
		" columns = " << cols << endl;
	if (isEmpty()) cout << "Empty Matrix!" << endl;
	for (int i = 0; i < terms; i++) {
		cout << "elements(" << elements[i].row << "," << elements[i].col << ") = " << elements[i].value << endl;
	}
	cout << endl;
	return;
}

template<typename T>
bool SMatrix<T>::isEmpty()
{
	return terms == 0;
}

int main() {
	SMatrix<int> sm1(100), sm2(100);
	sm1.input();
	sm2.input();
	sm1.mul(sm2).print();
}