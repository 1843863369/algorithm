/*
牛客算法初级班第四课第七题：找到后继节点
@2018/1/30
*/

#include <iostream>
using namespace std;

struct Node {
	Node() = default;
	Node(const int i):data(i),left(nullptr),right(nullptr),parent(nullptr){}
	int data;
	Node* left, *right, *parent;
};

Node* DescendantNode(Node* node) {
	if (node == nullptr)
		return nullptr;
	if (node->right != nullptr) {
		node = node->right;
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
	else {
		while (node->parent != nullptr) {
			if (node->parent->left == node) {
				break;
			}
			node = node->parent;
		}
		return node->parent;
	}
}

int main() {
	Node *head = new Node(6);
	head->parent = nullptr;
	head->left = new Node(3);
	head->left->parent = head;
	head->left->left = new Node(1);
	head->left->left->parent = head->left;
	head->left->left->right = new Node(2);
	head->left->left->right->parent = head->left->left;
	head->left->right = new Node(4);
	head->left->right->parent = head->left;
	head->left->right->right = new Node(5);
	head->left->right->right->parent = head->left->right;
	head->right = new Node(9);
	head->right->parent = head;
	head->right->left = new Node(8);
	head->right->left->parent = head->right;
	head->right->left->left = new Node(7);
	head->right->left->left->parent = head->right->left;
	head->right->right = new Node(10);
	head->right->right->parent = head->right;

	Node *test = DescendantNode(head->right->left->left);
	cout << test->data << endl;
	system("pause");
	return 0;
}