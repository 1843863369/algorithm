/*
牛客算法进阶第四课第一题，奇数下标都为奇数或偶数下标都为偶数
偶下标和奇下标，从最后一位向下标发货，下标右移两个
@2018/3/6
*/

#include <vector>
#include <random>
#include <iostream>

using namespace std;

void OddEven(vector<int> &v) {
	int even = 0;
	int odd = 1;
	int len = v.size() - 1;
	while (odd <= len&&even <= len) {
		if (v[len] % 2 == 0) {
			swap(v[even], v[len]);
			even += 2;
		}
		else {
			swap(v[odd], v[len]);
			odd += 2;
		}
	}
}

vector<int> geneVec() {
	static default_random_engine e;
	static uniform_int_distribution<> u(0, 9);
	vector<int> res;
	for (int i = 0; i < 12; ++i) {
		res.push_back(u(e));
	}
	return res;
}

void printVec(vector<int> &v) {
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}


int main() {
	int times = 10;
	while (times-- > 0) {
		vector<int> v = geneVec();
		printVec(v);
		OddEven(v);
		printVec(v);
		cout << "=============" << endl;
	}
	
	system("pause");
	return 0;
}