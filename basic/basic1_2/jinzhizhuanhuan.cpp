/*
牛客初级班第一二节作业，编程第一题
https://www.nowcoder.com/questionTerminal/ac61207721a34b74b06597fe6eb67c52
输入int，转成n进制
*/

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

//void Jinzhi(int num, int n) {
//	string res = "";
//	if (num < 0) {
//		res = res + '-';
//		num = -num;
//	}
//	int nns = 1;//n的幂
//	int bits;//每一位的值
//	int len = 0;//总位数
//
//	while (num >= nns) {
//		++len;
//		nns *= n;
//	}//循环结束后得到总位数；
//
//	while (num > 0) {
//		bits = 0;	
//		nns /= n;
//		num -= nns;
//		if (num < 0) {
//			res = res + '0';
//			--len;
//			num += nns;
//			continue;
//		}
//		while (num >= 0) {
//			++bits;
//			num -= nns;
//		}
//		num += nns;
//		if (bits > 9) {
//			res = res + char('A' + bits - 10);
//		}
//		else {
//			res = res + char('0' + bits);
//		}
//		--len;
//    }
//	while (len > 0) {
//		res = res + '0';
//		--len;
//	}
//
//	cout << res << endl;
//
//}
//void Jinzhi(int num, int n) {
//	string res = "";
//	if (num < 0) {
//		res = res + '-';
//		num = -num;
//	}
//	int nns = 1;//n的幂
//	int bits;//每一位的值
//	int len = 0;//总位数
//
//	while (num >= nns) {
//		++len;
//		nns *= n;
//	}//循环结束后得到总位数；
//
//	while (num > 0) {
//		bits = 0;
//		nns /= n;
//		if (num >= 0) {
//			bits = num/nns;
//			num -= nns*bits;
//		}
//		if (bits > 9) {
//			res = res + char('A' + bits - 10);
//		}
//		else {
//			res = res + char('0' + bits);
//		}
//		--len;
//	}
//	while (len > 0) {
//		res = res + '0';
//		--len;
//	}
//
//	cout << res << endl;
//
//}



//int main() {
//	int a, b;
//	scanf_s("%d %d", &a, &b);
//	Jinzhi(a, b);
//	
//	//system("pause");
//	//int c, d;
//	//scanf_s("%d,%d", &c, &d);
//}

string table = "0123456789ABCDEFG";
string res = "";
int main() {
	int m, n;
	cin >> m >> n;
	if (m < 0) {
		m = -m;
		cout << "-";
	}
	while (m) {
		res = table[m%n] + res;
		m /= n;
	}
	cout << res << endl;
	return 0;
}