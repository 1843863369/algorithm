/*
牛客算法进阶班第二课第六题：符合条件的最大矩形区域O(NM)
思路：矩阵相关问题将矩阵压缩成数组，例如：求累加和最大的矩阵，以每一行为底，将矩阵向下压缩成数组，解决数组问题即可
本题将矩阵纵向压缩，按行遍历，值为必须以某一行为底的直方图的高度，即，zip[c] = v[r][c] == 0 ? 0 : zip[c] + 1;//r从上到下
再用单调栈，求每一元素向左向右第一个小于自身的数，范围内就是最大的矩阵
@2018/2/2
*/

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int FromButton(vector<vector<int>> &v, int row) {
	int col = v[0].size();
	vector<int> zip(col);
	for (int c = 0; c < col; ++c) {
		for (int r = 0; r <= row; ++r) {
			zip[c] = v[r][c] == 0 ? 0 : zip[c] + 1;
		}
	}
	int res = 0;
	int left = 0;
	int high = 0;
	int cur = 0;
	stack<int> l_s;//从上到下减小
	for (int i = 0; i<col; ++i) {
		while (!l_s.empty() && zip[i] < zip[l_s.top()]) {
			high = l_s.top();
			l_s.pop();
			left = l_s.empty() ? -1 : l_s.top();
			cur = (i - left - 1)*zip[high];
			res = max(res, cur);
		}
		l_s.push(i);
	}
	
	while (!l_s.empty()) {
		high = l_s.top();
		l_s.pop();
		left = l_s.empty() ? -1 : l_s.top();
		cur = (col - left - 1)*zip[high];
		res = max(res, cur);
	}
	//cout << res <<" row: " << row << endl;
	return res;
}

int MaxRec(vector<vector<int>> &v) {
	int row = v.size();
	if (row == 0) {
		return 0;
	}
	int res = 0;
	for (int i = 0; i < row; ++i) {//必须以第i行结尾
		res = max(res, FromButton(v, i));
	}
	return res;
}

int main() {
	vector<vector<int>> v{ { 1, 0, 1, 1 },
						   { 1, 1, 1, 1 },
						   { 1, 1, 1, 0 } ,
						  };
	cout << MaxRec(v) << endl;
	//cout << FromButton(v,2);
	system("pause");
	return 0;
}