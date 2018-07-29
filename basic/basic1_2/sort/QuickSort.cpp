/*
牛客算法初级班第一课，快速排序
@2018/1/16
*/

#include "Sorts.h"

using namespace std;

int GetRandom(int l,int r) {
	default_random_engine e;
	uniform_int_distribution<> u(l, r);
	int i = u(e);
	//cout << "in get function: "<<l << " " << r <<" "<< i<< endl;
	
	return i;
}

int partation(vector<int> &v, int l, int r) {
	int less = l - 1;
	//cout << l << " " << r << endl;
	int pivot = GetRandom(l, r);
	//cout << pivot << endl;
	swap(v[pivot], v[r]);
	for (int more = l; more <= r - 1; ++more) {
		if (v[more] <= v[r]) {
			swap(v[++less], v[more]);
		}
	}
	swap(v[less + 1], v[r]);
	return less + 1;
	return pivot;
}
void QuickSort(vector<int> &v,int l,int r) {
	if (l < r) {
		int p = partation(v, l, r);
		QuickSort(v, l, p - 1);
		QuickSort(v, p + 1, r);
	}
}
void QuickSort(vector<int> &v) {
	if (v.size()>1) {
		QuickSort(v, 0, v.size() - 1);
	}
}

