/*
牛客初级算法三四课作业：翻转链表中的每K个值
https://www.nowcoder.com/questionTerminal/5f44c42fd21a42b8aeb889ab83b17ad0
开始使用指针方式，一直无法通过全部测试用例，原因可能是空间超限
改成vec，用swap反转，通过
@2018/1/26
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node {
	int data;
	int nextint;
	int addint;
	Node() = default;
	Node(const int i, const int a, const int n) :data(i), addint(a), nextint(n) {}
};

//Node* ReverK(Node *head, int n, int k) {
//	if (head == nullptr || n == 0) {
//		return nullptr;
//	}
//	if (n<k||k==1) {
//		return head;
//	}
//	Node *pre = nullptr;
//	Node *nex = head;
//	Node *h = head;
//	Node *resh = new Node(0,0,0);
//	Node *htmp = resh;
//	int slots = n / k;
//	int i = 0;
//	if (head == nullptr || n == 0) {
//		return nullptr;
//	}
//	while (slots-- > 0) {
//		for (i = 0; i < k; ++i) {
//				nex = h->next;
//				h->next = pre;
//				pre = h;
//				h = nex;
//			}
//		htmp->next = pre;
//		htmp = head;
//		head = h;
//		pre = nullptr;
//	}
//	htmp->next = h;
//	return resh->next;
//
//}

void ReverK1(vector<int> &head, int n, int k) {
	if ( n <= 1 || n < k || k == 1) {
		return;
	}
	int pre = 0;
	int nex = 0;
	int i = 1;
	while (i * k <= n) {
		pre = (i - 1)*k;
		nex = i*k - 1;
		while (nex >= pre) {
			swap(head[pre++], head[nex--]);
		}
		++i;
	}
}


int main() {
	// 1->2->3->4->5->6->7->null
	//Node *head_no1 = new Node(1);
	//head_no1->next = new Node(2);
	//head_no1->next->next = new Node(3);
	//head_no1->next->next->next = new Node(4);
	//head_no1->next->next->next->next = new Node(5);
	//head_no1->next->next->next->next->next = new Node(6);
	////head_no1->next->next->next->next->next->next = new Node(7);
	////head_no1->next->next->next->next->next->next->next = new Node(8);

	//Node* h = head_no1;
	//while (h != nullptr) {
	//	cout << h->data << " ";
	//	h = h->next;
	//}
	//cout << endl;
	//head_no1 = ReverK(head_no1, 8, 3);
	//h = head_no1;
	//while (h != nullptr) {
	//	cout << h->data << " ";
	//	h = h->next;
	//}
	map<int, Node*> record;
	vector<int> nodes;
	int add = 0;
	int data = 0, next = -1, n = 0, k = 0, head = -1;
	cin >> head >> n >> k;
	while (n-->0) {
		cin >> add >> data >> next;
		record.insert({ add, new Node(data,add, next) });
	}
	
	//Node *head_n = record.find(head) == record.end() ? nullptr : record[head];
	//Node *h = head_n;
	int i = 0;
	nodes.push_back(head);
	while (record.find(nodes[i]) != record.end()) {
		nodes.push_back(record.find(nodes[i])->second->nextint);
		++i;
	}
	
	/*h = head_n;
	while (h != nullptr) {
		cout << h->data << " ";
		h = h->next;

	}
	cout << endl;*/
	ReverK1(nodes, i + 1, k);

	for (int j = 0; j < i - 1; ++j) {
		printf("%05d %d %05d\n", nodes[j], record[nodes[j]]->data, nodes[j+1]);
	}
	printf("%05d %d %d\n", nodes[i - 1], record[nodes[i - 1]]->data, -1);

	system("pause");
	return 0;
}



