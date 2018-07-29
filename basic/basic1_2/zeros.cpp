/*
牛客网基础班一二节作业
https://www.nowcoder.com/questionTerminal/6ffdd7e4197c403e88c6a8aa3e7a332a
*/

#include <iostream>
#include <string>

using namespace std;

void Zeros(int n) {//n个数中能分解出i个5，结果为i（分解除2的个数一定比5多，所以不考虑）
	int res = 0;
	if (n % 5 != 0) {
		n -= n % 5;
	}
	int div5;
	while (n >= 5) {
		div5 = n;
		while (div5 % 5 == 0) {
			++res;
			div5 = div5 / 5;
		}
		n -= 5;
	}

	cout << res << endl;
}
/*
作者：哇咔哇咔
链接：https://www.nowcoder.com/questionTerminal/6ffdd7e4197c403e88c6a8aa3e7a332a
来源：牛客网

比如100/5=20，即有20个数包含因数5：
5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100。
这20个数中又有20/5=4个包含因数5:25,50,75,100
（可以把前面的20个数看成5*1，5*2，5*3，5*4，5*5，5*6，5*7，5*8，5*9，
5*10,，5*11，5,12，5*13，5*14，5*15，5*16，5*17，5*18，5*19，5*20），
然后这4个数中的因数5又被计算过了，即可。
*/
void Zeros1(int n) {
	int res = 0;
	while (n) {
		res += n / 5;
		n /= 5;
	}

	cout << res << endl;
}


//对数器
int Comparator(int n) {
	unsigned long long result = 1;
	while (n > 0) {
		result *= n;
		--n;
	}
	string table = "0123456789";
	string res = "";
	while (result > 0) {
		res = table[result % 10] + res;
		result /= 10;
	}
	cout << res << endl;
	int len = res.size();
	int count = 0;
	char *temp = &res[len - 1];
	while (*temp == '0') {
		++count;
		--temp;
	}
	return count;
}

int main() {
	cout << Comparator(25) << endl;
	Zeros(999);
	/*int n = 20;
	while (n > 0) {
		cout << (Comparator(20) == Zeros(20)) << endl;
		--n;
	}*/
	system("pause");
	return 0;
}