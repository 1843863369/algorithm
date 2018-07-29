/*
ţ���㷨���װ�ڶ��ε����⣺��������������������O(NM)
˼·������������⽫����ѹ�������飬���磺���ۼӺ����ľ�����ÿһ��Ϊ�ף�����������ѹ�������飬����������⼴��
���⽫��������ѹ�������б�����ֵΪ������ĳһ��Ϊ�׵�ֱ��ͼ�ĸ߶ȣ�����zip[c] = v[r][c] == 0 ? 0 : zip[c] + 1;//r���ϵ���
���õ���ջ����ÿһԪ���������ҵ�һ��С�������������Χ�ھ������ľ���
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
	stack<int> l_s;//���ϵ��¼�С
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
	for (int i = 0; i < row; ++i) {//�����Ե�i�н�β
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