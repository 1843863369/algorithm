/*
ţ�ͽ��װ��һ�ε����⣺
���������⣺���ֵ����СֵС�ڵ���num������������
�������Ӵ���ص����⣬ʹ�ô��ڣ�����ʹ��˫�˶���ʵ�֣�ʱ���index����ֵ��С����
@2018/1/8
*/

#include <vector>
#include <deque>
#include <iostream>
#include <climits>
#include <random>

using namespace std;


//for test
//ʵ�ִ��ڽṹ���õ�L��R�м�������������ֵ
int vectorMax(vector<int> &v,size_t L, size_t R) {//���ڰ����˵㣺L,R
	deque<int> max_deq;
	for (auto i = L; i <= R; ++i) {
		while ( !max_deq.empty() && v[max_deq.back()] <= v[i]) {
			max_deq.pop_back();
		}
		max_deq.push_back(i);
	}
	return max_deq.front();
}

int subLessEquNum(vector<int> &v,int num) {//�ؼ��㣺���������i-j���ϣ���ôi-j�����������鶼���ϡ�
	//��0��ʼ��������i��ͷ��������
	//Rֻ����
	deque<int> max_deq, min_deq;
	int i = 0, R= 0;
	int len = v.size();
	int result = 0;
	while (i < len) {//��i��ͷ��
		while (R < len) {
			while (!max_deq.empty() && v[max_deq.back()] <= v[R]) {
				max_deq.pop_back();
			}
			max_deq.push_back(R);
			while (!min_deq.empty() && v[min_deq.back()] >= v[R]) {
				min_deq.pop_back();
			}
			min_deq.push_back(R);
			if (v[max_deq.front()] - v[min_deq.front()] <= num) {//ע��Ҫ�Ƚ�vector�е�ֵ���������д����index
				//ֻҪ����������Rһֱ������
				
				++R;
			}
			else {
				break;
			}
		}//����ѭ������,��������result+  i-R�����������������i	
		result += R - i;	
		printf("%d �� %d �е����������飬һ���� %d ��\n", i, R-1, R-i);
		//����i֮ǰ�����жϵ�ǰi�Ƿ��ڶ����У������Ҫ���������ھͿ���ֱ���ƶ�i
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
	cout << "һ���� "<<num << " ��"<< endl;
	system("pause");
	return 0;
}