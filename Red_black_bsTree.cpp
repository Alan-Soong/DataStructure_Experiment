/*#include<iostream>
using namespace std;

//# define Black true
//# define Red false

enum Color {
    Red,
    Black
};

struct rb_BSTNode
{
    int index;
	int data;
	rb_BSTNode* left;
	rb_BSTNode* right;
    rb_BSTNode* parent;
	Color color;
    rb_BSTNode(int i, int v) {
        index = i;
        data = v;
        left = right = parent = NULL;
        color = Red;
    }
};

class rb_BST {
public:
    rb_BSTNode* root;
	rb_BST(){
		root = NULL;
	}
    void insert(int i, int m);
    void remove(int i);
    rb_BSTNode* find(int i);
    bool ascend(rb_BSTNode* nd);
    rb_BSTNode* rightRotate(rb_BSTNode* y);
    rb_BSTNode* leftRotate(rb_BSTNode* x);
    void VLRascend(rb_BSTNode* nd);
    void fixed_insert(rb_BSTNode* z);
    void fixed_remove(rb_BSTNode* z);
};

rb_BSTNode* rb_BST::find(int i)
{
    rb_BSTNode* p = root;
    while (p != NULL) {
        if (i < p->index) {
            p = p->left;
        }
        else {
            if (i > p->index) {
                p = p->right;
            }
            else {
                return p;
            }
        }
    }
    return nullptr;
}

void rb_BST::VLRascend(rb_BSTNode* nd)
{
    if (nd != NULL) {
        cout << nd->index << ", " << nd->data << " (Color: " << (nd->color == Red ? "Red" : "Black") << ")" << endl;
        VLRascend(nd->left);
        VLRascend(nd->right);
    }
}

rb_BSTNode* rb_BST::rightRotate(rb_BSTNode* y)
{
    rb_BSTNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
    return x;
}

rb_BSTNode* rb_BST::leftRotate(rb_BSTNode* x)
{
    rb_BSTNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
}

void rb_BST::fixed_insert(rb_BSTNode* z)
{
    while (z != root && z->parent->color == Red) {
        if (z->parent == z->parent->parent->left) {
            rb_BSTNode* y = z->parent->parent->right;
            if (y != NULL && y->color == Red) {
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = Black;
                z->parent->parent->color = Red;
                rightRotate(z->parent->parent);
            }
        }
        else {
            rb_BSTNode* y = z->parent->parent->left;
            if (y != NULL && y->color == Red) {
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = Black;
                z->parent->parent->color = Red;
                rightRotate(z->parent->parent);
            }
        }
        root->color = Black;
    }
}

void rb_BST::insert(int i, int m)
{
    rb_BSTNode* p = root;
    rb_BSTNode* pp = NULL;
    while (p != NULL) {
        pp = p;
        if (i < p->index) {
            p = p->left;
        }
        else {
            if (i > p->index) {
                p = p->right;
            }
            else {
                p->data = m;
                return;
            }
        }
    }
    rb_BSTNode* tmp = new rb_BSTNode(i, m);
    if (root != NULL) {
        if (i < pp->index) {
            pp->left = tmp;
        }
        else{
            pp->right = tmp;
        }
        tmp->parent = pp;
    }
    else {
        root = tmp;
    }
    fixed_insert(tmp);
}

rb_BSTNode* successor(rb_BSTNode* x) {
    if (x->right != NULL) {
        rb_BSTNode* p = x->right;
        while (p->left != NULL) {
            p = p->left;
        }
        return p;
    }
    rb_BSTNode* p = x->parent;
    while (p != NULL && x == p->right) {
        x = p;
        p = p->parent;
    }
    return p;
}

void rb_BST::fixed_remove(rb_BSTNode* z) {
    while (z != root && (z == NULL || z->color == Black)) {
        if (z == z->parent->left) {
            rb_BSTNode* y = z->parent->right;
            if (y->color == Red) {
                y->color = Black;
                z->parent->color = Red;
                leftRotate(z->parent);
                y = z->parent->right;
            }
            if ((y->left == NULL || y->left->color == Black)||(y->right == NULL || y->right->color == Black)) {
                    y->color = Red;
                    z = z->parent;
            }
            else {
                if (y->right == NULL || y->right->color == Black) {
                    y->left->color = Black;
                    y->color = Red;
                    rightRotate(y);
                    y = z->parent->right;
                }
                y->color = z->parent->color;
                z->parent->color = Black;
                y->right->color = Black;
                leftRotate(z->parent);
                z = root;
            }
        }
        else {
            rb_BSTNode* y = z->parent->left;
            if (y->color == Red) {
                y->color = Black;
                z->parent->color = Red;
                rightRotate(z->parent);
                y = z->parent->left;
            }
            if ((y->right == NULL || y->right->color == Black) || (y->left == NULL || y->left->color == Black)) {
                y->color = Red;
                z = z->parent;
            }
            else {
                if (y->left == NULL || y->left->color == Black) {
                    y->right->color = Black;
                    y->color = Red;
                    leftRotate(y);
                    y = z->parent->left;
                }
                y->color = z->parent->color;
                z->parent->color = Black;
                y->left->color = Black;
                rightRotate(z->parent);
                z = root;
            }
        }
    }
    if (z != NULL) {
        z->color = Black;
    }
}

void rb_BST::remove(int i)
{
    rb_BSTNode* z = find(i);
    if (z == NULL) {
        return;
    }
    rb_BSTNode* y = z;
    Color y_original_color = y->color;
    rb_BSTNode* x;
    if (z->left == NULL) {
        x = z->right;
        if (z->parent == NULL) {
            root = x;
        }
        else {
            if (z == z->parent->left) {
                z->parent->left = x;
            }
            else {
                z->parent->right = x;
            }
            if (x != NULL) {
                x->parent = z->parent;
            }
        }
    }
    else if (z->right == NULL) {
        x = z->left;
        if (z->parent == NULL) {
            root = x;
        }
        else {
            if (z == z->parent->left) {
                z->parent->left = x;
            }
            else {
                z->parent->right = x;
            }
            if (x != NULL) {
                x->parent = z->parent;
            }
        }
    }
    else {
        y = successor(z);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        }
        else {
            if (y->parent != NULL) {
                y->parent->right = x;
            }
            if (x != NULL) {
                x->parent = y->parent;
            }
            y->right = z->right;
            z->right->parent = y;
        }
        y->left = z->left;
        z->left->parent = y;
        y->parent = z->parent;
        if (z->parent == NULL) {
            root = y;
        }
        else {
            if (z == z->parent->left) {
                z->parent->left = y;
            }
            else {
                z->parent->right = y;
            }
        }
    }
    if (y_original_color == Black) {
        fixed_remove(x);
    }
    delete z;
}

bool rb_BST::ascend(rb_BSTNode* nd)
{
    if (nd == NULL) {
        return false;
    }
    else {
        cout << nd->index << ", " << nd->data << endl;
        ascend(nd->left);
        ascend(nd->right);
    }
    return true;
}

int main() {
    rb_BST* tree = new rb_BST();
    tree->insert(1, 2);
    tree->insert(2, 3);
    tree->insert(3, 1);
    tree->insert(9, 6);
    tree->insert(5, 4);
    tree->insert(6, 5);
    tree->insert(7, 9);
    tree->insert(8, 7);
    tree->VLRascend(tree->root);
    tree->remove(5);
    cout << endl;
    tree->VLRascend(tree->root);
    cout << "Hello, world!" << endl;
    return 0;
}*/

