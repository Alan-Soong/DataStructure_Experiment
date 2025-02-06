#include <iostream>
#include <queue>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

// AVL树节点结构体
template<typename T>
struct AVLNode {
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    AVLNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// 获取节点的高度，若节点为空则返回0
template<typename T>
int getHeight(AVLNode<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// 更新节点的高度，取左右子树高度最大值加1
template<typename T>
void updateHeight(AVLNode<T>* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// 获取平衡因子，即左右子树高度差
template<typename T>
int getBalanceFactor(AVLNode<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// 右旋操作，用于调整树的平衡
template<typename T>
AVLNode<T>* rightRotate(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// 左旋操作，用于调整树的平衡
template<typename T>
AVLNode<T>* leftRotate(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// 插入节点到AVL树中，并返回新的根节点（插入过程中会维护树的平衡）
template<typename T>
AVLNode<T>* insert(AVLNode<T>* node, T data) {
    if (node == nullptr) {
        return new AVLNode<T>(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    else {
        cout << "same! " << endl;
        return node;
    }

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // LL情况
    if (balanceFactor > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    // RR情况
    if (balanceFactor < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    // LR情况
    if (balanceFactor > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL情况
    if (balanceFactor < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 计算AVL树的高度函数
template<typename T>
int getAVLTreeHeight(AVLNode<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

//以log n的复杂度计算树高
template<typename T>
int getAVLTreeHeight_self(AVLNode<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    if (getBalanceFactor(root) > 0) {
        return 1 + getAVLTreeHeight_self(root->left);
    }
    else {
        return 1 + getAVLTreeHeight_self(root->right);
    }
}


// 以层次遍历的方式打印AVL树，更直观地展示树结构
template<typename T>
void printTree(AVLNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    queue<AVLNode<T>*> q;
    queue<char> flag;
    q.push(root);
    flag.push('C');
    // int level = 1;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            AVLNode<T>* node = q.front();
            char tmp = flag.front();
            q.pop();
            flag.pop();
            /*for (int j = 0; j < 4 * (level - 1); j++) {
                cout << " ";
            }*/
            cout << node->data << "(" << tmp /* << "," << node->height*/ << ") ";
            if (node->left) {
                q.push(node->left);
                flag.push('L');
            }
            if (node->right) {
                q.push(node->right);
                flag.push('R');
            }
        }
        cout << endl;
        // level++;
    }
}

// 查找并返回AVL树中距离根节点最近的叶节点的值
template<typename T>
T findNearestLeafValue(AVLNode<T>* root) {
    if (root == nullptr) {
        throw std::runtime_error("树为空");
    }
    std::queue<AVLNode<T>*> q;
    q.push(root);
    while (!q.empty()) {
        AVLNode<T>* node = q.front();
        q.pop();
        // 如果当前节点是叶节点（没有左右子节点），则返回其值
        if (node->left == nullptr && node->right == nullptr) {
            return node->data;
        }
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
    // 正常情况下不会执行到这里，因为AVL树至少有一个叶节点
    throw std::runtime_error("未找到叶节点");
}



// 销毁AVL树的函数，用于释放内存，避免内存泄漏
template<typename T>
void destroyAVLTree(AVLNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    destroyAVLTree(root->left);
    destroyAVLTree(root->right);
    delete root;
}

int main() {
    // 设置随机数种子，使每次运行生成不同的随机数序列
    srand((unsigned int)time(NULL));

    int n = 0;
    cin >> n;
    AVLNode<int>* root = nullptr;
    // 插入节点构建AVL树
    for (int i = 0; i < n; i++) {
        int tmp = rand() % 101;
        cout << "Insert: " << tmp << endl;
        root = insert(root, tmp);
        printTree(root);
        cout << endl;
    }

    // 打印AVL树
    // printTree(root);

    // 计算并输出AVL树的高度
    int height = getAVLTreeHeight(root);
    int height_self = getAVLTreeHeight_self(root);
    cout << "AVL树的高度为: " << height << endl;
    cout << "AVL树的高度为: " << height_self << endl;

    try {
        // 查找并输出距离根节点最近的叶节点的值
        int nearestLeafValue = findNearestLeafValue(root);
        cout << "距离根节点最近的叶节点的值为: " << nearestLeafValue << endl;
    }
    catch (const std::runtime_error& e) {
        cerr << e.what() << endl;
    }

    // 释放AVL树占用的内存
    destroyAVLTree(root);

    return 0;
}