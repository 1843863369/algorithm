/*
ţ��������������ε�ʮ���⣺����һ�������ָ���list
���ף������ö������ݽṹ��ʱ�临�Ӷ�O(N)��
˼·����ÿ���ڵ㸴�ƺ����ԭ�ڵ��next������ʡȥ��¼copy��ϵ��map
��Ҫ�����⣺1���Կսڵ�ȡnext
            2��rand��next���޸Ĳ��У����randָ��ǰ��Ľڵ�ʱ���޷�������ȡ��Ҫ��rand�������
@2018/1/24
*/

#include <iostream>
#include <map>
#include <random>

using namespace std;

class Node {
public:
	Node() = default;
	Node(const int i) :data(i),rand(nullptr),next(nullptr){}

	Node *rand;
	Node *next;
	int data;
};
struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
	
};
RandomListNode *copyRandomList(RandomListNode *head) {
	RandomListNode *h = head;
	RandomListNode *copy;
	while (h != nullptr) {
		copy = new RandomListNode(h->label);
		copy->next = h->next;
		h->next = copy;
		h = h->next->next;
	}
	h = head;
	while (h != nullptr) {//�������е�rand������ڸ�next����
		h->next->random = h->random == nullptr ? nullptr : h->random->next;
		h = h->next->next;
	}
	h = head;
	RandomListNode *res = h->next;
	copy = res;
	while (h != nullptr) {//��next����
		h->next = res->next;
		h = h->next;
		res->next = h == nullptr ? nullptr : h->next;
		res = res->next;
	}
	res = copy;
	return res;
}
int getRandInt(int n) {//���������нڵ���������0����ʾ��һ��������n��ʾnull
	static default_random_engine e;
	static uniform_int_distribution<> u(0, n);
	return u(e);
}

void getList(int arr[], Node* head,int len) {
	int ran = 0;
	Node *h = head;
	Node *rand_node = head;
	for (int i = 0; i < len; ++i) {
		
		h->next = new Node(arr[i]);
		h = h->next;
	}
	h = head->next;
	while (h != nullptr) {
		ran = getRandInt(len);
		for (int j = 0; j <= ran; ++j) {
			rand_node = rand_node->next;
		}
		h->rand = rand_node;
		rand_node = head;
		h = h->next;
	}

}

Node* CopyWithMap(Node *head) {
	map<Node*, Node*> copys;
	Node *h = head->next;
	while (h != nullptr) {
		copys.insert({ h,new Node(h->data) });
		h = h->next;
	}
	copys[nullptr] = nullptr;
	h = head->next;
	while (h != nullptr) {
		copys[h]->next = copys[h->next];
		copys[h]->rand = copys[h->rand];
		h = h->next;
	}
	h = head;
	h->next = copys[head->next];
	return h;

}

void printL(Node *head);

//����ռ临�Ӷ�O(1)
Node* Copy(Node* head) {
	if (!head) return head;
	Node *h = head->next;
	while (h != nullptr) {
		auto copy = new Node(h->data);
		copy->next = h->next;
		h->next = copy;
		h = h->next->next;
	}
	h = head->next;
	while (h != nullptr) {//�������е�rand������ڸ�next����
		h->next->rand = h->rand == nullptr ? nullptr : h->rand->next;
		h = h->next->next;
	}
	Node *tmp;
	h = head->next;
	Node *res = new Node(0);
	res->next = h->next;
	while (h != nullptr) {//��next����
		tmp = h->next->next;
		h->next->next = tmp == nullptr ? nullptr : tmp->next;
		h->next = tmp;
		h = tmp;
	}
	return res;
}

void printL(Node *head) {
	head = head->next;
	while (head != nullptr) {
		printf("data��%d��rand��%d\n", head->data, (head->rand == nullptr ? -1: head->rand->data));
		head = head->next;
	}
	cout << "=====================" << endl;
}

//int* getVec() {
//	static default_random_engine e;
//	static uniform_int_distribution<> u(0, 10);
//	int a[6];
//	for (int i = 0; i < 6; ++i) {
//		a[i] = u(e);
//	}
//	return a;
//}

int main() {
	int t = 5;
	while (--t > 0) {


		static default_random_engine e;
		static uniform_int_distribution<> u(0, 10);
		int a[6];
		for (int i = 0; i < 6; ++i) {
			a[i] = u(e);
			cout << a[i] << " ";
		}
		cout << endl;
		Node *head = new Node(0);
		Node *headc = new Node(0);
		Node *head1 = new Node(0);
		getList(a, head, 6);
		cout << "���飺" << endl;
		printL(head);
		headc = CopyWithMap(head);
		//cout << "mapʵ�֣�" << endl;
		//printL(headc);
		cout << "O(1)ʵ�֣�" << endl;
		head1 = Copy(head);
		printL(head1);
		cout << "ԭ���飺" << endl;
		printL(head);
		cout << "++++++++++++++++++++" << endl;

		RandomListNode *rh = new RandomListNode(1);
		rh->next = new RandomListNode(2);
		rh->next->next = new RandomListNode(3);
		rh->random = rh->next->next;
		rh->next->random = rh;
		rh->next->next->random = rh->next;
		RandomListNode *crh = copyRandomList(rh);
		while (rh != nullptr) {
			cout << rh->label << " " << rh->random->label << endl;
			rh = rh->next;
		}
		cout << "................" << endl;
		while (crh != nullptr) {
			cout << crh->label << " " << crh->random->label << endl;
			crh = crh->next;
		}
	}
	system("pause");
	return 0;

}