#include <iostream>
using namespace std;

// 定义红黑树节点颜色，这里用枚举类型更清晰
enum Color {
    RED,
    BLACK
};

struct rb_BSTNode {
    int index;
    int data;
    rb_BSTNode* left;
    rb_BSTNode* right;
    rb_BSTNode* parent;
    Color color;
    rb_BSTNode(int i, int v) {
        index = i;
        data = v;
        left = right = parent = NULL;
        color = RED;  // 新插入节点初始化为红色
    }
};

class rb_BST {
public:
    rb_BSTNode* root;
    rb_BST() {
        root = NULL;
    }
    void insert(int i, int m);
    void remove(int i);
    rb_BSTNode* find(int i);  // 增加查找节点的函数声明
    void inorderTraversal(rb_BSTNode* nd);  // 中序遍历打印函数声明，替代原ascend
    rb_BSTNode* rightRotate(rb_BSTNode* y);
    rb_BSTNode* leftRotate(rb_BSTNode* x);
    void fixInsertion(rb_BSTNode* z);  // 插入后修复红黑树性质的函数声明
    void fixDeletion(rb_BSTNode* x);  // 删除后修复红黑树性质的函数声明
};

// 查找节点函数实现
rb_BSTNode* rb_BST::find(int i) {
    rb_BSTNode* p = root;
    while (p != NULL) {
        if (i < p->index) {
            p = p->left;
        }
        else if (i > p->index) {
            p = p->right;
        }
        else {
            return p;
        }
    }
    return NULL;
}

