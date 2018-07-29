#include "SubFunctions.h"


using namespace std;

vector<int> generatePosVector() {
	vector<int> v;
	static default_random_engine e;
	static uniform_int_distribution<unsigned> u(0, 9);
	for (int i = 0; i < 10; ++i) {
		v.push_back(u(e));
	}
	return v;

}

vector<int> generateVector() {
	vector<int> v;
	static default_random_engine e;
	static uniform_int_distribution<> u(-9, 9);
	for (int i = 0; i < 10; ++i) {
		v.push_back(u(e));
	}
	return v;

}

void printVector(vector<int> &v) {
	if (!v.empty()) {
		for (auto &a : v) {
			cout.width(4);
			cout << a << " ";
		}
		cout << endl;
	}
}
