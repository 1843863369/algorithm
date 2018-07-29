/*
牛客算法初级第四课第五题，二叉树的非递归三种遍历
@2018/1/30
*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node {
	Node() = default;
	Node(const int i):data(i),left(nullptr),right(nullptr){}
	int data;
	Node* left;
	Node* right;
};

void InPrint(Node* root) {
	cout << "InPrint:" << endl;
	stack<Node*> s;
	while (!s.empty() || root != nullptr) {
		if (root != nullptr) {
			s.push(root);
			root = root->left;
		}
		else {
			root = s.top();
			cout << root->data << " ";
			s.pop();
			root = root->right;
		}
	}
	cout << endl;
}

void PrePrint(Node* root) {
	cout << "PrePrint:" << endl;
	stack<Node*> s;
	while (!s.empty() || root != nullptr) {
		if (root != nullptr) {
			cout << root->data << " ";
			s.push(root);
			root = root->left;
		}
		else {
			root = s.top()->right;
			s.pop();
		}
	}
	cout << endl;
}

void PrePrint2(Node* root) {
	cout << "PrePrint2:" << endl;
	stack<Node*> s;
	s.push(root);
	while (!s.empty()) {
		root = s.top();
		s.pop();
		cout << root->data << " ";
		if (root->right != nullptr) {
			s.push(root->right);
		}
		if (root->left != nullptr) {
			s.push(root->left);
		}
	}
	cout << endl;
}

void PosPrint(Node* head) {
	cout << "PosPrint:" << endl;
	stack<Node*> s;
	stack<Node*> help;
	s.push(head);
	while (!s.empty()) {
		head = s.top();
		help.push(head);
		s.pop();
		if (head->left != nullptr) {
			s.push(head->left);
		}
		if (head->right != nullptr) {
			s.push(head->right);
		}
	}
	while (!help.empty()) {
		cout << help.top()->data << " ";
		help.pop();
	}
	cout << endl;
}

void PostPrint2(Node* root) {
	if (root == nullptr) {
		return;
	}
	PostPrint2(root->left);
	PostPrint2(root->right);
	cout << root->data << " ";
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
vector<int> postorderTraversal(TreeNode *root) {
	stack<TreeNode*> s;
	vector<int> res;
	if (!root) return res;
	s.push(root);
	while (!s.empty()) {
		root = s.top();
		res.push_back(root->val);
		s.pop();
		if (root->left != nullptr) {
			s.push(root->left);
		}
		if (root->right != nullptr) {
			s.push(root->right);
		}
	}
	reverse(res.begin(), res.end());
	return res;
}
int main() {
	Node* head = new Node(5);
	head->left = new Node(3);
	head->right = new Node(8);
	head->left->left = new Node(2);
	head->left->right = new Node(4);
	head->left->left->left = new Node(1);
	head->right->left = new Node(7);
	head->right->left->left = new Node(6);
	head->right->right = new Node(10);
	head->right->right->left = new Node(9);
	head->right->right->right = new Node(11);
	TreeNode* headt = new TreeNode(5);
	headt->left = new TreeNode(3);
	headt->right = new TreeNode(8);
	headt->left->left = new TreeNode(2);
	headt->left->right = new TreeNode(4);
	headt->left->left->left = new TreeNode(1);
	headt->right->left = new TreeNode(7);
	headt->right->left->left = new TreeNode(6);
	headt->right->right = new TreeNode(10);
	headt->right->right->left = new TreeNode(9);
	headt->right->right->right = new TreeNode(11);
	
	/*InPrint(head);
	PrePrint(head);
	PrePrint2(head);
	PosPrint(head);
	cout << "posPrint2:" << endl;
	PostPrint2(head);*/
	vector<int> res = postorderTraversal(headt);
	for (auto i : res) {
		cout << i << " ";
	}
	system("pause");
	return 0;
}

