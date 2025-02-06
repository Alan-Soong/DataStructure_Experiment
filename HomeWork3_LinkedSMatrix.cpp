#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// CNode�ṹ�嶨�壬�洢��ͷ�ڵ���к�ֵ
template<class T>
struct CNode {
    int col;    //ֻ�洢����
    T value;    //��ֵ
    CNode* next;    //ָ�룬ָ����һ��
    CNode() {
        col = 0;
        value = 0;
        next = NULL;
    }
    CNode(int c, T val) {
        col = c;
        value = val;
        next = NULL;
    }
};

// HeadNode�ṹ�嶨�壬�洢ͷ�ڵ㣬ֻ������ֵ
template<class T>
struct HeadNode {
    int row;    //�洢����
    CNode<T>* next; //ָ�룬����һ��ָ��CNode�����ڴ洢
    HeadNode() {
        row = 0;
        next = NULL;
    }
    HeadNode(int r) {
        row = r;
        next = NULL;
    }
};

// LinkedMatrix�ඨ�壬�洢����
template<class T>
class LinkedMatrix {
    int rows;   //���������
    int columns;    //���������
    vector<HeadNode<T>*> Matrix;    //����
public:
    //���캯��
    LinkedMatrix(int rs, int cls) {
        Matrix.resize(rs, NULL);
        rows = rs;
        columns = cls;
    }
    void insert(int r, int c, T val);   // ����Ԫ��
    T retrive(int r, int c); //ȡ����Ӧ��ֵ
    LinkedMatrix<T> add(LinkedMatrix<T> lm);    //����ӷ�
    LinkedMatrix<T> sub(LinkedMatrix<T> lm);    //�������
    LinkedMatrix<T> mul(LinkedMatrix<T> lm);    //����˷�
    LinkedMatrix<T> transpose();    //����ת��
    void printMatrix();  // ��ӡ����
};


template<class T>
void LinkedMatrix<T>::insert(int r, int c, T val) {
    if (r < 1 || r > rows || c < 0 || c > columns) {
        cout << "Error! Column index out of bounds." << endl;
        return;
    }
    CNode<T>* newNode = new CNode<T>(c, val);
    if (Matrix[r - 1] == NULL) {
        Matrix[r - 1] = new HeadNode<T>(r);
        Matrix[r - 1]->next = newNode;
    }
    else {
        CNode<T>* prev = NULL;
        CNode<T>* current = Matrix[r - 1]->next;
        while (current != NULL && current->col < c) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            // ����������ͷ��
            newNode->next = Matrix[r - 1]->next;
            Matrix[r - 1]->next = newNode;
        }
        else {
            // �������м��β��
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

template<class T>
T LinkedMatrix<T>::retrive(int r, int c)
{
    if (r < 1 || r > rows) {
        cout << "Error! Column index out of bounds." << endl;
        return -1;
    }
    if (Matrix[r - 1]->next == NULL) {
        return 0;
    }
    CNode<T>* current = Matrix[r - 1]->next;
    while (current->next != NULL) {
        if (current->col == c) {
            return current->value;
        }
        current = current->next;
    }
    return 0;
}

template<class T>
LinkedMatrix<T> LinkedMatrix<T>::add(LinkedMatrix lm)
{
    //�ж��Ƿ���ϼӷ�Ҫ��
    if ((columns != lm.columns) && (rows != lm.rows)) {
        cout << "Error! Can't add! " << endl;
        return LinkedMatrix<T>(0, 0);
    }

    LinkedMatrix<T> sum(rows, columns);
    
    //������ʱ��������ָ����������
    for (int i = 0; i < rows; i++) {
        CNode<T>* tmp1 = Matrix[i] ? Matrix[i]->next : NULL;
        CNode<T>* tmp2 = lm.Matrix[i] ? lm.Matrix[i]->next : NULL;
        while (tmp1 != NULL || tmp2 != NULL) {
            if (tmp1 == NULL) {
                if (tmp2->value) {
                    sum.insert(i + 1, tmp2->col, tmp2->value);
                }
                tmp2 = tmp2->next;
            }
            else if (tmp2 == NULL) {
                if (tmp1->value) {
                    sum.insert(i + 1, tmp1->col, tmp1->value);
                }
                tmp1 = tmp1->next;
            }
            else if (tmp1->col > tmp2->col) {
                if (tmp2->value) {
                    sum.insert(i + 1, tmp2->col, tmp2->value);
                }
                tmp2 = tmp2->next;
            }
            else if (tmp1->col < tmp2->col) {
                if (tmp1->value) {
                    sum.insert(i + 1, tmp1->col, tmp1->value);
                }
                tmp1 = tmp1->next;
            }
            else{
                T m = tmp1->value + tmp2->value;
                if (m) {
                    sum.insert(i + 1, tmp1->col, m);
                }
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }
        }
    }
    return sum;
}

template<class T>
LinkedMatrix<T> LinkedMatrix<T>::sub(LinkedMatrix lm)
{
    //�ж��Ƿ���ϼ���Ҫ��
    if ((columns != lm.columns) && (rows != lm.rows)) {
        cout << "Error! Can't sub! " << endl;
        return LinkedMatrix<T>(0, 0);
    }
    LinkedMatrix<T> sum(rows, columns);

    //������ʱ��������ָ����������
    for (int i = 0; i < rows; i++) {
        CNode<T>* tmp1 = Matrix[i] ? Matrix[i]->next : NULL;
        CNode<T>* tmp2 = lm.Matrix[i] ? lm.Matrix[i]->next : NULL;
        while (tmp1 != NULL || tmp2 != NULL) {
            if (tmp1 == NULL) {
                if (tmp2->value) {
                    sum.insert(i + 1, tmp2->col, -(tmp2->value));
                }
                tmp2 = tmp2->next;
            }
            else if (tmp2 == NULL) {
                if (tmp1->value) {
                    sum.insert(i + 1, tmp1->col, tmp1->value);
                }
                tmp1 = tmp1->next;
            }
            else if (tmp1->col > tmp2->col) {
                if (tmp2->value) {
                    sum.insert(i + 1, tmp2->col, -(tmp2->value));
                }
                tmp2 = tmp2->next;
            }
            else if (tmp1->col < tmp2->col) {
                if (tmp1->value) {
                    sum.insert(i + 1, tmp1->col, tmp1->value);
                }
                tmp1 = tmp1->next;
            }
            else {
                T s = tmp1->value - tmp2->value;
                if (s) {
                    sum.insert(i + 1, tmp1->col, s);
                }
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }
        }
    }
    return sum;
}

template<class T>
LinkedMatrix<T> LinkedMatrix<T>::mul(LinkedMatrix<T> lm)
{
    //�ж��Ƿ���ϳ˷�Ҫ��
    if (columns != lm.rows) {
        cout << "Invalid input! Can't mul! " << endl;
        return LinkedMatrix<T>(0, 0);
    }

    LinkedMatrix<T> trlm = lm.transpose();
    LinkedMatrix<T> result(rows, lm.columns);

    //ִ�г˷�������ת�þ����������ڹ�������Ĳ���
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < trlm.rows; j++) {
            T sum = 0;
            CNode<T>* rowNode = Matrix[i] ? Matrix[i]->next : NULL;
            CNode<T>* colNode = trlm.Matrix[j] ? trlm.Matrix[j]->next : NULL;
            for (int k = 0; k < columns; k++) {
                while (rowNode != NULL && colNode != NULL) {
                    if (rowNode->col == colNode->col) {
                        sum += rowNode->value * colNode->value;
                        rowNode = rowNode->next;
                        colNode = colNode->next;
                    }
                    else if (rowNode->col < colNode->col) {
                        rowNode = rowNode->next;
                    }
                    else {
                        colNode = colNode->next;
                    }
                }
            }
            if (sum != 0) {
                result.insert(i + 1, j + 1, sum);
            }
        }
    }
    return result;
}

