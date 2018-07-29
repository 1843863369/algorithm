/*
ţ���㷨���׵����ε�һ�⣺����ۼӺ�����С���ĳ˻�
˼·��ʹ�õ���ջ����ÿһ�����ҵ�����С����������ı߽磬����Ϊ��Χ����Сֵ���������¼sum��
������ջ�����ϵ��µ�����������ջ���ϵ��µݼ�����Сֵ���ü�ջ��
�״���51����sum����ʼ������arr����Ϊ����ǰ�ѽ�У�飬sum����Ҫ�ж�l��
        cur_min�����ֵ꣬��arr[cur_min]
		Ҫ������������и������Ը�����sumʱҪ����С��
@2018/2/2
*/

#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>

using namespace std;

//��l-r���ۼӺͣ�������l��r��sumΪ�ۼӺ�����
inline int Sum(vector<int> &sum, int l, int r) {
	return sum[r - 1] - sum[l];
}
//��l-r���ۼӺͣ�����l��r��sumΪ�ۼӺ�����
inline int lrSum(vector<int> &sum, int l, int r) {
	return l == 0 ? sum[r] : sum[r] - sum[l - 1];
}

int MaxTimes(vector<int> &arr) {
	stack<int> l_s;//from up to sown:large to small;
	int len = arr.size();
	vector<int> sum(arr);
	if (len == 0) {
		return 0;
	}
	if (len == 1) {
		return arr[0] * arr[0];
	}
	for (int i = 1; i < len; ++i) {
		sum[i] += sum[i - 1];
	}
	int cur_min = 0;
	int cur_sum = 0;
	int res = INT_MIN;
	int left = 0;
	int right = 0;
	int f_min = 0;
	int f_sum = 0;
	for (int i = 0; i < len; ++i) {
		while (!l_s.empty() && arr[i] <= arr[l_s.top()]) {
			cur_min = l_s.top();
			l_s.pop();
			cur_sum = l_s.empty() ? sum[i-1] : Sum(sum, l_s.top(), i);
			//res = max(res, cur_sum*cur_min);
			if (res < cur_sum*arr[cur_min]) {
				res = cur_sum*arr[cur_min];
				left = l_s.empty() ? -1:l_s.top();
				right = i;
				f_min = arr[cur_min];
				f_sum = cur_sum;
			}
		}
		l_s.push(i);
	}
	while (!l_s.empty()) {
		cur_min = l_s.top();
		l_s.pop();
		cur_sum = l_s.empty() ? sum[len-1] : Sum(sum, l_s.top(), len);
		//res = max(res, cur_sum*cur_min);
		if (res < cur_sum*arr[cur_min]) {
			res = cur_sum*arr[cur_min];
			left = l_s.empty() ? -1:l_s.top();
			right = len;
			f_min = arr[cur_min];
			f_sum = cur_sum;
		}
	}
	cout << "Max:" << endl;
	printf("from %d to %d, the min is %d,the sum is %d,the result is %d", left, right, f_min, f_sum, res);
	return res;
}

int comparator(vector<int> &arr) {
	int len = arr.size();
	vector<int> sum(arr);
	if (len == 0) {
		return 0;
	}
	if (len == 1) {
		return arr[0] * arr[0];
	}
	for (int i = 1; i < len; ++i) {
		sum[i] += sum[i - 1];
	}
	int cur_min = 0;
	int cur_sum = 0;
	int res = INT_MIN;
	int fmin = cur_min;
	int fsum = cur_sum;
	int left;
	int right;
	for (int i = 0; i < len; ++i) {
		for (int j = i; j < len; ++j) {//��j��β����j
			cur_sum = lrSum(sum, i, j);
			cur_min = i;
			for (int k = i; k <= j; ++k) {
				cur_min = arr[cur_min] > arr[k] ? k : cur_min;
			}
			//res = max(res, cur_min*cur_sum);
			if (res < arr[cur_min]*cur_sum) {
				res = arr[cur_min]*cur_sum;
				left = i;
				right = j;
				fmin = cur_min;
				fsum = cur_sum;
			}
		}
	}
	cout << "com:" << endl;
	printf("from %d to %d, the min is %d,the sum is %d,the result is %d", left, right, arr[fmin], fsum, res);

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
	int time = 30;
	//while(time-- > 0) {
		generateVec();
		generateVec();
		generateVec();
		vector<int> v = generateVec();
		cout << "���飺" << endl;
		printVec(v);
		cout << "comp:" << endl;
		cout << comparator(v) << endl;
		cout << "Max:" << endl;
		cout << MaxTimes(v) << endl;
		//cout << (comparator(v) == MaxTimes(v)) << endl;
		cout << "=======================" << endl;
	//}
	
	system("pause");
	return 0;
}