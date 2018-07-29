/*
牛客算法初级班第四款第四题，第三四课作业：
https://www.nowcoder.com/questionTerminal/430180b66a7547e1963b69b1d0efbd3c
折纸问题，二叉树的应用，中序遍历
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