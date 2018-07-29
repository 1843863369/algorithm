/*
牛客算法初级班第三课第三题，用队列实现栈，用栈实现队列
@2018/1/123
*/

#include <queue>
#include <stack>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

class TwoQueuesStack {
public:
	TwoQueuesStack() {
		data = make_shared<queue<int>>();
		help = make_shared<queue<int>>();
		}
	void push(int a) {
		data->push(a);
	}
	void pop() {
		while (data->size() != 1) {
			help->push(data->front());
			data->pop();
		}
		data->pop();
		swap();
	}
	int top() {
		return data->back();
	}
	void swap() {
		shared_ptr<queue<int>> tmp(data);
		data = help;
		help = tmp;
	}
private:
	shared_ptr<queue<int>> data;
	shared_ptr<queue<int>> help;

};

class TwoStacksQueue {
public:
	void inque(int n){
		data.push(n);
	}
	int front() {
		pollin();
		return help.top();
	}
	void outque() {
		pollin();
		help.pop();
	}
	int back() {
		if (data.empty() && help.empty()) {
			throw out_of_range("the queue is empty");
		}
		if (!data.empty()) {
			return data.top();
		}
		else {
			return back_d;
		}
	}
	void pollin() {
		if (help.empty()) {
			back_d = data.top();
			while (!data.empty()) {
				help.push(data.top());
				data.pop();
			}
		}
	}

private:
	stack<int> data;
	stack<int> help;
	int back_d;
};

int main() {
	
	int a[9] = { 4,6,3,4,5,6,3,6,1 };
	
	int n = 10;
	TwoStacksQueue as;
	for (auto &i : a) {

		as.inque(i);

	}
	cout << as.back() << endl;
	cout << as.front() << endl;
	as.outque();
	cout << as.front() << endl;
	cout << as.back() << endl;
	as.outque();
	cout << as.front() << endl;
	as.inque(8);
	cout << as.back() << endl;
	cout << as.front() << endl;
	as.inque(10);
	cout << as.back() << endl;
	cout << as.front() << endl;
	as.outque();
	as.outque();
	as.outque();
	as.outque();
	as.outque();
	as.outque();
	as.outque();
	as.outque();
	as.outque();
	as.outque();


	/*cout << as.top() << endl;
	as.pop();
	cout << as.top() << endl;
	as.pop();
	cout << as.top() << endl;
	as.pop();
	cout << as.top() << endl;
	as.pop();
	cout << as.top() << endl;
	as.pop();

	as.pop();
	as.pop();
	as.pop();
	as.pop();


	as.push(1);
	cout << as.top() << endl;
	as.push(4);
	cout << as.top() << endl;
	as.push(5);
	cout << as.top() << endl;*/
	//cout << size(s);

	system("pause");
	
}