/*
牛客算法初级第四课第三题，给定花费，利润和项目数，求最大收益
思路：先按cost进小根堆，弹出可以做的按利润进入大根堆，选最大的
@2018/1/29
*/

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct CostProfit {
	CostProfit() = default;
	CostProfit(const int c,const int p):cost(c),profit(p){}
	int cost;
	int profit;
};

struct LessCost {
	bool operator()(CostProfit &a, CostProfit &b) {
		return a.cost > b.cost;
	}
};
struct LargePro {
	bool operator()(CostProfit &a, CostProfit &b) {
		return a.profit < b.profit;
	}
};

int MaxPro(vector<int> &c, vector<int> &p, int k, int m) {
	int len = c.size();
	if (len != p.size() || len == 0) {
		return 0;
	}
	k = min(len, k);
	priority_queue<CostProfit, vector<CostProfit>, LessCost> cost_q;
	priority_queue<CostProfit, vector<CostProfit>, LargePro> pro_q;
	int i = 0;
	for_each(c.begin(), c.end(), [&cost_q, &p, &i](int a) {cost_q.emplace(a, p[i++]); });
	while (k-- > 0) {
		while (!cost_q.empty() && cost_q.top().cost <= m) {
			pro_q.push(cost_q.top());
			cost_q.pop();
		}
		m += pro_q.top().profit;
		pro_q.pop();
	}
	return m;
}

int main() {
	vector<int> c = { 1,2,5 };
	vector<int> p = { 4,3,7 };
	int k = 2;
	int m = 3;
	/*priority_queue<int, vector<int>, com> pq;
	for_each(v.cbegin(), v.cend(), [&pq](const int n) {pq.push(n); });
	int n = 4;
	while (n-->0) {
		cout << pq.top() << " ";
		pq.pop();
	}*/
	/*priority_queue<CostProfit, vector<CostProfit>, LargePro> pro_q;
	pro_q.emplace(5, 5);
	pro_q.emplace(5, 7);*/
	cout << MaxPro(c, p, k, m) << endl;

	system("pause");
	return 0;
}