template<class T>
LinkedMatrix<T> LinkedMatrix<T>::transpose() {
    // ����ת�ú�ľ������л���
    LinkedMatrix<T> transposedMatrix(columns, rows);
    for (int i = 0; i < rows; ++i) {
        CNode<T>* current = Matrix[i] ? Matrix[i]->next : NULL;
        while (current != NULL) {
            // ���л�������Ԫ��
            transposedMatrix.insert(current->col, i + 1, current->value);
            current = current->next;
        }
    }
    return transposedMatrix;
}


template<class T>
void LinkedMatrix<T>::printMatrix() {
    int count = 0;
    cout << "rows: " << rows << ", " << "columns: " << columns << endl;
    for (int i = 0; i < rows; i++) {
        HeadNode<T>* head = Matrix[i];
        if (head == NULL) {
            count++;
            //cout  << " __zero__ "  << endl;
            continue;
        }
        cout << "row " << i + 1 << ": ";
        
        CNode<T>* current = head->next;
        
        while (current != NULL) {
            cout << "(" << current->col << ", " << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
    if (count == rows) {
        cout << "Zero matrix! " << endl;
    }
    cout << endl;
}

// ���Ժ���
template<class T>
LinkedMatrix<T> testLinkedMatrix(int r, int c) {
    LinkedMatrix<int> matrix(r, c);  // ��������

    // ����һЩԪ��
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // ���� [1, 100] ��Χ�ڵ����������������Ԫ�أ����޸ķ�Χ
            matrix.insert(i + 1, j + 1, rand() % 100 + 1);
        }
    }

    return matrix;
}

template<class T>
LinkedMatrix<T> testLinkedSparseMatrix(int r, int c, double rate) {
    LinkedMatrix<int> matrix(r, c);  // ��������

    // ����һЩԪ��
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double random = static_cast<double>(rand()) / RAND_MAX;
            if (random < rate) {
                // ���� [1, 100] ��Χ�ڵ����������������Ԫ�أ����޸ķ�Χ
                matrix.insert(i + 1, j + 1, rand() % 100 + 1);
            }
        }
    }

    return matrix;
}

int main() {
    clock_t start = clock();

    LinkedMatrix<int> lm1 = testLinkedMatrix<int>(3, 4);
    LinkedMatrix<int> lm2 = testLinkedMatrix<int>(4, 3);
    LinkedMatrix<int> lm3 = testLinkedSparseMatrix<int>(400, 30, 0.001);
    LinkedMatrix<int> lm4 = testLinkedSparseMatrix<int>(30, 500, 0.0012);

    lm1.retrive(4, 4);
    lm1.add(lm2).printMatrix();
    lm1.mul(lm2).printMatrix();
    lm3.printMatrix();
    lm4.printMatrix();
    lm3.mul(lm4).printMatrix();

    clock_t end = clock();

    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    cout << "It takes " << duration << "s. " << endl;

    return 0;
}


