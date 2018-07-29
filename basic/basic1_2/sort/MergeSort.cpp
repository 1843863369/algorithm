/*
牛客算法初级班第一课，归并排序
@2018/1/16
*/

#include "Sorts.h"

using namespace std;

void merge(vector<int> &v, int l, int m, int r) {
	vector<int> help;
	int start_r = m + 1;
	int left = l;
	size_t i = 0;
	while (l <= m && start_r <= r) {
		help.push_back(v[l] <= v[start_r] ? v[l++] : v[start_r++]);
	}
	while (l <= m) {  //第一次写成if
		help.push_back(v[l++]);
	}
	while (start_r <= r) {
		help.push_back(v[start_r++]);
	}
	for (i = 0; i < help.size(); ++i) {
		v[left + i] = help[i];
	}
}

void MergeSort(vector<int> &v,int l,int r) {
	if (l >= r) {
		return;
	}
	int m = l + ((r - l) >> 1);
	MergeSort(v, l, m);
	MergeSort(v, m + 1, r);
	merge(v, l, m, r);
}

void MergeSort(vector<int> &v) {
	int l = 0;
	int r = v.size() - 1;
	MergeSort(v, l, r);
}

