/*
  @ 牛客进阶版第一课，第一题
    如何把一个栈排序，只能使用一个辅助栈
  @ 2018/1/5
*/

#include <stack>
#include <iostream>
//#include <stdio.h>

using namespace std;

void stack_sort(stack<int> &s) {//参数使用引用，否则为值传递，不会改变s。详见c++参数传递机制
	stack<int> help;
	int temp = 0;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		while (!help.empty() && temp > help.top()) {
			s.push(help.top());
			help.pop();
		}
		help.push(temp);
	}
	while (!help.empty()) {
		s.push(help.top());
		help.pop();
	}
}

int main() {
	stack<int> s;
	s.push(3);
	s.push(1);
	s.push(6);
	s.push(2);
	s.push(5);
	s.push(4);
	stack_sort(s);
	while (!s.empty()) {
		//printf("%d",s.top());
		cout << s.top() << ",";
		s.pop();
	}
	system("pause");
		


}