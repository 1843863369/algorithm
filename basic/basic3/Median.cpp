/*
牛客初级三四作业：求中位数
https://www.nowcoder.com/questionTerminal/5f44c42fd21a42b8aeb889ab83b17ad0
@2018/1/26

*/

#include <queue>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;


class Solution {
	priority_queue<double,vector<double>,greater<double>> min_q;
	priority_queue<double> max_q;
	int count = 0;
	
public:
	void Insert(int num)
	{
		++count;
		if (count % 2 != 0) {
			if (min_q.empty()|| num <= min_q.top()) {
				max_q.push(num);
			}
			else {
				min_q.push(num);
				max_q.push(min_q.top());
				min_q.pop();
			}
			
		}
		else {
			max_q.push(num);
			min_q.push(max_q.top());
			max_q.pop();
		}
	}
	double GetMedian()
	{
		return count % 2 != 0 ? max_q.top() : (min_q.top() + max_q.top()) / 2;

	}
};

//bool greater(double a, double b) {
//	return a < b;
//}



int main() {
	vector<double> v = { 5,2,3,4,1,6,7,0,8 };
	//sort(v.begin(), v.end(), [](int a, int b) {return a < b; });
	//for_each(v.begin(), v.end(), [](const int i) {cout << i << " "; });
	//cout << endl;
	priority_queue <double> pq(v.begin(), v.end());
	//for_each(pq.begin(), pq.end(), [](const int i) {cout << i << " "; });
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
	double res;
	Solution s;
	for (auto &i : v) {
		s.Insert(i);
		res = s.GetMedian();
		cout << res << " " << endl;
	}
	
	////double res = getMedian(v);

	system("pause");
	return 0;
}