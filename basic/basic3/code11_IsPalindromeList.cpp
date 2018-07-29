/*
牛客网初级班第三课第十一题，判断链表是否是回文
@2018/1/23
*/

#include <iostream>
#include <list>
#include <memory>
#include <stack>

using namespace std;

class Node {
public:
	Node() = default;
	Node(const int i) :data(i),next(nullptr) {}

	int data;
	shared_ptr<Node> next;
};

class NodeList {
public:
	NodeList():head(nullptr) {}
	shared_ptr<Node> Head(){
		return head;
	}
	void push(int n) {
		auto node = make_shared<Node>(n);
		if (head == nullptr) {
			head = make_shared<Node>(0);
			//cout << "head";
			head->next = node;
		}
		if(!node_list.empty())
			node_list.back()->next = node;
		node_list.push_back(node);
	}
	list<shared_ptr<Node>>::iterator insert(list<shared_ptr<Node>>::iterator ite, int n) {
		auto node = make_shared<Node>(n);
		(*ite)->next = node;
		return node_list.insert(ite, node);
	}
	void print() {
		shared_ptr<Node> h = head->next;
		while (h != nullptr) {
			cout << h->data;
			h = h->next;
		}
		cout << endl;
	}

private:
	list<shared_ptr<Node>> node_list;
	shared_ptr<Node> head;
};

bool IsPalinWithStack(NodeList &node_list) {
	stack<int> s;
	auto head = node_list.Head();
	while (head->next != nullptr) {
		s.push(head->next->data);
		//cout << head->next->data << " ";
		head = head->next;
	}
	head = node_list.Head();
	while (!s.empty()) {
		if (s.top() != head->next->data) {
			return false;
		}
		head = head->next;
		s.pop();
	}
	return true;
}

//额外空间复杂度O(1)
bool IsPalinWithPtr(NodeList &node_list) {
	shared_ptr<Node> slow = node_list.Head()->next;
	shared_ptr<Node> fast = node_list.Head()->next;
	while (slow->next != nullptr&&fast->next != nullptr&&fast->next->next != nullptr) {
		//当fast正好为最后一位时，fast->next->next != nullptr会报错，访问非法内存
		//需要在前面添加fast->next != nullptr
		slow = slow->next;
	//	cout << fast->next->next->data << " ";
		fast = fast->next->next;
	}
	fast = slow->next;
	slow->next = nullptr;//如果不先置空，会导致死循环，在slow和slow next之间。
	shared_ptr<Node> tmp = fast;
	while (tmp != nullptr) {
		tmp = tmp->next;
		fast->next = slow;
		slow = fast;
		fast = tmp;
		

	}
	tmp = slow;
	fast = slow;
	slow = node_list.Head()->next;//slow from the head
	bool res = true;
	while (fast != nullptr&&slow != nullptr) {
		if (fast->data != slow->data) {
			res = false;
			break;
		}
		fast = fast->next;
		slow = slow->next;
	}
	//recover origin list
	fast = tmp;
	slow = fast->next;
	tmp = slow;
	fast->next = nullptr; //同逆序过程，不然会造成死循环
	while (tmp != nullptr) {
		tmp = tmp->next;
		slow->next = fast;
		fast = slow;
		slow = tmp;
		
	}
	return res;

}

int main() {
	NodeList node_list;
	list<int> l = { 2 };
	for (auto &i : l) {
		node_list.push(i);
	}
	node_list.print();
	/*shared_ptr<Node> fast = node_list.Head()->next;
	shared_ptr<Node> slow = node_list.Head()->next;
	cout << (slow->next != nullptr&&fast->next->next != nullptr) << endl;
	slow = slow->next;
	fast = fast->next->next;
	cout << (slow->next != nullptr&&fast->next->next != nullptr) << endl;
	cout << fast->data << endl;
	slow = slow->next;
	fast = fast->next->next;
	cout << fast->data << endl;
	cout << (slow->next != nullptr&&fast->next != nullptr&&fast->next->next != nullptr) << endl;*/
	/*shared_ptr<Node> slow = node_list.Head()->next;
	shared_ptr<Node> fast = node_list.Head()->next;
	while (slow->next != nullptr&&fast->next->next != nullptr) {
		slow = slow->next;
		cout << fast->next->next->data << " ";
		fast = fast->next->next;
	}
*/

	cout << "O(N): " << IsPalinWithStack(node_list) << endl;
	cout << "O(1): " << IsPalinWithPtr(node_list) << endl;
	node_list.print();
	system("pause");
	return 0;
	
}