/*
ţ���㷨��������Ŀεڶ��⣬�н�������С����
Huffman����ԭ��̰���㷨

priority_queue<int,vector<int>, greater<int>> cost_que;������������ֻд����
@2018/1/29
*/

#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include <deque>

using namespace std;

int MinCost(vector<int> &v) {
	if (v.empty()) return 0;
	priority_queue<int, vector<int>, greater<int>> cost_que;
	for_each(v.begin(), v.end(), [&cost_que](const int n) {cost_que.push(n); });
	int min_cost = 0;
	while (cost_que.size() > 1) {
		min_cost = cost_que.top();
		cost_que.pop();
		min_cost += cost_que.top();
		cost_que.pop();
		cost_que.push(min_cost);
	}
	return cost_que.top();
}

int main() {
	vector<int> v{ 2,5,3,6,9 };
	cout << MinCost(v);
	system("pause");
	return 0;
}