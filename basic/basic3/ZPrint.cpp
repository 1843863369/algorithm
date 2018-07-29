/*
牛客算法初级三四作业：之子打印矩阵
https://www.nowcoder.com/questionTerminal/7df39c7556424eada267d8f793961a1e
@2018/1/25
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> ZPrint(vector<vector<int>> &mat,int n,int m) {
	int rows = 0;
	vector<int> res;
	bool rightwards = true;
	while (rows < n) {
		if (rightwards) 
			res.insert(res.end(), mat[rows].begin(), mat[rows].end());
		else 
			res.insert(res.end(), mat[rows].rbegin(), mat[rows].rend());
		rightwards = !rightwards;
		++rows;
	}
	return res;
}

int main() {
	vector<vector<int>> vv = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },
	{ 13, 14, 15, 16 } };
	vector<int> res = ZPrint(vv, 4, 4);
	for (auto &i : res) {
		cout << i << " ";
	}
	system("pause");
	return 0;
}