/*
Å£¿ÍÍø³õ¼¶°àµÚÒ»¿Î£¬Í°ÅÅÐò
@2018/1/20
*/

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

void BucketSort(vector<int> &v) {//only for 0-200
	int len = v.size();
	if (len <= 1) {
		return;
	}
	int max_v = v[0];
	for (int i = 1; i < len; ++i) {
		max_v = max(max_v, v[i]);
	}
	vector<int> buckets(max_v + 1,0);
	for (int i = 0; i < len; ++i) {
		buckets[v[i]]++;
	}
	int i = 0;
	for (int j = 0; j <= max_v; ++j) {
		while (buckets[j]-- > 0) {
			v[i++] = j;
		}
	}

}

void CountSort(vector<int> &v) {
	int len = v.size();
	if (len <= 1) {
		return;
	}
	vector<int> result(v);
	int max_v = v[0];
	for (int i = 1; i < len; ++i) {
		max_v = max(max_v, v[i]);
	}
	vector<int> buckets(max_v + 1, 0);
	for (int i = 0; i < len; ++i) {
		buckets[v[i]]++;
	}
	for (int i = 1; i < max_v + 1; ++i) {
		buckets[i] += buckets[i - 1];
	}
	for (int i = len - 1; i >= 0; --i) {
		v[(buckets[result[i]]--) - 1] = result[i];
	}
}

//comparator
void comparator(vector<int> &v) {
	stable_sort(v.begin(), v.end());
}
vector<int> generateVec() {
	vector<int> v;
	static default_random_engine e;
	static uniform_int_distribution<> u(0, 200);
	for (int i = 0; i < 10; ++i) {
		v.push_back(u(e));
	}
	return v;
}
void printVec(vector<int> &v) {
	for (auto &a : v) {
		cout.width(3);
		cout << a << " ";
	}
	cout << endl;
}


int main() {
	int n = 1;
	while (n-- > 0) {
		//vector<int> v = generateVec();
		vector<int> v{ 1,2,2,2,2,3,3,3,1,1,7,3,9,2 };
		vector<int> vc(v);
		printVec(v);
		CountSort(v);
		printVec(v);
		comparator(vc);
		//printVec(vc);
		cout << (v == vc) << endl << "================================" << endl;
	}
	system("pause");
	return 0;
}