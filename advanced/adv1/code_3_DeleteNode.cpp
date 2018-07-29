#include <iostream>

using namespace std;

class Node {
public:
	Node() = default;
	Node(int i):data(i){}
	Node* next;
	int data;

};

void deleteNode(Node* node) {
	if (node == NULL) {
		cout << "no node to delete" << endl;
		return;
	}
	if (node->next == nullptr) {
		cout << "can't delete the last node" << endl;
		return;
	}
	node->data = node->next->data;
	node->next = node->next->next;

}

void printNodeList(Node* head) {
	cout << "node list:" << endl;
	while (head != nullptr) {
		cout << head->data;
		head = head->next;
	}
	cout << endl;

}

int main() {
	Node head(0);
	Node* head_ptr = &head;
	Node node1(1), node2(2), node3(3);
	Node *node1_ptr, *node2_ptr, *node3_ptr,*node_null=nullptr;
	node1_ptr = &node1;
	node2_ptr = &node2;
	node3_ptr = &node3;
	head.next = &node1;
	node1.next = &node2;
	node2.next = &node3;
	printNodeList(head_ptr);
	deleteNode(node3_ptr);
	printNodeList(head_ptr);

	system("pause");
	return 0;
}