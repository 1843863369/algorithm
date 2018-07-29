/*
ţ�����������һ�Σ���������arr������������������������ֵ�Ƕ��٣�O(N)��
����������Ͱ����ԭ������������������������������ȷ��� N+1 ��Ͱ��ÿ���ǿ�Ͱ���������ķǿ�Ͱ�Ƚ�
@2018/1/20
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

//���صڼ���Ͱ����0��ʼ���
int WhichBucket(int n, int max_v, int min_v, int len) {
	return (n - min_v) * len / (max_v - min_v); //ע����len ����len+1
}

int MaxGap(vector<int> v) {
	int len = v.size();
	if (len <= 1) {
		return 0;
	}
	//find max and min of vec
	int max_v = v[0];
	int min_v = v[0];
	for (int i = 1; i < len; ++i) {
		max_v = max(max_v, v[i]);
		min_v = min(min_v, v[i]);
	}
	if (max_v == min_v) {
		return 0;
	}
	//N+1 buckets
	vector<bool> bstatus(len + 1); //empty bucket? false=empty
	vector<int> max_vector(len + 1);//max value of the ith bucket
	vector<int> min_vector(len + 1);//min value of the ith bucket
	int bucket_num;
	for (int i = 0; i < len; ++i) {//��Ͱ��Ͱ������vec���
		bucket_num = WhichBucket(v[i], max_v, min_v, len);
		max_vector[bucket_num] = bstatus[bucket_num] ? max(max_vector[bucket_num], v[i]) : v[i];
		min_vector[bucket_num] = bstatus[bucket_num] ? min(min_vector[bucket_num], v[i]) : v[i];
		bstatus[bucket_num] = true;
	}
	//0�ź�len��Ͱ��ȻΪtrue
	int res = 0;
	//int last_max = max_vector[0];
	//for (int i = 0; i < len + 1; ++i) {
	//	if (bstatus[i]) {
	//		res = max(res, min_vector[i] - last_max);
	//		last_max = max_vector[i];
	//	}
	//}
	int last_not_emp, next_not_emp = 0;
	while(next_not_emp < len + 1) {
		if (!bstatus[next_not_emp]) {//if it is empty, find the last and the next not empty
			last_not_emp = next_not_emp - 1;
			next_not_emp = next_not_emp + 1;
			while (!bstatus[next_not_emp]) {
				++next_not_emp;
			}
			res = max(res, min_vector[next_not_emp] - max_vector[last_not_emp]);
		}
		else {
			++next_not_emp;
		}
		
	}
	return res;

}

int comparator(vector<int> v) {
	int len = v.size();
	sort(v.begin(),v.end());
	int max_gap = 0;
	for (int i = 1; i < len; ++i) {
		max_gap = max(max_gap, v[i] - v[i - 1]);
	}
	return max_gap;

}

vector<int> generateVec(int len,int min,int max) {
	static default_random_engine e;
	static uniform_int_distribution<> u(min, max);
	vector<int> v;
	for (int i = 0; i < len; ++i) {
		v.push_back(u(e));
	}
	return v;
}
void printVec(vector<int> &v) {
	if (v.size() == 0) {
		return;
	}
	for (auto &a : v) {
		cout.width(3);
		cout << a << " ";
	}
	cout << endl;
}
int main() {
	vector<int> v;
	int times = 50;
	while (times-- > 0) {
		v = generateVec(10, -20, 20);
		//printVec(v);
		//cout << MaxGap(v) << endl;
		//cout << comparator(v) << endl;
		cout << ((MaxGap(v)==comparator(v))? "^-^^-^":"!!!!!!!!!!!") << endl;
		
	}
	system("pause");
	return 0;
}