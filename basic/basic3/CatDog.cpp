/*
牛客初级班三四节作业：
https://www.nowcoder.com/questionTerminal/6235a76b1e404f748f7c820583125c50
@2018/1/25
*/

#include <vector>
#include <iostream>
#include <queue>
#include <utility>


using namespace std;

vector<int> CatDogQueue(vector<vector<int>> &ope) {
	int len = ope.size();
	vector<int> res;
	if (len == 0) {
		return { 0 };
	}
	queue<pair<int,int>> dog;
	queue<pair<int,int>> cat;
	int num = 0;
	vector<int> i;
	for (auto &i:ope) {
		if (1 == i[0]) {//in
			if (i[1] > 0) {
				dog.push(make_pair(i[1],num++));//编号
			}
			else if (i[1] < 0) {
				cat.push(make_pair(i[1],num++));
			}
		}
		if (2 == i[0]) {//out
			if (1 == i[1] && !dog.empty()) {
				res.push_back(dog.front().first);
				dog.pop();
			}
			if (-1 == i[1] && !cat.empty()) {
				res.push_back(cat.front().first);
				cat.pop();
			}
			if (0 == i[1]) {
				if (((!dog.empty() && !cat.empty()) && (dog.front().second < cat.front().second))
					|| (!dog.empty() && cat.empty())) {
					res.push_back(dog.front().first);
					dog.pop();
				}
				else if (((!dog.empty() && !cat.empty()) && (dog.front().second > cat.front().second))
					|| (dog.empty() && !cat.empty())) {//第一次错误是因为没加else，导致上一个if中pop后还能进到下一个if
					res.push_back(cat.front().first);
					cat.pop();

				}

			}
		}

	}
	return res;
}

int main() {
	vector<vector<int>> v = 
		{{1, -5}, {1, -1}, {1, 9}, {1, 9}, {2, 0}, {2, 1}, {1, -8}, {2, 1},
		{1, -71}, {1, -92}, {1, 18}, {1, 91}, {1, 61}, {2, -1}, {1, -35}, {1, 95}, 
		{1, -49}, {1, 9}, {1, 78}, {2, 0}, {1, 91}, {1, -96}, {2, -1}, {2, 0}, {2, -1},
		{2, 1}, {1, 38}, {2, 0}, {1, 45}, {2, 0}, {1, -51}, {2, 1}, {2, 1}, {2, -1}, {1, 39}, 
		{1, 59}, {1, 45}, {2, 0}, {1, -70}, {2, 0}, {1, 23}, {1, 88}, {1, 83}, {1, 69}, {1, -78}, 
		{1, -3}, {1, -9}, {1, -20}, {1, -74}, {1, -62}, {1, 5}, {1, 55}, {1, -36}, {1, -21}, {1, -94},
		{1, -27}, {1, -69}, {2, 0}, {1, -30}, {1, -84}, {2, 0}, {2, 0}, {2, -1}, {1, 92}, {1, 60},
		{2, 1}, {2, 0}, {1, -63}, {2, 0}, {1, -87}, {1, 66}, {2, 0}, {1, 17}, {2, 0}, {2, 1}, {1, -41},
		{1, -3}, {1, -29}, {1, 72}, {2, 1}, {1, 35}, {1, 81}, {1, -83}, {1, -17}, {1, 36}, {1, 99}, 
		{1, -17}, {1, 8}, {2, 0}, {1, 80}, {1, 50}, {1, 80}, {2, 0}, {1, -48}, {1, -82}, {1, -63},
		{1, 2}, {2, 1}, {1, -43}, {1, 59}, {1, 93}, {1, 55}, {1, -93}, {2, -1}, {1, 2}, {1, 13}, {2, 0}};

	vector<vector<int>> v1 = { { 1, 5 },{ 1, 55 },{ 1, -36 },{ 1, -21 },{ 1, -94 },
	{ 1, -27 },{ 1, -69 },{ 2, 0 },{ 1, -30 },{ 1, -84 },{ 2, 0 },{ 2, 0 },{ 2, -1 } };
	vector<int> res = CatDogQueue(v1);
	for (auto &i : res) {
		cout << i << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}