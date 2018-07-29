/*
牛客网初级班第一课：求所有的逆序对
思路：归并排序
@2018/1/21
*/

#include <vector>
#include <iostream>
#include <random>

using namespace std;

int merge(vector<int> &v, int l, int m, int r) {
	int res = 0;
	int pl = l;
	int pr = m + 1;
	vector<int> help;
	while (pl <= m&&pr <= r) {
		res += (v[pl] > v[pr] ? m - pl +1 : 0);
		help.push_back(v[pl] <= v[pr] ? v[pl++] : v[pr++]);
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

void MergeSort(vector<int> &v, int l, int r, int &res) {
	if (l == r) {
		return;
	}
	int m = l + ((r - l) >> 1);
	MergeSort(v, l, m, res);
	MergeSort(v, m + 1, r, res);
	res += merge(v, l, m, r);
}

int InverseNum(vector<int> v) {
	int res = 0;
	int len = v.size();
	if (len <= 1) {
		return 0;
	}
	MergeSort(v, 0, len - 1, res);
	return res;
}

int comparator(vector<int> v) {
	int len = v.size();
	if (len <= 1) {
		return 0;
	}
	int res = 0;
	for (int i = 0; i < len - 1; ++i) {
		for (int j = i + 1; j < len; ++j) {
			res += (v[j] < v[i] ? 1 : 0);
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
	int i;
	while (times-- > 0) {
		v = generateVec(10, 0, 20);
		printVec(v);
		c = comparator(v);
		i = InverseNum(v);
		cout << i << endl;
		cout << "comparetor: " << c << endl;
		cout << ((i == c) ? "^-^^-^" : "!!!!!!!!!!!") << endl;

	}
	system("pause");
	return 0;
}
