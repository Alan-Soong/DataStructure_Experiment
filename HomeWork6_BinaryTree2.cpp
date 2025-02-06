#include<iostream>
#include<queue>
using namespace std;

class BinaryTreeNode {
public:
	int value;
	BinaryTreeNode* LeftChildren;
	BinaryTreeNode* RightChildren;
	BinaryTreeNode() {
		value = 0;
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
	BinaryTreeNode* root;
	int countLeaves(BinaryTreeNode* node);
	void swapLRTree(BinaryTreeNode* node);
	int heightTree(BinaryTreeNode* node);
public:
	BinaryTree() {
		root = new BinaryTreeNode();
	}
	~BinaryTree() {};

	void createSampleTree() {
		root = new BinaryTreeNode(1);
		root->LeftChildren = new BinaryTreeNode(2);
		root->RightChildren = new BinaryTreeNode(3);
		root->LeftChildren->LeftChildren = new BinaryTreeNode(4);
		root->LeftChildren->RightChildren = new BinaryTreeNode(5);
		root->RightChildren->RightChildren = new BinaryTreeNode(6);
	}

	int CountLeaves() {
		return countLeaves(root);
	}
	void SwapLRTree() {
		swapLRTree(root);
	}
	int HeightTree() {
		return heightTree(root);
	}
	void LevelTraversal() {
		if (root == NULL) return;
		queue<BinaryTreeNode*> Q;
		Q.push(root);

		while (!Q.empty()) {
			BinaryTreeNode* current = Q.front();
			Q.pop();
			cout << current->value;

			if (current->LeftChildren != nullptr) Q.push(current->LeftChildren);
			if (current->RightChildren != nullptr) Q.push(current->RightChildren);
			if (!Q.empty())cout << " ";
		}
		return;
	}
	int WidthTree() {
		if (root == NULL) return 0;
		queue<BinaryTreeNode*> Q;
		Q.push(root);
		int maxnum = 0;
		while (!Q.empty()) {
			int levelWidth = Q.size();  // 当前层节点数
			maxnum = max(maxnum, levelWidth);

			for (int i = 0; i < levelWidth; ++i) {
				BinaryTreeNode* current = Q.front();
				Q.pop();
				if (current->LeftChildren != nullptr) Q.push(current->LeftChildren);
				if (current->RightChildren != nullptr) Q.push(current->RightChildren);
			}
		}
		return maxnum;
	}
};

int BinaryTree::countLeaves(BinaryTreeNode* node)
{
	if (node == NULL) return 0;
	if (node->LeftChildren == NULL && node->RightChildren == NULL) {return 1;}
	return countLeaves(node->LeftChildren)+countLeaves(node->RightChildren);
}

void BinaryTree::swapLRTree(BinaryTreeNode* node)
{
	if (node == NULL) return;
	swap(node->LeftChildren, node->RightChildren);
	swapLRTree(node->LeftChildren);
	swapLRTree(node->RightChildren);
}

int BinaryTree::heightTree(BinaryTreeNode* node)
{
	if (node == NULL) return 0;
	return max(heightTree(node->LeftChildren), heightTree(node->RightChildren)) + 1;
}

int main() {
	BinaryTree st;

	st.createSampleTree();

	cout << "叶节点数目: " << st.CountLeaves() << endl;

	cout << "层次遍历: ";
	st.LevelTraversal();
	cout << endl;

	st.SwapLRTree();
	cout << "交换左右子树后，层次遍历结果: ";
	st.LevelTraversal();
	cout << endl;
	
	cout << "二叉树的宽度: " << st.WidthTree() << endl;

	return 0;
}
