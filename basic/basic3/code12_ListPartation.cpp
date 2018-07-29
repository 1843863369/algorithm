/*
牛客网算法初级班第三课十二题：单向链表按某值划分成小于，等于，大于三部分
@2018/1/24
*/

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Node {
public:
	Node() = default;
	Node(const int i) :data(i), next(nullptr) {}

	int data;
	Node* next;
};

void PartationWithVec(Node *head,int pivot) {
	Node *h = head->next;
	vector<Node*> help;
	while (h != nullptr) {
		help.push_back(h);
		h = h->next;
	}
	int len = help.size();
	if (len <= 1) {
		return;
	}
	int small = -1;
	int mid = -1;
	int large = 0;
	while (large < len) {
		if (help[large]->data > pivot) {
			++large;
		}
		else if (pivot == help[large]->data) {
			swap(help[++mid], help[large++]);
		}
		else {
			swap(help[++mid], help[large++]);
			swap(help[++small], help[mid]);
		}

	}
	head->next = help[0];
	for (int i = 1; i < len; ++i) {
		help[i - 1]->next = help[i];
	}
	help[len - 1]->next = nullptr; //注意，不置空会出现环，打印出现死循环
	
}

//额外空间复杂度O(1)，比pivot小或比pivot大的数相对顺序不变
void PartitionWithList(Node *head, int pivot) {
	Node s(0);
	Node m(0);
	Node l(0);
	Node *small = &s;
	Node *mid = &m;
	Node *large = &l;
	Node *csmall = small;
	Node *cmid = mid;
	Node *clarge = large;
	Node *h = head->next;
	while (h != nullptr) {
		if (h->data < pivot) {
			csmall->next = h;
			csmall = csmall->next;
		}
		else if (pivot == h->data) {
			cmid->next = h;
			cmid = cmid->next;
		}else{
			clarge->next = h;
			clarge = clarge->next;
		}
		h = h->next;
	}
	//连接三部分
	//如果small为空，small==csmall，使用csmall和small效果相同相连，再把small的next赋给head的next
	//如果small不为空，用csmall连接，再把small的next赋给head的next。
	//所以此处无需单独判断small那一条是否为空。
	if (mid->next != nullptr&&large->next != nullptr) {
		csmall->next = mid->next;
		cmid->next = large->next;
		clarge->next = nullptr;
	}
	else {
		csmall->next = (mid->next == nullptr) ? 
			(large->next == nullptr ? nullptr : large->next) : mid->next;
		cmid->next = nullptr;
		clarge->next = nullptr;
	}
	head->next = small->next;
}

void printL(Node *head) {
	while (head->next != nullptr) {
		cout << head->next->data << " ";
		head = head->next;
	}
	cout << endl;
}
vector<int> getRanVec() {
	static default_random_engine e;
	static uniform_int_distribution<> u(0, 10);
	vector<int> v;
	for (int i = 0; i < 10; ++i) {
		v.push_back(u(e));

	}
	return v;
}

Node* getList(vector<int> &v,Node *head) {
	for (int i = 0; i < v.size(); ++i) {
		head->next = new Node(v[i]);
		head = head->next;
	}
	return head;
}

int main() {
	vector<int> v;
	int time = 10;
	while (time-- > 0) {
		v = getRanVec();
		Node *headv = new Node(0);
		Node *headl = new Node(0);
		getList(v,headv);
		getList(v, headl);
		//cout << head->data << endl;
		//cout << head->next->data << endl;
		printL(headv);
		cout << "vec:" << endl;
		PartationWithVec(headv, 7);
		printL(headv);
		cout << "list:" << endl;
		PartitionWithList(headl, 7);
		printL(headl);
		cout << "==========================" << endl;
	}
	
	system("pause");
	return 0;
}