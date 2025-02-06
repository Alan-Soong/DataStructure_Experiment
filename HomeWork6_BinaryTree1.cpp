#include<iostream>
#include<stack>
using namespace std;

struct BinaryTreeNode {
	char value;
	BinaryTreeNode* LeftChildren;
	BinaryTreeNode* RightChildren;
public:
	BinaryTreeNode() {
		value = {};
		LeftChildren = NULL;
		RightChildren = NULL;
	}
	BinaryTreeNode(char str) {
		value = str;
		LeftChildren = NULL;
		RightChildren = NULL;
	}
};

class BinaryTree {
public:
	BinaryTreeNode* root;
	BinaryTree() {
		root = new BinaryTreeNode();
	}
	~BinaryTree() {};
	bool IsEmpty() const
	{
		return ((root) ? false : true);
	}
	bool isSpace(char a);
	bool isAlpha(char a);	//判断是否为操作数
	bool isOperator(char a);
	int precedence(char a);
	BinaryTreeNode* constructExpressionTree(const string& expression);
};

bool BinaryTree::isSpace(char a)
{
	return (a == ' ');
}

bool BinaryTree::isAlpha(char a)
{
	return (a >= 'a' && a <= 'z');
}

bool BinaryTree::isOperator(char a)
{
	return (a == '+' || a == '-' || a == '*' || a == '/');
}

int BinaryTree::precedence(char a)
{
	if (a == '+' || a == '-')	return 1;
	if (a == '*' || a == '/')	return 2;
	return 0;
}

BinaryTreeNode* BinaryTree::constructExpressionTree(const string& expression) {
	stack<BinaryTreeNode*> nodes;
	stack<char> operators;
	for (char a : expression) {
		if (isSpace(a)) {
			continue;
		}
		if (isAlpha(a)) {
			nodes.push(new BinaryTreeNode(a));
		}
		else if (a == '(') {
			operators.push(a);
		}
		else if (a == ')') {
			while (!operators.empty() && operators.top() != '(') {
				char op = operators.top(); operators.pop();
				BinaryTreeNode* right = nodes.top(); nodes.pop();
				BinaryTreeNode* left = nodes.top(); nodes.pop();
				BinaryTreeNode* node = new BinaryTreeNode(op);
				node->LeftChildren = left;
				node->RightChildren = right;
				nodes.push(node);
			}
			operators.pop();
		}
		else if (isOperator(a)) {
			while (!operators.empty() && precedence(operators.top()) >= precedence(a)) {
				char op = operators.top(); operators.pop();
				BinaryTreeNode* right = nodes.top(); nodes.pop();
				BinaryTreeNode* left = nodes.top(); nodes.pop();
				BinaryTreeNode* node = new BinaryTreeNode(op);
				node->LeftChildren = left;
				node->RightChildren = right;
				nodes.push(node);
			}
			operators.push(a);
		}
	}
	while (!operators.empty()) {
		char op = operators.top(); operators.pop();
		BinaryTreeNode* right = nodes.top(); nodes.pop();
		BinaryTreeNode* left = nodes.top(); nodes.pop();
		BinaryTreeNode* node = new BinaryTreeNode(op);
		node->LeftChildren = left;
		node->RightChildren = right;
		nodes.push(node);
	}
	return nodes.top();
}

void printExpressionTree(BinaryTreeNode* nd, int level = 0)
{
	if (nd == NULL) return;
	printExpressionTree(nd->RightChildren, level + 1);
	for (int i = 0; i < level; i++) {
		cout << "   ";
	}
	cout << nd->value << endl;
	printExpressionTree(nd->LeftChildren, level + 1);
}

int main() {
	string expression;
	cout << "请输入一个中缀表达式: ";
	cin >> expression;
	cout << endl;

	BinaryTree tree;
	tree.root = tree.constructExpressionTree(expression);

	printExpressionTree(tree.root);

	return 0;
}