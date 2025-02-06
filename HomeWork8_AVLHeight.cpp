#include <iostream>
#include <queue>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

// AVL���ڵ�ṹ��
template<typename T>
struct AVLNode {
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    AVLNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// ��ȡ�ڵ�ĸ߶ȣ����ڵ�Ϊ���򷵻�0
template<typename T>
int getHeight(AVLNode<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// ���½ڵ�ĸ߶ȣ�ȡ���������߶����ֵ��1
template<typename T>
void updateHeight(AVLNode<T>* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// ��ȡƽ�����ӣ������������߶Ȳ�
template<typename T>
int getBalanceFactor(AVLNode<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// �������������ڵ�������ƽ��
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

// �������������ڵ�������ƽ��
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

// ����ڵ㵽AVL���У��������µĸ��ڵ㣨��������л�ά������ƽ�⣩
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

    // LL���
    if (balanceFactor > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    // RR���
    if (balanceFactor < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    // LR���
    if (balanceFactor > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL���
    if (balanceFactor < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ����AVL���ĸ߶Ⱥ���
template<typename T>
int getAVLTreeHeight(AVLNode<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

//��log n�ĸ��Ӷȼ�������
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


// �Բ�α����ķ�ʽ��ӡAVL������ֱ�۵�չʾ���ṹ
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

// ���Ҳ�����AVL���о�����ڵ������Ҷ�ڵ��ֵ
template<typename T>
T findNearestLeafValue(AVLNode<T>* root) {
    if (root == nullptr) {
        throw std::runtime_error("��Ϊ��");
    }
    std::queue<AVLNode<T>*> q;
    q.push(root);
    while (!q.empty()) {
        AVLNode<T>* node = q.front();
        q.pop();
        // �����ǰ�ڵ���Ҷ�ڵ㣨û�������ӽڵ㣩���򷵻���ֵ
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
    // ��������²���ִ�е������ΪAVL��������һ��Ҷ�ڵ�
    throw std::runtime_error("δ�ҵ�Ҷ�ڵ�");
}



// ����AVL���ĺ����������ͷ��ڴ棬�����ڴ�й©
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
    // ������������ӣ�ʹÿ���������ɲ�ͬ�����������
    srand((unsigned int)time(NULL));

    int n = 0;
    cin >> n;
    AVLNode<int>* root = nullptr;
    // ����ڵ㹹��AVL��
    for (int i = 0; i < n; i++) {
        int tmp = rand() % 101;
        cout << "Insert: " << tmp << endl;
        root = insert(root, tmp);
        printTree(root);
        cout << endl;
    }

    // ��ӡAVL��
    // printTree(root);

    // ���㲢���AVL���ĸ߶�
    int height = getAVLTreeHeight(root);
    int height_self = getAVLTreeHeight_self(root);
    cout << "AVL���ĸ߶�Ϊ: " << height << endl;
    cout << "AVL���ĸ߶�Ϊ: " << height_self << endl;

    try {
        // ���Ҳ����������ڵ������Ҷ�ڵ��ֵ
        int nearestLeafValue = findNearestLeafValue(root);
        cout << "������ڵ������Ҷ�ڵ��ֵΪ: " << nearestLeafValue << endl;
    }
    catch (const std::runtime_error& e) {
        cerr << e.what() << endl;
    }

    // �ͷ�AVL��ռ�õ��ڴ�
    destroyAVLTree(root);

    return 0;
}