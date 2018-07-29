/*
ţ���㷨��������Ŀ�����⣬�����Ŀ���ҵ��
https://www.nowcoder.com/questionTerminal/430180b66a7547e1963b69b1d0efbd3c
��ֽ���⣬��������Ӧ�ã��������
@2018/1/28
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



void PrintTree(int i, int N, bool down,vector<string> &res) {
	if (i == N) {
		res.push_back(down == true ? "down" : "up");
		return;
	}
	PrintTree(i + 1, N, true,res);
	res.push_back(down == true ? "down" : "up");
	PrintTree(i + 1, N, false,res);

}
vector<string> PaperFold(int n) {
	vector<string> res;
	PrintTree(1, n, true,res);
	return res;

}
int main() {
	int n;
	cin >> n;
	vector<string> s = PaperFold(n);
	for_each(s.begin(), s.end(), [](const string &a) {cout << a << " "; });
	system("pause");
	return 0;
}