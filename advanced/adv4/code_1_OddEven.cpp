/*
ţ���㷨���׵��Ŀε�һ�⣬�����±궼Ϊ������ż���±궼Ϊż��
ż�±�����±꣬�����һλ���±귢�����±���������
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