/*
牛客算法初级班第三课第一题，用固定大小的arr实现队列和栈
第二题：为栈添加geimin O(1)
@2018/1/22
*/

#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class ArrStack {
public:
	ArrStack() = default;
	ArrStack(const int i) {
		if (i < 0) {
			throw invalid_argument("size can not less than 0!");
			}
		cursize = 0;
		arr.assign(i,0);
	}
	
	void push(const int &a) {
		if (cursize>= arr.size()) {
			throw out_of_range("the stack is full!");
		}
		arr[cursize++] = a;
	}
	void pop() {
		if (cursize == 0) {
			throw out_of_range("the stack is empty");
		}
		cursize--;
	}
	int top() {
		if (cursize == 0) {
			throw out_of_range("the stack is empty");
		}
		return arr[cursize - 1];
	}


private:
	int cursize;
	vector<int> arr;
};

class ArrQueue {
public:
	ArrQueue() = default;
	ArrQueue(const int i) {
		arr.assign(i,0);
		cursize = 0;
		start = 0;
		end = 0;
	}
	int front() {
		if (cursize == 0) {
			throw out_of_range("the queue is empty");
		}
		return arr[start];
	}
	int back() {
		if (cursize == 0) {
			throw out_of_range("the queue is empty");
		}
		int tmp = end == 0 ? arr.size() - 1 : end - 1;
		return arr[tmp];
	}
	void push_back(int n) {
		if (cursize == size(arr)) {
			throw out_of_range("the queue is full");
		}
		cursize++;
		arr[end] = n;
		end = end == size(arr) - 1 ? 0 : end + 1;
	}
	int poll_front() {
		if (cursize == 0) {
			throw out_of_range("the queue is empty");
		}
		cursize--;
		int tmp = arr[start];
		start = start == size(arr) - 1 ? 0 : start + 1;
		return tmp;
	}
	
private:
	int cursize;
	int start;
	int end;
	vector<int> arr;
};

template <typename T>
class StackWithMin {
public:
	void push(T n) {
		data.push(n);
		if (min_d.empty() || n <= min_d.top()) {
			min_d.push(n);
		}
		else {
			min_d.push(min_d.top());
		}
	}
	void pop() {
		data.pop();
		min_d.pop();
	}
	T top() {
		return data.top();
	}
	T GetMin() {
		return min_d.top();
	}

private:
	stack<T> data;
	stack<T> min_d;
};

int main() {
	int a[9] = {4,6,3,4,5,6,3,6,1};
	string s[5] = { "ss","dd","gg" ,"aa","bb"};
	int n = 10;
	StackWithMin<string> as;
	for (auto &i : s) {
		
		as.push(i);
	
	}
	/*cout << endl;
	cout << as.back() << endl;
	cout << as.front() << endl;
	as.poll_front();
	cout << as.front() << endl;
	as.poll_front();
	cout << as.front() << endl;
	as.push_back(8);
	cout << as.back() << endl;*/

	cout << as.top()<<" " << as.GetMin()<< endl;
	as.pop();
	cout << as.top() << as.GetMin() << endl;
	as.pop();
	cout << as.top() << as.GetMin() << endl;
	as.pop();
	cout << as.top() << as.GetMin() << endl;
	as.pop();
	cout << as.top() << as.GetMin() << endl;
	as.pop();
	
	
	as.push("bb");
	cout << as.top() << as.GetMin() << endl;
	as.push("gg");
	cout << as.top() << as.GetMin() << endl;
	as.push("aa");
	cout << as.top() << as.GetMin() << endl;
	//cout << size(s);
	
	system("pause");
}