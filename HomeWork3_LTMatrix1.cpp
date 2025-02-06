#include<iostream>
using namespace std;

template <class T>
class Term {
private:
    int row, col;
    T value;
};

template<typename T>
class SparseMatrix {
public:
    SparseMatrix(int maxTerms = 10);
    ~SparseMatrix() { delete[] a; }

    friend ostream& operator<<(ostream&, const SparseMatrix<T>&);
    friend istream& operator>>(istream&, SparseMatrix<T>&);

    void Transpose(SparseMatrix<T>& b) const;
    void Multiply(const SparseMatrix<T>& b, SparseMatrix<T>& c) const;
private:
    void Append(const Term<T>& t);
    int rows, cols;
    int terms;
    Term<T>* a;
    int MaxTerms;
};

template<typename T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
    // Sparse matrix constructor.
    if (maxTerms < 1) cout<<"Wrong!";
    MaxTerms = maxTerms;
    a = new Term<T>[MaxTerms];
    terms = rows = cols = 0;
}

template <class T>
ostream& operator<<(ostream& out,
    const SparseMatrix<T>& x)
{// Put *this in output stream.
    out << "rows = " << x.rows << " columns = "
        << x.cols << endl;
    out << "nonzero terms = " << x.terms << endl;

    for (int i = 0; i < x.terms; i++)
        out << "a(" << x.a[i].row << ',' << x.a[i].col
        << ") = " << x.a[i].value << endl;
    return out;
}

template<class T>
istream& operator>>(istream& in, SparseMatrix<T>& x)
{// Input a sparse matrix.
    cout << "Enter number of rows, columns, and terms"
        << endl;
    in >> x.rows >> x.cols >> x.terms;
    if (x.terms > x.MaxTerms) cout << "Wrong!";

    for (int i = 0; i < x.terms; i++) {
        cout << "Enter row, column, and value of term "
            << (i + 1) << endl;
        in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
    }
    return in;
}

template<class T>
void SparseMatrix<T>::
Transpose(SparseMatrix<T>& b) const
{// b保存转置结果.

   // make sure b has enough space
    if (terms > b.MaxTerms) throw NoMem();

    // set transpose characteristics
    b.cols = rows;
    b.rows = cols;
    b.terms = terms;
    // initialize to compute transpose
    int* ColSize, * RowNext;
    ColSize = new int[cols + 1];
    RowNext = new int[cols + 1];

    // find number of entries in each column of *this
    for (int i = 1; i <= cols; i++) // initialize
        ColSize[i] = 0;
    for (i = 0; i < terms; i++) // 计算每列元素数目
        ColSize[a[i].col]++;
    // 计算转置矩阵每行（原矩阵每列）第一个元素在b中位置
// 第i行起始位置：行1元素数+…+行i-1元素数
    RowNext[1] = 0;
    for (i = 2; i <= cols; i++)
        RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
    // perform the transpose copying from *this to b
    for (i = 0; i < terms; i++) {
        int j = RowNext[a[i].col]++; // a[i]在b中位置
        b.a[j].row = a[i].col;
        b.a[j].col = a[i].row;
        b.a[j].value = a[i].value;
    }
}

template<class T>
void SparseMatrix<T>::Append(const Term<T>& t)
{// Append a nonzero term t to *this.
    if (terms >= MaxTerms) throw NoMem();
    a[terms] = t;
    terms++;
}

int main() {
    
	cout << "Hello,world!" << endl;
}