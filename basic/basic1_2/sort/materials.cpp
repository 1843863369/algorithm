#include "Sorts.h"

using namespace std;


void comparator(vector<int> &v, int l, int r) {
	sort(v.begin() + l, v.begin() + r + 1);
}

void comparator(vector<int> &v) {
	comparator(v, 0, v.size() - 1);
}

void printVec(vector<int> &v) {
	if (v.size() != 0) {
		for (auto &a : v) {
			cout.width(3);
			cout << a << " ";
		}
		cout << endl;
	}
}

vector<int> generateVec() {
	static default_random_engine e;
	static uniform_int_distribution<> u(-20, 20);
	vector<int> v;
	for (int i = 0; i < 20; i++) {
		v.push_back(u(e));
	}
	return v;
}

