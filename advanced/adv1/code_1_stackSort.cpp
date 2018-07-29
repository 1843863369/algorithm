/*
  @ ţ�ͽ��װ��һ�Σ���һ��
    ��ΰ�һ��ջ����ֻ��ʹ��һ������ջ
  @ 2018/1/5
*/

#include <stack>
#include <iostream>
//#include <stdio.h>

using namespace std;

void stack_sort(stack<int> &s) {//����ʹ�����ã�����Ϊֵ���ݣ�����ı�s�����c++�������ݻ���
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