// 中序遍历打印函数实现，用于按顺序查看树中节点
void rb_BST::inorderTraversal(rb_BSTNode* nd) {
    if (nd != NULL) {
        inorderTraversal(nd->left);
        cout << nd->index << ", " << nd->data << " (Color: " << (nd->color == RED ? "RED" : "BLACK") << ")" << endl;
        inorderTraversal(nd->right);
    }
}

// 右旋操作
rb_BSTNode* rb_BST::rightRotate(rb_BSTNode* y) {
    rb_BSTNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
    return x;
}

// 左旋操作
rb_BSTNode* rb_BST::leftRotate(rb_BSTNode* x) {
    rb_BSTNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
}

// 插入后修复红黑树性质
void rb_BST::fixInsertion(rb_BSTNode* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rb_BSTNode* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else {
            rb_BSTNode* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// 插入函数，在基本插入基础上调用修复函数维护红黑树性质
void rb_BST::insert(int i, int m) {
    rb_BSTNode* p = root;
    rb_BSTNode* pp = NULL;
    while (p != NULL) {
        pp = p;
        if (i < p->index) {
            p = p->left;
        }
        else {
            if (i > p->index) {
                p = p->right;
            }
            else {
                p->data = m;
                return;
            }
        }
    }
    rb_BSTNode* tmp = new rb_BSTNode(i, m);
    if (root != NULL) {
        if (i < pp->index) {
            pp->left = tmp;
        }
        else {
            pp->right = tmp;
        }
        tmp->parent = pp;
    }
    else {
        root = tmp;
    }
    fixInsertion(tmp);
}

// 获取节点的后继节点（用于删除操作中找替代节点）
rb_BSTNode* successor(rb_BSTNode* x) {
    if (x->right != NULL) {
        rb_BSTNode* p = x->right;
        while (p->left != NULL) {
            p = p->left;
        }
        return p;
    }
    rb_BSTNode* p = x->parent;
    while (p != NULL && x == p->right) {
        x = p;
        p = p->parent;
    }
    return p;
}

// 删除后修复红黑树性质
void rb_BST::fixDeletion(rb_BSTNode* x) {
    while (x != root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            rb_BSTNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right == NULL || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            rb_BSTNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) && (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left == NULL || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    if (x != NULL) {
        x->color = BLACK;
    }
}

// 删除函数，在基本删除基础上调用修复函数维护红黑树性质
void rb_BST::remove(int i) {
    rb_BSTNode* z = find(i);
    if (z == NULL) {
        return;
    }
    rb_BSTNode* y = z;
    Color y_original_color = y->color;
    rb_BSTNode* x;
    if (z->left == NULL) {
        x = z->right;
        if (z->parent == NULL) {
            root = x;
        }
        else {
            if (z == z->parent->left) {
                z->parent->left = x;
            }
            else {
                z->parent->right = x;
            }
            if (x != NULL) {
                x->parent = z->parent;
            }
        }
    }
    else if (z->right == NULL) {
        x = z->left;
        if (z->parent == NULL) {
            root = x;
        }
        else {
            if (z == z->parent->left) {
                z->parent->left = x;
            }
            else {
                z->parent->right = x;
            }
            if (x != NULL) {
                x->parent = z->parent;
            }
        }
    }
    else {
        y = successor(z);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        }
        else {
            if (y->parent != NULL) {
                y->parent->right = x;
            }
            if (x != NULL) {
                x->parent = y->parent;
            }
            y->right = z->right;
            z->right->parent = y;
        }
        y->left = z->left;
        z->left->parent = y;
        y->parent = z->parent;
        if (z->parent == NULL) {
            root = y;
        }
        else {
            if (z == z->parent->left) {
                z->parent->left = y;
            }
            else {
                z->parent->right = y;
            }
        }
    }
    if (y_original_color == BLACK) {
        fixDeletion(x);
    }
    delete z;
}

int main() {
    rb_BST* tree = new rb_BST();
    tree->insert(1, 2);
    tree->insert(2, 3);
    tree->insert(3, 1);
    tree->insert(9, 6);
    tree->insert(5, 4);
    tree->insert(6, 5);
    tree->insert(7, 9);
    tree->insert(8, 7);
    tree->inorderTraversal(tree->root);
    tree->remove(5);
    cout << endl;
    tree->inorderTraversal(tree->root);
    cout << "Hello, world!" << endl;
    return 0;
}