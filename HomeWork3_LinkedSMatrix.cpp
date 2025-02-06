#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// CNode结构体定义，存储非头节点的列和值
template<class T>
struct CNode {
    int col;    //只存储列数
    T value;    //数值
    CNode* next;    //指针，指向下一个
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

// HeadNode结构体定义，存储头节点，只含有行值
template<class T>
struct HeadNode {
    int row;    //存储行数
    CNode<T>* next; //指针，让下一个指向CNode，便于存储
    HeadNode() {
        row = 0;
        next = NULL;
    }
    HeadNode(int r) {
        row = r;
        next = NULL;
    }
};

// LinkedMatrix类定义，存储矩阵
template<class T>
class LinkedMatrix {
    int rows;   //矩阵的行数
    int columns;    //矩阵的列数
    vector<HeadNode<T>*> Matrix;    //矩阵
public:
    //构造函数
    LinkedMatrix(int rs, int cls) {
        Matrix.resize(rs, NULL);
        rows = rs;
        columns = cls;
    }
    void insert(int r, int c, T val);   // 插入元素
    T retrive(int r, int c); //取出对应的值
    LinkedMatrix<T> add(LinkedMatrix<T> lm);    //矩阵加法
    LinkedMatrix<T> sub(LinkedMatrix<T> lm);    //矩阵减法
    LinkedMatrix<T> mul(LinkedMatrix<T> lm);    //矩阵乘法
    LinkedMatrix<T> transpose();    //矩阵转置
    void printMatrix();  // 打印矩阵
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
            // 插入在链表头部
            newNode->next = Matrix[r - 1]->next;
            Matrix[r - 1]->next = newNode;
        }
        else {
            // 插入在中间或尾部
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
    //判断是否符合加法要求
    if ((columns != lm.columns) && (rows != lm.rows)) {
        cout << "Error! Can't add! " << endl;
        return LinkedMatrix<T>(0, 0);
    }

    LinkedMatrix<T> sum(rows, columns);
    
    //两个临时变量各自指向两个矩阵
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
    //判断是否符合减法要求
    if ((columns != lm.columns) && (rows != lm.rows)) {
        cout << "Error! Can't sub! " << endl;
        return LinkedMatrix<T>(0, 0);
    }
    LinkedMatrix<T> sum(rows, columns);

    //两个临时变量各自指向两个矩阵
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
    //判断是否符合乘法要求
    if (columns != lm.rows) {
        cout << "Invalid input! Can't mul! " << endl;
        return LinkedMatrix<T>(0, 0);
    }

    LinkedMatrix<T> trlm = lm.transpose();
    LinkedMatrix<T> result(rows, lm.columns);

    //执行乘法，利用转置矩阵做类似于哈德马积的操作
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
    // 创建转置后的矩阵，行列互换
    LinkedMatrix<T> transposedMatrix(columns, rows);
    for (int i = 0; i < rows; ++i) {
        CNode<T>* current = Matrix[i] ? Matrix[i]->next : NULL;
        while (current != NULL) {
            // 行列互换插入元素
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

// 测试函数
template<class T>
LinkedMatrix<T> testLinkedMatrix(int r, int c) {
    LinkedMatrix<int> matrix(r, c);  // 创建矩阵

    // 插入一些元素
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // 生成 [1, 100] 范围内的随机整数，填充矩阵元素，可修改范围
            matrix.insert(i + 1, j + 1, rand() % 100 + 1);
        }
    }

    return matrix;
}

template<class T>
LinkedMatrix<T> testLinkedSparseMatrix(int r, int c, double rate) {
    LinkedMatrix<int> matrix(r, c);  // 创建矩阵

    // 插入一些元素
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double random = static_cast<double>(rand()) / RAND_MAX;
            if (random < rate) {
                // 生成 [1, 100] 范围内的随机整数，填充矩阵元素，可修改范围
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


