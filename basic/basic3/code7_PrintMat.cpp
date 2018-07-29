/*
牛客算法初级班第三课第七题，转圈打印矩阵.
第八题，之字形打印矩阵
思路：关于按顺序打印数组的题，不用追踪坐标的方法
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintEdge(vector<vector<int>> &v, int lr, int lc, int rr, int rc) {
	int temp = lc;
	if (lr == rr&&lc == rc) {
		cout << v[lr][lc] << " ";
		return;
	}
	while (temp != rc) {//上边
		cout << v[lr][temp++] << " ";
	}
	temp = lr;
	while (temp != rr) {//右边
		cout << v[temp++][rc] << " ";
	}
	temp = rc;
	while (temp != lc) {
		cout << v[rr][temp--] << " ";
	}
	temp = rr;
	while (temp != lr) {
		cout << v[temp--][lc] << " ";
	}
}

void OrderPrint(vector<vector<int>> &v) {
	int rr = v.size() - 1;
	int rc = v[0].size() - 1;
	if (rr == 0 || rc == 0) {
		return;
	}
	int lr = 0;
	int lc = 0;
	while (lr <= rr&&lc <= rc) {
		PrintEdge(v, lr++, lc++, rr--, rc--);
	}
	cout << endl;
}

void PrintLine(vector<vector<int>> &v, int r, int c, bool upwards) {
	int rows = v.size() - 1;
	int cols = v[0].size() - 1;
	int tmp1 = max(0, r - rows);
	int tmp2 = max(0, c - cols);
	r = min(r, rows);
	c = min(c, cols);
	if (upwards) {
		while (tmp1 <= c) {
			cout << v[r--][tmp1++] << " ";
		}
	}
	else {
		while (tmp2 <= r){
			cout << v[tmp2++][c--] << " ";
		}
	}
}

void ZPrint(vector<vector<int>> &v) {
	int rows = v.size();
	int cols = v[0].size();
	if (rows == 0 || cols == 0) {
		return;
	}
	int c = 0;
	bool upwards = true;
	while (c <= rows + cols - 1) {
		PrintLine(v, c, c, upwards);
		++c;
		upwards = !upwards;
		cout << endl;
	}

}

int main() {
	vector<vector<int>> vv = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },
	{ 13, 14, 15, 16 } };
	vector<vector<int>> vv1 = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 } };
	OrderPrint(vv);
	OrderPrint(vv1);
	vector<vector<int>> vv2 = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },
	{ 13, 14, 15, 16 } ,{ 17, 18, 19, 20 } };
	OrderPrint(vv2);
	vector<vector<int>> vv3 = { { 1, 2, 3, 4,5 },{  6, 7, 8 ,9,10},{ 11, 12, 13, 14,15 },
	{ 16, 17, 18 ,19,20 },{ 21, 22, 23 ,24,25 } };
	OrderPrint(vv3);
	cout << "=============================" << endl;
	ZPrint(vv);
	ZPrint(vv1);
	ZPrint(vv2);
	ZPrint(vv3);

	system("pause");
		
}