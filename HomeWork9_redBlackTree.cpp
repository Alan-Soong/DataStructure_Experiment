#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

enum Color {
    Black, Red
};

struct rb_Node {
    int data = 0;
    rb_Node* left;  //左指针
    rb_Node* right; //右指针
    rb_Node* parent;    //父指针
    Color c = Red;  //颜色

public:
    rb_Node(int m) {
        data = m;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    // 获取结点颜色
    Color getColor() {
        return c;
    }

    // 设置节点颜色
    void setColor(Color color) {
        if (this != nullptr) {
            c = color;
        }
    }
};

class rb_Tree {
public:
    rb_Node* root;
    rb_Tree() {
        root = NULL;
    }

    rb_Node* rightRotate(rb_Node* y);   //右旋
    rb_Node* leftRotate(rb_Node* x);    //左旋
    void adjustColorAfterInsert(rb_Node* current);  //调整插入后的树的颜色
    rb_Node* insert(int m);  //插入

    rb_Node* remove(rb_Node* root, int m);
    void fixRemove(rb_Node* root, rb_Node* x);    // 修复树的平衡
    rb_Node* findNode(rb_Node* root, int data);
    rb_Node* minValueNode(rb_Node* node);

    void ascend();  //中序遍历
    void inorderTraversal(rb_Node* node);
    //bool findNode(int m);
};

// 左旋操作：以x为根节点进行左旋，调整节点和父指针
rb_Node* rb_Tree::leftRotate(rb_Node* x) {
    rb_Node* y = x->right;
    rb_Node* T2 = y->left;

    // 进行左旋
    y->left = x;
    x->right = T2;

    // 更新父指针
    if (T2 != nullptr) {
        T2->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;  // 如果x是根节点，更新root
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    x->parent = y;

    return y;  // 返回旋转后的新根节点
}

// 右旋操作：以x为根节点进行右旋，调整节点和父指针
rb_Node* rb_Tree::rightRotate(rb_Node* y) {
    rb_Node* x = y->left;
    rb_Node* T2 = x->right;

    // 进行右旋
    x->right = y;
    y->left = T2;

    // 更新父指针
    if (T2 != nullptr) {
        T2->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;  // 如果x是根节点，更新root
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }

    y->parent = x;

    return x;  // 返回旋转后的新根节点
}

void rb_Tree::adjustColorAfterInsert(rb_Node* current) {
    // 根节点始终保持黑色
    root->setColor(Black);

    while (current != root && current->parent && current->parent->getColor() == Red) {
        rb_Node* grandparent = current->parent->parent;

        // 如果父节点是祖父节点的左子节点
        if (current->parent == grandparent->left) {
            rb_Node* uncle = grandparent->right;

            // Case 1: 叔叔节点是红色，重新着色
            if (uncle && uncle->getColor() == Red) {
                current->parent->setColor(Black);
                uncle->setColor(Black);
                grandparent->setColor(Red);
                current = grandparent;  // 继续向上调整
            }
            else {
                // Case 2: 当前节点是右子节点，进行左旋
                if (current == current->parent->right) {
                    current = current->parent;
                    leftRotate(current);  // 左旋
                }

                // Case 3: 当前节点是左子节点，进行右旋
                current->parent->setColor(Black);
                grandparent->setColor(Red);
                rightRotate(grandparent);  // 右旋
            }
        }
        // 如果父节点是祖父节点的右子节点
        else {
            rb_Node* uncle = grandparent->left;

            // Case 1: 叔叔节点是红色，重新着色
            if (uncle && uncle->getColor() == Red) {
                current->parent->setColor(Black);
                uncle->setColor(Black);
                grandparent->setColor(Red);
                current = grandparent;  // 继续向上调整
            }
            else {
                // Case 2: 当前节点是左子节点，进行右旋
                if (current == current->parent->left) {
                    current = current->parent;
                    rightRotate(current);  // 右旋
                }

                // Case 3: 当前节点是右子节点，进行左旋
                current->parent->setColor(Black);
                grandparent->setColor(Red);
                leftRotate(grandparent);  // 左旋
            }
        }
    }

    // 根节点始终保持黑色
    root->setColor(Black);
}

rb_Node* rb_Tree::insert(int m) {
    rb_Node* newNode = new rb_Node(m);  // 创建新节点
    if (root == NULL) {
        root = newNode;
        root->setColor(Black);  // 根节点始终为黑色
        return root;  // 如果树为空，直接返回新节点
    }

    rb_Node* current = root;
    rb_Node* parent0 = NULL;

    // 寻找插入位置
    while (current != NULL) {
        parent0 = current;
        if (m < current->data) {
            current = current->left;
        }
        else if (m > current->data) {
            current = current->right;
        }
        else {
            cout << "Same!" << endl;  // 如果已经存在相同值，直接返回
            delete newNode;  // 清理新创建的节点
            return root;
        }
    }

    // 插入新节点
    if (m < parent0->data) {
        parent0->left = newNode;
    }
    else {
        parent0->right = newNode;
    }
    newNode->parent = parent0;

    // 插入后调整颜色和结构
    adjustColorAfterInsert(newNode);  // 调用颜色调整函数

    return root;
}


// 删除节点
rb_Node* rb_Tree::remove(rb_Node* root, int m) {
    // 查找要删除的节点，没有的话返回
    rb_Node* node = findNode(root, m);
    if (node == nullptr) {
        cout << "Node not found!" << endl;
        return root;
    }

    rb_Node* replacement;   //替代被删除节点的节点
    rb_Node* child; //替代节点的子节点
    rb_Node* parent;    //替代节点的父节点
    Color originalColor = node->getColor(); //保存被删除节点的颜色

    // Case 1: Node has two children
    if (node->left != nullptr && node->right != nullptr) {
        // 找到后继节点（右子树的min）
        replacement = minValueNode(node->right);
        originalColor = replacement->getColor();    //替代节点的颜色
        child = replacement->right; //后继节点的右子节点
        parent = replacement->parent;   //后继节点的父节点

        // 后继节点与右子树断开，更新连接关系
        if (child != nullptr) {
            child->parent = parent;
        }

        if (replacement != node->right) {   // 如果后继节点不是直接右子节点
            parent->left = child;   // 替换后继节点为其子节点
            replacement->right = node->right;   // 更新后继节点的右子树为原节点的右子树
            node->right->parent = replacement;  // 更新右子树的父节点
        }

        // 将后继节点替换到原节点位置
        replacement->parent = node->parent; // 更新后继节点的父节点为原节点的父节点
        if (node->parent == nullptr) {  // 如果原节点是根节点
            root = replacement; // 后继节点成为新的根
        }
        else if (node == node->parent->left) {
            node->parent->left = replacement;
        }
        else {
            node->parent->right = replacement;
        }

        // 更新后继节点的左子树为原节点的左子树，保持后继节点的颜色为原节点的颜色
        replacement->left = node->left;
        node->left->parent = replacement;
        replacement->setColor(node->getColor());

        delete node;
        return root;
    }

    // Case 2: Node has one child or no children
    if (node->left != nullptr) {
        child = node->left;
    }
    else {
        child = node->right;
    }

    parent = node->parent;  // 保存原节点的父节点
    if (child != nullptr) {
        child->parent = parent; // 更新子节点的父节点为原节点的父节点
    }

    if (parent == nullptr) {    // 如果原节点是根节点
        root = child;   // 将子节点提升为根节点
    }
    else if (node == parent->left) {    // 如果原节点是左子节点
        parent->left = child;   // 更新父节点的左子树
    }
    else {  // 如果原节点是右子节点
        parent->right = child;  // 更新父节点的右子树
    }

    // 如果被删除的节点是黑色，需要修复红黑树性质
    if (originalColor == Black) {
        fixRemove(root, child);  // 需要修复树的平衡
    }

    delete node;
    return root;
}


// 修复红黑树的平衡
void rb_Tree::fixRemove(rb_Node* root, rb_Node* x) {
    rb_Node* sibling;   //兄弟节点

    // 循环：修复直到当前节点 `x` 不是根节点且其颜色为黑色
    while (x != root && x->getColor() == Black) {
        // 情况 1：当前节点是其父节点的左子节点
        if (x == x->parent->left) {
            sibling = x->parent->right;

            // 子情况 1.1：兄弟节点是红色
            if (sibling->getColor() == Red) {
                sibling->setColor(Black);
                x->parent->setColor(Red);
                leftRotate(x->parent);
                sibling = x->parent->right;
            }

            // 子情况 1.2：兄弟节点是黑色，且两个子节点均为黑色
            if (sibling->left->getColor() == Black && sibling->right->getColor() == Black) {
                sibling->setColor(Red);
                x = x->parent;
            }
            else {
                // 子情况 1.3：兄弟节点是黑色，且兄弟节点的右子节点为黑色，左子节点为红色
                if (sibling->right->getColor() == Black) {
                    sibling->left->setColor(Black);
                    sibling->setColor(Red);
                    rightRotate(sibling);
                    sibling = x->parent->right;
                }

                // 子情况 1.4：兄弟节点是黑色，且兄弟节点的右子节点为红色
                sibling->setColor(x->parent->getColor());
                x->parent->setColor(Black);
                sibling->right->setColor(Black);
                leftRotate(x->parent);
                x = root;
            }
        }

        // 情况 2：当前节点是其父节点的右子节点
        else {
            sibling = x->parent->left;
            if (sibling->getColor() == Red) {
                sibling->setColor(Black);
                x->parent->setColor(Red);
                rightRotate(x->parent);
                sibling = x->parent->left;
            }

            if (sibling->right->getColor() == Black && sibling->left->getColor() == Black) {
                sibling->setColor(Red);
                x = x->parent;
            }
            else {
                if (sibling->left->getColor() == Black) {
                    sibling->right->setColor(Black);
                    sibling->setColor(Red);
                    leftRotate(sibling);
                    sibling = x->parent->left;
                }

                sibling->setColor(x->parent->getColor());
                x->parent->setColor(Black);
                sibling->left->setColor(Black);
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    x->setColor(Black);
}

rb_Node* rb_Tree::findNode(rb_Node* root, int data) {
    rb_Node* current = root;
    while (current != nullptr) {
        if (data < current->data) {
            current = current->left;  // 如果 data 小于当前节点的值，去左子树
        }
        else if (data > current->data) {
            current = current->right;  // 如果 data 大于当前节点的值，去右子树
        }
        else {
            return current;  // 找到节点，返回该节点
        }
    }
    return nullptr;  // 没有找到节点，返回 nullptr
}

rb_Node* rb_Tree::minValueNode(rb_Node* node) {
    rb_Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

/*
void rb_Tree::ascend() {
    function<void(rb_Node*)> inorderTraversal = [&](rb_Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            switch (node->getColor()) {
            case 0: cout << "(Black)" << endl; break;
            case 1: cout << "(Red)" << endl; break;
            default: break;
            }
            inorderTraversal(node->right);
        }
        };
    inorderTraversal(root);
    cout << endl;
}*/

void rb_Tree::ascend() {
    // 中序遍历递归实现
    rb_Node* current = root;
    inorderTraversal(current);
    cout << endl;
}

void rb_Tree::inorderTraversal(rb_Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);  // 先遍历左子树
        cout << node->data << " ";     // 输出当前节点数据
        // 输出节点颜色
        switch (node->getColor()) {
        case Black: cout << "(Black)" << endl; break;
        case Red: cout << "(Red)" << endl; break;
        default: break;
        }
        inorderTraversal(node->right); // 再遍历右子树
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    rb_Tree tree;
    int n = 0;
    cout << "Please input the number of Nodes: " << endl;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int tmp = rand() % 101;
        cout << "Insert: " << tmp << endl;
        tree.root = tree.insert(tmp);
        tree.ascend();
    }
    
    tree.root = tree.insert(20);
    tree.ascend();
    if (tree.findNode(tree.root, 20) != nullptr) {
        cout << "20 is existed! " << endl;
    }
    else {
        cout << "20 isn't existed! " << endl;
    }
    cout << endl;
    tree.root = tree.remove(tree.root, 20);
    tree.ascend();  // 删除后中序遍历输出结果
    if (tree.findNode(tree.root, 20) != nullptr) {
        cout << "20 is existed! " << endl;
    }
    else {
        cout << "20 isn't existed! " << endl;
    }
    cout << endl;
    return 0;
}
