/*
牛客进阶班第一课第三题：
子数组问题：最大值减最小值小于等于num的子数组数量
子数组子串相关的问题，使用窗口，窗口使用双端队列实现，时间存index，按值大小排序。
@2018/1/8
*/

#include <vector>
#include <deque>
#include <iostream>
#include <climits>
#include <random>

using namespace std;


//for test
//实现窗口结构：得到L和R中间的子数组中最大值
int vectorMax(vector<int> &v,size_t L, size_t R) {//窗口包含端点：L,R
	deque<int> max_deq;
	for (auto i = L; i <= R; ++i) {
		while ( !max_deq.empty() && v[max_deq.back()] <= v[i]) {
			max_deq.pop_back();
		}
		max_deq.push_back(i);
	}
	return max_deq.front();
}

int subLessEquNum(vector<int> &v,int num) {//关键点：如果子数组i-j符合，那么i-j的任意子数组都符合。
	//从0开始，遍历从i开头的子数组
	//R只右移
	deque<int> max_deq, min_deq;
	int i = 0, R= 0;
	int len = v.size();
	int result = 0;
	while (i < len) {//以i开头的
		while (R < len) {
			while (!max_deq.empty() && v[max_deq.back()] <= v[R]) {
				max_deq.pop_back();
			}
			max_deq.push_back(R);
			while (!min_deq.empty() && v[min_deq.back()] >= v[R]) {
				min_deq.pop_back();
			}
			min_deq.push_back(R);
			if (v[max_deq.front()] - v[min_deq.front()] <= num) {//注意要比较vector中的值，两个队列存的是index
				//只要符合条件，R一直向右移
				
				++R;
			}
			else {
				break;
			}
		}//否则，循环结束,计算结果：result+  i-R的子数组个数；右移i	
		result += R - i;	
		printf("%d 到 %d 中的所有子数组，一共有 %d 个\n", i, R-1, R-i);
		//右移i之前，先判断当前i是否在队列中，如果在要弹出，不在就可以直接移动i
		if (max_deq.front() == i) {
			max_deq.pop_front();
		}
		if (min_deq.front() == i) {
			min_deq.pop_front();
		}
		++i;
	}
	return result;
}

vector<int> getRandom() {
	
	static default_random_engine e;
	static uniform_int_distribution<unsigned> u(0, 9);
	vector<int> ret;
	for (int i = 0; i < 10; ++i) {
		ret.push_back(u(e));
	}
	return ret;
}

void printArr(vector<int> &v) {
	if (0 == v.size()) {
		cout << "no vector to print" << endl;
		return;
	}
		
	for (auto vv : v) {
		cout << vv << " ";
	}
	cout << endl;
}

int main() {
	vector<int> test_v = getRandom();
	printArr(test_v);
	//cout << vectorMax(test_v, 4, 6)<<endl;
	vector<int> test_v1{ 1000,500,600,400 };
	int num = subLessEquNum(test_v, 3);
	cout << "一共有 "<<num << " 个"<< endl;
	system("pause");
	return 0;
}