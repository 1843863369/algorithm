/*
牛客算法进阶班第二课第五题，山峰问题：返回能相互看到的山峰对数
高度无重复O(1)：选出高和次高（n-2），每一对小找大，每一个点左右都会各有一对，2(n-2),再加上次高和最高:2n-3
高度有重复O(N)：单调栈，小到大，每一层保存高度和数量，相等的高度不入栈，而是将数量加一，被弹出时Ck 2 + 2k，
                清算栈时注意边界，栈中剩余两项以上、只剩一项：数量一个和大于一个；
注意：对环使用单调栈，首先将最大值入栈，从最大值的next开始。
@2018/2/2
*/

#include <stack>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <random>

using namespace std;

class PairStack {
public:
	int TopVal() {
		if (!p_stack.empty()) {
			return p_stack.top().first;
		}
		return -1;
	}
	int TopNum() {
		if (!p_stack.empty()) {
			return p_stack.top().second;
		}
		return -1;
	}
	pair<int, int> PopPair() {
		auto t = p_stack.top();
		p_stack.pop();
		return t;
	}
	
	void Push(const int i) {
		if (!p_stack.empty() && this->TopVal() == i) {
			++p_stack.top().second;
		}
		else {
			p_stack.emplace(i, 1);
		}
	}
	bool Empty() {
		return p_stack.empty();
	}
	int Size() {
		return p_stack.size();
	}
private:
	stack<pair<int,int>> p_stack;
};

int EqualsTimes(int i) {
	return i*(i - 1) / 2;
}

int next(vector<int> &v, int index) {
	return index == v.size() - 1 ? 0 : index + 1;
}

int Mountains(vector<int> &v) {
	int len = v.size();
	//set<int> uniq(v.begin(), v.end());
	//if (uniq.size() == len) {//没有重复元素
	//	return max(0, 2 * len - 3);
	//}
	//有重复元素才能进行到这里
	PairStack ps;
	int res = 0;
	int max_index = 0;
	for (int i = 0; i<len; ++i) {
		max_index = v[max_index]<v[i] ? i : max_index;
	}
	int i = next(v, max_index);
	ps.Push(v[max_index]);
	pair<int, int> tmp;
	while (i!=max_index) {
 		while (!ps.Empty() && v[i] > ps.TopVal()) {
			tmp = ps.PopPair();
			res += EqualsTimes(tmp.second) + tmp.second;
			res += ps.Empty() ? 0 : tmp.second;
		}
		if (ps.Empty() || v[i] <= ps.TopVal()) {//相等情况已封装到class
			ps.Push(v[i]);

		}
		i = next(v, i);
	}
	while (!ps.Empty()) {
		tmp = ps.PopPair();
		res += EqualsTimes(tmp.second);
		if (!ps.Empty()) {
			res += tmp.second;
			if (ps.TopNum() > 1) {
				res += tmp.second;
			}
			else if (ps.Size() > 1) {
				res += tmp.second;
			}
		}
	}
	return res;
}

int last(vector<int> &v, int index) {
	return index == 0 ? v.size() - 1 : index - 1;
}

int comparator(vector<int> &v) {
	int start_index = 0;
	int next_index = 1;
	int res = v.size();//相邻的
	for (int i = 0; i < v.size(); ++i) {
		for (int j = next(v,next(v, i)); j != i; j = next(v,j)) {
			int k = 0;
			int kni = 0;
			for (k = next(v, i); k != j; k = next(v, k)) {
				if (v[k] > min(v[i], v[j])) {
					break;
				}
			}
			for (kni = last(v, i); kni != j; kni = last(v, kni)) {
				if (v[kni] > min(v[i], v[j])) {
					break;
				}
			}
			if (k == j || kni == j) {
				res += 1;
			}
		}
	}
	return res / 2;
}

int main() {
	vector<int> v{ 5,2,4,7,6,5,6,7,1,3,5,3};
	cout << Mountains(v) << endl;
	cout << "comparator:" << endl;
	cout << comparator(v) << endl;
	system("pause");
	return 0;
}