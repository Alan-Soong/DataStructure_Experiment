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
    //int weight = 1;

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

// ��������������������״�����ܳ���������ɫ�ڵ�
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

// ��������������µĽ�㣬�ظ�ֵ��Ȩ�� +1
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
        else if (m >= current->data) {
            current = current->right;
        }
        else {
            //current->weight++;
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
    if (findNode(root, m) == nullptr) {
        cout << m << " Not existed! " << endl;
    }
    while (findNode(root, m) != nullptr) {
        rb_Node* node = findNode(root, m);
        if (node == nullptr) {
            cout << "Node not found!" << endl;
            return root;
        }
        /*else if (node->weight > 1) {
            node->weight--;
            return root;
        }*/

        rb_Node* replacement;
        rb_Node* child;
        rb_Node* parent;
        Color originalColor = node->getColor();

        // Case 1: ��������
        if (node->left != nullptr && node->right != nullptr) {
            // �ҵ���̽ڵ�
            replacement = minValueNode(node->right);
            originalColor = replacement->getColor();
            child = replacement->right;
            parent = replacement->parent;

            if (child != nullptr) {
                child->parent = parent;
            }

            if (replacement != node->right) {
                parent->left = child;
                replacement->right = node->right;
                node->right->parent = replacement;
            }

            replacement->parent = node->parent;
            if (node->parent == nullptr) {
                root = replacement;
            }
            else if (node == node->parent->left) {
                node->parent->left = replacement;
            }
            else {
                node->parent->right = replacement;
            }

            replacement->left = node->left;
            node->left->parent = replacement;
            replacement->setColor(node->getColor());

            delete node;
            //return root;
            continue;
        }

        // Case 2: һ�����ӻ�û�к���
        if (node->left != nullptr) {
            child = node->left;
        }
        else {
            child = node->right;
        }

        parent = node->parent;
        if (child != nullptr) {
            child->parent = parent;
        }

        if (parent == nullptr) {
            root = child;
        }
        else if (node == parent->left) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }

        if (originalColor == Black) {
            fixRemove(root, child);  // ��Ҫ�޸�����ƽ��
        }

        delete node;
        
    }
    return root;
}


// �޸��������ƽ��
void rb_Tree::fixRemove(rb_Node* root, rb_Node* x) {
    rb_Node* sibling;
    while (x != root && x->getColor() == Black) {
        if (x == x->parent->left) {
            sibling = x->parent->right;
            if (sibling->getColor() == Red) {
                sibling->setColor(Black);
                x->parent->setColor(Red);
                leftRotate(x->parent);
                sibling = x->parent->right;
            }

            if (sibling->left->getColor() == Black && sibling->right->getColor() == Black) {
                sibling->setColor(Red);
                x = x->parent;
            }
            else {
                if (sibling->right->getColor() == Black) {
                    sibling->left->setColor(Black);
                    sibling->setColor(Red);
                    rightRotate(sibling);
                    sibling = x->parent->right;
                }

                sibling->setColor(x->parent->getColor());
                x->parent->setColor(Black);
                sibling->right->setColor(Black);
                leftRotate(x->parent);
                x = root;
            }
        }
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
    cin >> n;

    for (int i = 0; i < n; i++) {
        int tmp = rand() % 101;
        cout << "Insert: " << tmp << endl;
        tree.root = tree.insert(tmp);
        tree.ascend();
    }

    tree.root = tree.insert(20);
    tree.ascend();
    tree.root = tree.insert(20);
    tree.ascend();
    //if (tree.findNode(tree.root, 20) != nullptr) {
        //cout << "20 is existed! " << endl;
    //}
    //else {
        //cout << "20 isn't existed! " << endl;
    //}
    //cout << endl;
    tree.root = tree.remove(tree.root, 20);
    tree.ascend();  // ɾ�����������������
    tree.root = tree.remove(tree.root, 20);
    tree.ascend();  // ɾ�����������������

    return 0;
}
