/*
进阶第五课第二题，分糖果  从左向右再从右向左扫描两次，保证大分值的糖更多
https://www.nowcoder.com/practice/74a62e876ec341de8ab5c8662e866aef?tpId=46&tqId=29045&rp=1&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
2018/4/23
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int candy(vector<int> &ratings) {
	int l,m,r;
	int len = ratings.size();
	l = 0;
	m = r = 0;
	int res = 0;
	if (len == 0) return 0;
	if (len == 1) return 1;
	while (r < len - 1) {
		while (r < len - 1 && ratings[m + 1]>ratings[m]) {
			//上升，m为最高点
			++m; ++r;	
		}
		while (r < len - 1 && ratings[r] >= ratings[r + 1]) {
			++r; //下降
		}
		int pre_candy = 1;
		int cur_candy = 1;
		for (int i = l + 1; i <= m; ++i) {
			res += pre_candy;
			cur_candy = ratings[i]>ratings[i - 1] ? pre_candy + 1 : pre_candy;
			pre_candy = cur_candy;
		}//结束后pre_candy表示上坡的m出的糖果数
		int pre_candy2 = 1;
		for (int i = r - 1; i >= m; --i) {
			res += pre_candy2;
			cur_candy = ratings[i] > ratings[i + 1] ? pre_candy2 + 1 : 1;
			pre_candy2 = cur_candy;
		}
		res += max(pre_candy, pre_candy2);
		l = r;
		m = r;
		--res;
	}
	
	return ++res;
}

int candy2(vector<int> &ratings) {
	int len = ratings.size();
	if (len == 0) return 0;
	vector<int> candys(len, 1);
	for (int i = 1; i < len; ++i) {
		if (ratings[i] > ratings[i - 1])
			candys[i] = candys[i - 1] + 1;
	}
	for (int i = len - 2; i >= 0; --i) {
		if (ratings[i] > ratings[i + 1] && candys[i] <= candys[i + 1])
			candys[i] = candys[i + 1] + 1;
	}
	int res = 0;
	for (int i = 0; i < len; ++i) {
		res += candys[i];
	}
	return res;
}
int main() {
	vector<int> v = { 1,2,2 };
	vector<int> v1 = { 3,2,4,5,3,3,2,5,5 };
	cout << candy2(v) << endl;
	cout << candy2(v1) << endl;
	system("pause");
	return 0;
}