/*
牛客算法进阶班第三课第二题，最短的需要排序的子数组的长度
思路，用两个变量从左向右、从右向左遍历，找小于左侧最大值和大于右侧最小值的
@2018/2/3
*/
#include <vector>
#include <iostream>
#include <random>

using namespace std;

int MinLenForSort(vector<int> &v) {
	int len = v.size();
	if (len <= 1)
		return 0;
	int smaller_than_max = -1;
	int larger_than_min = -1;
	int right_min = v[len - 1];
	int left_max = v[0];
	for (int i = len - 2; i >= 0; --i) {
		if (v[i] <= right_min) {
			right_min = v[i];
		}
		else {
			larger_than_min = i;
		}
	}
	if (larger_than_min == -1)
		return 0;
	for (int i = 1; i < len; ++i) {
		if (v[i] >= left_max) {
			left_max = v[i];
		}
		else {
			smaller_than_max = i;
		}
	}
	return smaller_than_max - larger_than_min + 1;
}

vector<int> generateVec() {
	vector<int> res;
	static default_random_engine e;
	static uniform_int_distribution<> u(0, 9);
	for (int i = 0; i < 10; ++i) {
		res.push_back(u(e));
	}
	return res;
}
void printVec(vector<int> &v) {
	for (auto &i : v) {
		cout << i << " ";
	}
	cout << endl;
}


int main() {
	vector<int> v = { 1, 2, 4,4,4, 7, 10, 11, 7, 12, 6, 7, 16,16, 18, 19 };
	printVec(v);
	cout << MinLenForSort(v) << endl;
	system("pause");
	return 0;
}