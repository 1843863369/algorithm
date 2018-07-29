/*
牛客算法进阶第三课第三题，最长的可整合子数组的长度
思路：不排序，看有无重复和最大值最小值的差是否等于N-1
@2018/2/4
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <random>

using namespace std;


int LongestIntergrated(vector<int> &v) {
	int len = v.size();
	if (len == 0) {
		return 0;
	}	
	set<int> filter;
	int res = 1;
	int fl = 0;
	int fr = 0;
	int max_v = 0;
	int min_v = 0;
	for (int left = 0; left < len;++left){
		max_v = v[left];
		min_v = v[left];
		for (int right = left; right < len; ++right) {
			if (filter.find(v[right]) != filter.end()) {
				break;
			}
			max_v = max(max_v, v[right]);
			min_v = min(min_v, v[right]);
			filter.insert(v[right]);
			if (max_v - min_v == right - left) {
				//res = max(res, j - i + 1);
				if (res < right - left +1) {
					fl = left;
					fr = right;
					res = right - left + 1;
				}
			}
		}
		filter.clear();
	}
	//printf("L: %d,%d,total:%d\n", fl, fr, res);
	return res;
}

int comparator(vector<int> v) {
	int len = v.size();
	int res = 0;
	int fl = 0;
	int fr = 0;
	for (auto i = v.begin(); i!=v.end(); ++i) {
		for (auto j = i; j !=v.end(); ++j) {
			vector<int> tmp(i, j+1);
			set<int> filter(i, j + 1);
			sort(tmp.begin(),tmp.end());
			if (filter.size()==tmp.size() && tmp[tmp.size() - 1] - tmp[0] == j - i) {
				//res = max(res, j - i + 1);
				if (res < j - i + 1) {
					fl = i-v.begin();
					fr = j-v.begin();
					res = j - i + 1;
				}
			}
		}
	}
	//printf("com: %d,%d,total:%d\n", fl, fr, res);
	return res;
}
vector<int> generateVec() {
	vector<int> res;
	static default_random_engine e;
	static uniform_int_distribution<> u(-9, 9);
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
	int time = 20;
	while(time--> 0) {
		vector<int> v = generateVec();
		//printVec(v);
		//cout << "L: " << LongestIntergrated(v) << endl;
		//cout << "com: " << comparator(v) << endl;
		cout << (LongestIntergrated(v) == comparator(v)) << endl;
	}
	
	system("pause");
	return 0;
}