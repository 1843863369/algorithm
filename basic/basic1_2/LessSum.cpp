/*
牛客网算法初级班第一课，求数组中每一个数的左侧小于该数的和的总和
思路：改进归并排序
@2018/1/20
*/
#include <vector>
#include <iostream>
#include <random>

using namespace std;

int merge(vector<int> &v, int l, int m, int r) {
	vector<int> help;
	int res = 0;
	int pl = l;
	int pr = m + 1;
	while (pl <= m && pr <= r) {
	/*	if (v[pl] < v[pr + 1]) {
			res += v[pl] * (r - pr +1);
			help.push_back(v[pl]);
			++pl;
		}
		else {
			help.push_back(v[pr]);
			++pr;
		}*/
		res += (v[pl] < v[pr]) ? v[pl] * (r - pr + 1) : 0;
		help.push_back(v[pl] < v[pr] ? v[pl++] : v[pr++]);
	}
	while (pl <= m) {
		help.push_back(v[pl++]);
	}
	while (pr <= r) {
		help.push_back(v[pr++]);
	}
	for (int i = 0; i < help.size(); ++i) {
		v[l + i] = help[i];
	}
	return res;
}

void MergeSort(vector<int> &v, int l, int r,int &res) {
	if (r <= l) {
		return;
	}
	int mid = l + ((r - l) >> 1);
	MergeSort(v, l, mid, res);
	MergeSort(v, mid + 1, r, res);
	res += merge(v, l, mid, r);
	}


int LessSum(vector<int> v) {
	int res = 0;
	MergeSort(v, 0, v.size() - 1,res);
	return res;
}


int comparator(vector<int> &v) {
	int res = 0;
	for (int i = v.size() - 1; i > 0; --i) {
		for (int j = i - 1; j >= 0; --j) {
			res += (v[j] < v[i]) ? v[j] : 0;
		}
	}
	return res;
}
 
vector<int> generateVec(int len, int min, int max) {
	static default_random_engine e;
	static uniform_int_distribution<> u(min, max);
	vector<int> v;
	for (int i = 0; i < len; ++i) {
		v.push_back(u(e));
	}
	return v;
}
void printVec(vector<int> &v) {
	if (v.size() == 0) {
		return;
	}
	for (auto &a : v) {
		cout.width(3);
		cout << a << " ";
	}
	cout << endl;
}

int main() {
	vector<int> v;
	int times = 10;
	int c;
	int l;
	while (times-- > 0) {
		v = generateVec(10, 0, 20);
		printVec(v);
		c = comparator(v);
		l = LessSum(v);
		printVec(v);
		cout << l << endl;
		cout << "comparetor: "<< c << endl;
		cout << ((l == c) ? "^-^^-^" : "!!!!!!!!!!!") << endl;

	}
	system("pause");
	return 0;
}