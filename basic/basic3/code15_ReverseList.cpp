/*
牛客算法初级班第三课十五题：翻转单向链表和双向链表
@2018/1/25
*/

#include <iostream>

using namespace std;

struct DoubleNode {
	DoubleNode() = default;
	DoubleNode(const int i):data(i),next(nullptr),pre(nullptr){}
	DoubleNode *next;
	DoubleNode *pre;
	int data;
};
struct Node {
	Node() = default;
	Node(const int i) :data(i), next(nullptr) {}
	Node *next;
	int data;
};



Node* ForwardReverse(Node *head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}
	Node* pre = nullptr;
	Node* next = nullptr;
	while (head != nullptr) {
		next = head->next;
		head->next = pre;
		pre = head;
		head = next;
	}
	return pre;
}

DoubleNode* DoubleReverse(DoubleNode* head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}
	DoubleNode* pre = nullptr;
	DoubleNode* next = nullptr;
	while (head != nullptr) {
		next = head->next;
		head->next = pre;
		head->pre = next;
		pre = head;
		head = next;
	}
	return pre;
}

 void printLinkedList(Node* head) {
	printf("Linked List: \n");
	while (head != nullptr) {
		cout << head->data << "->";
		head = head->next;
	}
	cout << endl;
}

 void printDoubledList(DoubleNode* head) {
	 printf("Doubled List: \n");
	 DoubleNode* end = nullptr;
	 while (head != nullptr) {
		 cout << head->data << "->";
		 end = head;
		 head = head->next;
	 }
	 cout << endl;
	 while (end != nullptr) {
		 cout << end->data << " ";
		 end = end->pre;
	 }
	 cout << endl;
	


 }

 int main() {
	 Node *head1 = new Node(1);
	 head1->next = new Node(2);
	 head1->next->next = new Node(3);
	 printLinkedList(head1);
	 head1 = ForwardReverse(head1);
	 printLinkedList(head1);

	 DoubleNode *head2 = new DoubleNode(1);
	 head2->next = new DoubleNode(2);
	 head2->next->pre = head2;
	 head2->next->next = new DoubleNode(3);
	 head2->next->next->pre = head2->next;
	 head2->next->next->next = new DoubleNode(4);
	 head2->next->next->next->pre = head2->next->next;
	 printDoubledList(head2);
	 printDoubledList(DoubleReverse(head2));


	 system("pause");
	 return 0;

 }