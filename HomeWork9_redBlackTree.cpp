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
    rb_Node* left;  //��ָ��
    rb_Node* right; //��ָ��
    rb_Node* parent;    //��ָ��
    Color c = Red;  //��ɫ

public:
    rb_Node(int m) {
        data = m;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    // ��ȡ�����ɫ
    Color getColor() {
        return c;
    }

    // ���ýڵ���ɫ
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

    rb_Node* rightRotate(rb_Node* y);   //����
    rb_Node* leftRotate(rb_Node* x);    //����
    void adjustColorAfterInsert(rb_Node* current);  //����������������ɫ
    rb_Node* insert(int m);  //����

    rb_Node* remove(rb_Node* root, int m);
    void fixRemove(rb_Node* root, rb_Node* x);    // �޸�����ƽ��
    rb_Node* findNode(rb_Node* root, int data);
    rb_Node* minValueNode(rb_Node* node);

    void ascend();  //�������
    void inorderTraversal(rb_Node* node);
    //bool findNode(int m);
};

// ������������xΪ���ڵ���������������ڵ�͸�ָ��
rb_Node* rb_Tree::leftRotate(rb_Node* x) {
    rb_Node* y = x->right;
    rb_Node* T2 = y->left;

    // ��������
    y->left = x;
    x->right = T2;

    // ���¸�ָ��
    if (T2 != nullptr) {
        T2->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;  // ���x�Ǹ��ڵ㣬����root
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    x->parent = y;

    return y;  // ������ת����¸��ڵ�
}

// ������������xΪ���ڵ���������������ڵ�͸�ָ��
rb_Node* rb_Tree::rightRotate(rb_Node* y) {
    rb_Node* x = y->left;
    rb_Node* T2 = x->right;

    // ��������
    x->right = y;
    y->left = T2;

    // ���¸�ָ��
    if (T2 != nullptr) {
        T2->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;  // ���x�Ǹ��ڵ㣬����root
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }

    y->parent = x;

    return x;  // ������ת����¸��ڵ�
}

void rb_Tree::adjustColorAfterInsert(rb_Node* current) {
    // ���ڵ�ʼ�ձ��ֺ�ɫ
    root->setColor(Black);

    while (current != root && current->parent && current->parent->getColor() == Red) {
        rb_Node* grandparent = current->parent->parent;

        // ������ڵ����游�ڵ�����ӽڵ�
        if (current->parent == grandparent->left) {
            rb_Node* uncle = grandparent->right;

            // Case 1: ����ڵ��Ǻ�ɫ��������ɫ
            if (uncle && uncle->getColor() == Red) {
                current->parent->setColor(Black);
                uncle->setColor(Black);
                grandparent->setColor(Red);
                current = grandparent;  // �������ϵ���
            }
            else {
                // Case 2: ��ǰ�ڵ������ӽڵ㣬��������
                if (current == current->parent->right) {
                    current = current->parent;
                    leftRotate(current);  // ����
                }

                // Case 3: ��ǰ�ڵ������ӽڵ㣬��������
                current->parent->setColor(Black);
                grandparent->setColor(Red);
                rightRotate(grandparent);  // ����
            }
        }
        // ������ڵ����游�ڵ�����ӽڵ�
        else {
            rb_Node* uncle = grandparent->left;

            // Case 1: ����ڵ��Ǻ�ɫ��������ɫ
            if (uncle && uncle->getColor() == Red) {
                current->parent->setColor(Black);
                uncle->setColor(Black);
                grandparent->setColor(Red);
                current = grandparent;  // �������ϵ���
            }
            else {
                // Case 2: ��ǰ�ڵ������ӽڵ㣬��������
                if (current == current->parent->left) {
                    current = current->parent;
                    rightRotate(current);  // ����
                }

                // Case 3: ��ǰ�ڵ������ӽڵ㣬��������
                current->parent->setColor(Black);
                grandparent->setColor(Red);
                leftRotate(grandparent);  // ����
            }
        }
    }

    // ���ڵ�ʼ�ձ��ֺ�ɫ
    root->setColor(Black);
}

rb_Node* rb_Tree::insert(int m) {
    rb_Node* newNode = new rb_Node(m);  // �����½ڵ�
    if (root == NULL) {
        root = newNode;
        root->setColor(Black);  // ���ڵ�ʼ��Ϊ��ɫ
        return root;  // �����Ϊ�գ�ֱ�ӷ����½ڵ�
    }

    rb_Node* current = root;
    rb_Node* parent0 = NULL;

    // Ѱ�Ҳ���λ��
    while (current != NULL) {
        parent0 = current;
        if (m < current->data) {
            current = current->left;
        }
        else if (m > current->data) {
            current = current->right;
        }
        else {
            cout << "Same!" << endl;  // ����Ѿ�������ֵͬ��ֱ�ӷ���
            delete newNode;  // �����´����Ľڵ�
            return root;
        }
    }

    // �����½ڵ�
    if (m < parent0->data) {
        parent0->left = newNode;
    }
    else {
        parent0->right = newNode;
    }
    newNode->parent = parent0;

    // ����������ɫ�ͽṹ
    adjustColorAfterInsert(newNode);  // ������ɫ��������

    return root;
}


// ɾ���ڵ�
rb_Node* rb_Tree::remove(rb_Node* root, int m) {
    // ����Ҫɾ���Ľڵ㣬û�еĻ�����
    rb_Node* node = findNode(root, m);
    if (node == nullptr) {
        cout << "Node not found!" << endl;
        return root;
    }

    rb_Node* replacement;   //�����ɾ���ڵ�Ľڵ�
    rb_Node* child; //����ڵ���ӽڵ�
    rb_Node* parent;    //����ڵ�ĸ��ڵ�
    Color originalColor = node->getColor(); //���汻ɾ���ڵ����ɫ

    // Case 1: Node has two children
    if (node->left != nullptr && node->right != nullptr) {
        // �ҵ���̽ڵ㣨��������min��
        replacement = minValueNode(node->right);
        originalColor = replacement->getColor();    //����ڵ����ɫ
        child = replacement->right; //��̽ڵ�����ӽڵ�
        parent = replacement->parent;   //��̽ڵ�ĸ��ڵ�

        // ��̽ڵ����������Ͽ����������ӹ�ϵ
        if (child != nullptr) {
            child->parent = parent;
        }

        if (replacement != node->right) {   // �����̽ڵ㲻��ֱ�����ӽڵ�
            parent->left = child;   // �滻��̽ڵ�Ϊ���ӽڵ�
            replacement->right = node->right;   // ���º�̽ڵ��������Ϊԭ�ڵ��������
            node->right->parent = replacement;  // �����������ĸ��ڵ�
        }

        // ����̽ڵ��滻��ԭ�ڵ�λ��
        replacement->parent = node->parent; // ���º�̽ڵ�ĸ��ڵ�Ϊԭ�ڵ�ĸ��ڵ�
        if (node->parent == nullptr) {  // ���ԭ�ڵ��Ǹ��ڵ�
            root = replacement; // ��̽ڵ��Ϊ�µĸ�
        }
        else if (node == node->parent->left) {
            node->parent->left = replacement;
        }
        else {
            node->parent->right = replacement;
        }

        // ���º�̽ڵ��������Ϊԭ�ڵ�������������ֺ�̽ڵ����ɫΪԭ�ڵ����ɫ
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

    parent = node->parent;  // ����ԭ�ڵ�ĸ��ڵ�
    if (child != nullptr) {
        child->parent = parent; // �����ӽڵ�ĸ��ڵ�Ϊԭ�ڵ�ĸ��ڵ�
    }

    if (parent == nullptr) {    // ���ԭ�ڵ��Ǹ��ڵ�
        root = child;   // ���ӽڵ�����Ϊ���ڵ�
    }
    else if (node == parent->left) {    // ���ԭ�ڵ������ӽڵ�
        parent->left = child;   // ���¸��ڵ��������
    }
    else {  // ���ԭ�ڵ������ӽڵ�
        parent->right = child;  // ���¸��ڵ��������
    }

    // �����ɾ���Ľڵ��Ǻ�ɫ����Ҫ�޸����������
    if (originalColor == Black) {
        fixRemove(root, child);  // ��Ҫ�޸�����ƽ��
    }

    delete node;
    return root;
}


// �޸��������ƽ��
void rb_Tree::fixRemove(rb_Node* root, rb_Node* x) {
    rb_Node* sibling;   //�ֵܽڵ�

    // ѭ�����޸�ֱ����ǰ�ڵ� `x` ���Ǹ��ڵ�������ɫΪ��ɫ
    while (x != root && x->getColor() == Black) {
        // ��� 1����ǰ�ڵ����丸�ڵ�����ӽڵ�
        if (x == x->parent->left) {
            sibling = x->parent->right;

            // ����� 1.1���ֵܽڵ��Ǻ�ɫ
            if (sibling->getColor() == Red) {
                sibling->setColor(Black);
                x->parent->setColor(Red);
                leftRotate(x->parent);
                sibling = x->parent->right;
            }

            // ����� 1.2���ֵܽڵ��Ǻ�ɫ���������ӽڵ��Ϊ��ɫ
            if (sibling->left->getColor() == Black && sibling->right->getColor() == Black) {
                sibling->setColor(Red);
                x = x->parent;
            }
            else {
                // ����� 1.3���ֵܽڵ��Ǻ�ɫ�����ֵܽڵ�����ӽڵ�Ϊ��ɫ�����ӽڵ�Ϊ��ɫ
                if (sibling->right->getColor() == Black) {
                    sibling->left->setColor(Black);
                    sibling->setColor(Red);
                    rightRotate(sibling);
                    sibling = x->parent->right;
                }

                // ����� 1.4���ֵܽڵ��Ǻ�ɫ�����ֵܽڵ�����ӽڵ�Ϊ��ɫ
                sibling->setColor(x->parent->getColor());
                x->parent->setColor(Black);
                sibling->right->setColor(Black);
                leftRotate(x->parent);
                x = root;
            }
        }

        // ��� 2����ǰ�ڵ����丸�ڵ�����ӽڵ�
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
            current = current->left;  // ��� data С�ڵ�ǰ�ڵ��ֵ��ȥ������
        }
        else if (data > current->data) {
            current = current->right;  // ��� data ���ڵ�ǰ�ڵ��ֵ��ȥ������
        }
        else {
            return current;  // �ҵ��ڵ㣬���ظýڵ�
        }
    }
    return nullptr;  // û���ҵ��ڵ㣬���� nullptr
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
    // ��������ݹ�ʵ��
    rb_Node* current = root;
    inorderTraversal(current);
    cout << endl;
}

void rb_Tree::inorderTraversal(rb_Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);  // �ȱ���������
        cout << node->data << " ";     // �����ǰ�ڵ�����
        // ����ڵ���ɫ
        switch (node->getColor()) {
        case Black: cout << "(Black)" << endl; break;
        case Red: cout << "(Red)" << endl; break;
        default: break;
        }
        inorderTraversal(node->right); // �ٱ���������
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
    tree.ascend();  // ɾ�����������������
    if (tree.findNode(tree.root, 20) != nullptr) {
        cout << "20 is existed! " << endl;
    }
    else {
        cout << "20 isn't existed! " << endl;
    }
    cout << endl;
    return 0;
}
