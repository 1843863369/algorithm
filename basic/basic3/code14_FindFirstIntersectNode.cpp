/*
ţ���㷨����������ε�ʮ���⣬���������ཻ������
1->�ж����������Ƿ�loop
2->�������loop���ֱ���end��end������ཻ���ཻ�ڵ㣺��������ȳ���һ�������ֱ�����
3->���һ��loop����һ����loop��һ�����뽻
4->�������loop���������
  4->1 ������β��loop�غϣ���ʱloopnode1==loopnode2��ȥ��loop�Ĳ��֣�תΪ2��
  4->2 ��loop1�����ߣ����û������loop2�����뽻������������ཻ����ʱ�Ľ���Ϊloop1��loop2����
@2018/1/25
*/

#include <iostream>

using namespace std;

struct Node {
	Node(const int i) :data(i),next(nullptr){}
	Node() = default;
	int data;
	Node *next;
};

Node* LoopNode(Node *head) {
	if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
		cout << "lenth of loop: " << 0 << endl;
		return nullptr;
	}
	Node* fast = head->next->next;
	Node* slow = head->next;         
	int step = 1;
	while (fast != slow) {
		if (fast->next == nullptr || fast->next->next == nullptr) {
			cout << "lenth of loop: " << 0 << endl;
			return nullptr;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	//�󳤶� Ҫע�ⳤ�Ȳ���slow�Ĳ������ǵ�һ������������ߣ��ٴ�����ʱ�Ĳ�����ֵ
	slow = slow->next;
	fast = fast->next->next;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next->next;
		step++;
	}

	cout << "lenth of loop: " << step << endl;
	fast = head;
	while (fast != slow) {
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

Node* noLoop(Node *head1, Node *head2) {//���뺯����headһ������Ϊ��
	Node *h1 = head1;
	Node *h2 = head2;
	int len = 0;
	while (h1->next != nullptr) {
		h1 = h1->next;
		++len;
	}
	while (h2->next != nullptr) {
		h2 = h2->next;
		--len;
	}
	cout << "len:"<<len << endl;
	if (h1 != h2) {
		cout << "���ཻ" << endl;
		return nullptr;
	}
	//�ཻ
	h1 = head1;
	h2 = head2;
	if (len >= 0) {//1��
		while (len > 0) {
			h1 = h1->next;
			--len;
		}
	}
	else {
		len = -len;
		while (len > 0) {
			h2 = h2->next;
			--len;
		}
	}
	while (h1 != h2) {
		h1 = h1->next;
		h2 = h2->next;
	}
	return h1;
}

Node* bothLoop(Node *head1, Node *head2, Node *loop1, Node *loop2) {//���뺯����head��loopһ������Ϊ��
	Node *h1 = head1;
	Node *h2 = head2;
	Node *l1 = loop1;
	Node *l2 = loop2;
	if (loop1 == loop2) {
		int len = 0;
		while (h1->next != loop1) {
			h1 = h1->next;
			++len;
		}
		while (h2->next != loop2) {
			h2 = h2->next;
			--len;
		}
		h1 = len >= 0 ? head1 : head2;//h1ָ�򳤵�head
		h2 = len >= 0 ? head2 : head1;
		len = len >= 0 ? len : -len;
		while (len > 0) {
			h1 = h1->next;
			--len;
		}
		while (h1 != h2) {
			h1 = h1->next;
			h2 = h2->next;
		}
		return h1;
	}
	else {
		while (l1->next != loop1) {
			l1 = l1->next;
			if (l1 == loop2)
				return loop2;
		}
		return nullptr;//תһȦ֮��û������loop2
	}
}

Node* IntersectNode(Node *head1,Node *head2){
	if (head1 == nullptr || head2 == nullptr) {
		cout << "��һ��listΪ�գ����ཻ" << endl;
		return nullptr;
	}
	Node *res = nullptr;
	Node *loop1 = LoopNode(head1);
	Node *loop2 = LoopNode(head2);
	if (loop1 == nullptr && loop2 == nullptr) {
		res = noLoop(head1, head2);
	}
	else if (loop1 != nullptr && loop2 != nullptr) {
		res = bothLoop(head1, head2, loop1, loop2);
	}
	return res;
}

int main() {
	// 1->2->3->4->5->6->7->4->->-> loop == 4 step == 4
	Node *head1;
	head1 = new Node(1);
	head1->next = new Node(2);
	head1->next->next = new Node(3);
	head1->next->next->next = new Node(4);
	head1->next->next->next->next = new Node(5);
	head1->next->next->next->next->next = new Node(6);
	head1->next->next->next->next->next->next = new Node(7);
	head1->next->next->next->next->next->next->next = head1->next->next->next; // 7->4
	//Node *loopnode = LoopNode(head1);
	/*if (loopnode != nullptr) {
		cout << loopnode->data << endl;

	}*/

	// 1->2->3->4->5->6->7->null
	Node *head_no1 = new Node(1);
	head_no1->next = new Node(2);
	head_no1->next->next = new Node(3);
	head_no1->next->next->next = new Node(4);
	head_no1->next->next->next->next = new Node(5);
	head_no1->next->next->next->next->next = new Node(6);
	head_no1->next->next->next->next->next->next = new Node(7);

	// 0->9->8->6->7->null
	Node *head_no2 = new Node(0);
	head_no2->next = new Node(9);
	head_no2->next->next = new Node(8);
	head_no2->next->next->next = head_no1->next->next->next->next->next; // 8->6

	// 1->2->3->4->5->6->7->4->->->
	Node *head_l1 = new Node(1);
	head_l1->next = new Node(2);
	head_l1->next->next = new Node(3);
	head_l1->next->next->next = new Node(4);
	head_l1->next->next->next->next = new Node(5);
	head_l1->next->next->next->next->next = new Node(6);
	head_l1->next->next->next->next->next->next = new Node(7);
	head_l1->next->next->next->next->next->next->next = head_l1->next->next->next; // 7->4

	Node *head_l2 = new Node(1);
	head_l2->next = new Node(2);
	head_l2->next->next = new Node(3);
	head_l2->next->next->next = new Node(4);
	head_l2->next->next->next->next = new Node(5);
	head_l2->next->next->next->next->next = new Node(6);
	head_l2->next->next->next->next->next->next = new Node(7);
	head_l2->next->next->next->next->next->next->next = head_l2->next->next->next; // 7->4

	
	Node *inter = IntersectNode(head_l1, head_l2);
	cout << (inter == nullptr ? -1 : inter->data) << endl;
	system("pause");
	return 0;

}