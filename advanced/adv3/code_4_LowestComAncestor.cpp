/*
牛客进阶第三课第四题，查找二叉树中两个节点的最近公共祖先
@2018/2/5  3/4完成
*/

#include <iostream>
#include <map>
#include <set>

using namespace std;

struct Node
{
	Node() = default;
	Node(const int i):data(i),left(nullptr),right(nullptr){}
	int data;
	Node* left;
	Node* right;
}; 

Node* LowestComAncestor(Node *head, Node* o1, Node*o2) {
	if (head == nullptr || head == o1 || head == o2) {
		return head;
	}
	Node* left_tree = LowestComAncestor(head->left, o1, o2);
	Node* right_tree = LowestComAncestor(head->right, o1, o2);
	if (left_tree != nullptr&&right_tree != nullptr) {
		return head;
	}
	else {
		return left_tree == nullptr ? right_tree : left_tree;
	}
}

class Record1 {
public:
	Record1(Node* head) {
		if (head != nullptr) {
			parents.insert({ head, nullptr });
			setMap(head);
		}
	}

	void setMap(Node* head) {
		if (head == nullptr)
			return;
		if (head->left != nullptr)
			parents.insert({ head->left,head });
		if (head->right != nullptr)
			parents.insert({ head->right,head });
		setMap(head->left);
		setMap(head->right);
	}

	Node* query(Node *o1, Node *o2) {
		set<Node*> path;
		while (parents.find(o1) != parents.end()) {
			path.insert(o1);
			o1 = parents[o1];
		}
		while (path.find(o2) == path.end()) {
			if (parents.find(o2) == parents.end()) {
				return nullptr;
			}
			o2 = parents[o2];
		}
		return o2;
	}

private:
	map<Node*, Node*> parents;

};

class Record2 {
public:
	Record2(Node* head) {
		initMap(head);
		setMap(head);
	}

	void initMap(Node *head) {
		if (head == nullptr)
			return;
		record[head].insert({head,head});
		initMap(head->left);
		initMap(head->right);
	}
	void setMap(Node *head) {
		if (head == nullptr)
			return;
		headRecord(head->left, head);
		headRecord(head->right, head);
		subRecord(head);
		setMap(head->left);
		setMap(head->right);
	}
	//head与node的所有孩子的公共ancestor为head
	void headRecord(Node *node, Node *head) {
		if (node == nullptr)
			return;
		record[head].insert({ node,head });
		headRecord(node->left,head);
		headRecord(node->right,head);
	}
	//head左子树上每一个node与右子树上每一个node的公共ancestor为head
	void subRecord(Node *head) {
		if (head == nullptr)
			return;
		preLeft(head->left, head->right, head);
		subRecord(head->left);
		subRecord(head->right);
	}
	void preLeft(Node *le, Node *ri, Node *head) {
		if (le == nullptr)
			return;
		preRight(le, ri, head);
		preLeft(le->left, ri, head);
		preLeft(le->right, ri, head);

	}
	void preRight(Node *le, Node *ri, Node *head) {
		if (ri == nullptr)
			return;
		record[le].insert({ ri,head });
		preRight(le, ri->left, head);
		preRight(le, ri->right, head);
	}
	Node* query(Node *o1, Node *o2) {
		if (record.find(o1) != record.end() && record[o1].find(o2) != record[o1].end()) {
			return record[o1][o2];
		}
		if (record.find(o2) != record.end() && record[o2].find(o1) != record[o2].end()) {
			return record[o2][o1];
		}
		return nullptr;
	}
private:
	map<Node*, map<Node*, Node*>> record;
};

int main() {
	Node *head = new Node(1);
	head->left = new Node(2);
	head->right = new Node(3);
	head->left->left = new Node(4);
	head->left->right = new Node(5);
	head->right->left = new Node(6);
	head->right->right = new Node(7);
	head->right->right->left = new Node(8);

	Node *o1 = head->left->right;
	Node *o2 = head->left;
	cout << "o1: " << o1->data << "   " << "o2: " << o2->data << endl;
	cout << LowestComAncestor(head, o1, o2)->data << endl;

	Record1 rec(head);
	cout << rec.query(o1, o2)->data << endl;

	Record2 rec2(head);
	cout << rec2.query(o1, o2)->data << endl;

	system("pause");
	return 0;
}