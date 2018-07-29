/*
ţ�����㷨���װ��һ�µ�6�⣺����������������������
ʹ��ǰ׺������ÿ�����ֵ�ÿһλ�����������Ҫ�����λ��ʼʹ����Ľ��Ϊ1��
����λ����һ����ͬ�š�

�������Ƚ���������⣺����  ������MaxSumSub
�ڽ��XOR 

@2018/1/10

*/

#include <deque>
#include <vector>
#include <iostream>
#include <tuple>
#include <random>
#include <memory>
#include <map>
#include <climits>
#include <bitset>

using namespace std;
typedef tuple<int, int, int> Result;

//�������������е����ͣ�ʹ������˫�˶��У��ֱ𱣴����ͺ���С�ͣ���֤��ͷ����ֵ
Result MaxSumSub(vector<int> &v) {
	int sum = 0;
	int res = 0;
	int len = v.size();
	if (len == 0)
		return Result(0,0,0);
	int R = 0;
	int fR = 0, fL = 0;
	deque<int> max_sum, min_sum,max_index,min_index;
	while (R < len) {
		sum += v[R];
		while (!max_sum.empty() && max_sum.back() < sum) {//ֵ���ʱ������������Ķ�Ӧ���������������������
			//ֻҪ�����и�С��ֵ����һֱ����
			max_sum.pop_back();
			max_index.pop_back();
		}
		max_sum.push_back(sum); 
		max_index.push_back(R);
		while (!min_sum.empty() && min_sum.back() > sum) {
			min_sum.pop_back();
			min_index.pop_back();
		}
		min_sum.push_back(sum);
		min_index.push_back(R);
		++R;
	}
	int min_s = min_sum.front();
	int max_s = max_sum.front();
	int min_i = min_index.front();
	int max_i = max_index.front();
	
	if (min_s < 0 && min_i < max_i) {
		res = max_s - min_s;
	}
	else {
		res = max_s;
	}
	Result results(res, min_i+1, max_i);
	return results;
	
}


class NumTrie;
//�ڵ�
class Node {
	friend class NumTrie;
public:
	Node() = default;
	Node(const int i) :data(i), right(nullptr), left(nullptr) { }

	int getData() {return data;}
	shared_ptr<Node> getLeft() {return left;}
	shared_ptr<Node> getRight() {return right;}
	void setLeft(shared_ptr<Node> n) { left = n; }
	void setRight(shared_ptr<Node> n) { right = n; }

private:
	int data;
	shared_ptr<Node> left;
	shared_ptr<Node> right;
};
//ǰ׺��
class NumTrie {
public:
	NumTrie():head(nullptr){}
	shared_ptr<Node> head;

	void add(int num, int index); //��ǰ׺���������,���λ��������λ��ǰ
	tuple<int, int> maxXOR(int num); //����һ��num,�ҵ�������num����õ��������ֵ�������������;
	shared_ptr<Node> next(int n, shared_ptr<Node> cur) {//������ǰλ 0 ��1���͵�ǰ�ڵ� ���ж���һ�����ﵱǰ�ڵ������ӻ����Һ���
		/*if (n == 1) {
			if (cur->getLeft() == nullptr) {
				return cur->getRight();
			}
			return cur->getLeft();
		}
		if (n == 0) {
			if (cur->getRight() == nullptr)
				return cur->getLeft();
			return cur->getRight();
		}
	}*/
		
		return n == 1 ? (cur->getLeft() == nullptr ? cur->getRight() : cur->getLeft())
			: (cur->getRight() == nullptr ? cur->getLeft() : cur->getRight());
	}

};

void NumTrie::add(int num,int index) { //��ǰ׺���������,���λ��������λ��ǰ
	if (head == nullptr) {
		shared_ptr<Node> nh = make_shared<Node>(0);
		head = nh;
	}
	shared_ptr<Node> cur(head);
	for (int move = 31; move >= 0; --move) {
		int path = (num >> move) & 1;
		//cout << path << " ";
		if (0 == path) {
			if (cur->getLeft() == nullptr) {
				shared_ptr<Node> n0 = make_shared<Node>(0);
				//cout << path << " ";
				cur->setLeft(n0);
			}
			cur=cur->getLeft();
		}
		if (path == 1) {
			if (cur->getRight() == nullptr) {
				shared_ptr<Node> n1 = make_shared<Node>(1);
				cur->setRight(n1);
			}
			cur=cur->getRight();
		}

	}
	//cout << index << endl;
	shared_ptr<Node> nd = make_shared<Node>(index);
	cur->setLeft(nd);//ǰ׺�����һλ�����Ӽ�¼index
}
	    
	



tuple<int,int> NumTrie::maxXOR(int num) {
	shared_ptr<Node> cur(head);
	int res = 0;
	int sign = (num >> 31) & 1;
	cur = next(sign^1,cur);
	res |= ((sign ^ (cur->data)) << 31);//������λ����ԭ����32λ
	for (int move = 30; move >= 0; --move) {
		int path = (num >> move) & 1;
		cur = next(path, cur);
		res |= ((path ^ cur->data) << move);//��ǰ׺���еļ�¼�뵱ǰֵ���ԭ��int
	}
	tuple<int, int> results(res, cur->getLeft()->data);
	return results;
}

tuple<int,int,int> MaxXORSub(vector<int> &v) {
	int len = v.size();
	if (0 == len) {
		return tuple<int,int,int>(0,0,0);
	}
	int xor_res = 0;
	int max_xor = INT_MIN;
	int L = 0, R = 0;
	tuple<int, int> temp_res;
	NumTrie tree;
	tree.add(0, -1);//�ȼ���һ��0ֵ������Ϊ-1.0-i�Ѿ�Ϊ���ֵʱ�������ֵ��0
	//������������
	for (int i = 0; i < len; ++i) {
		xor_res ^= v[i];
		temp_res = tree.maxXOR(xor_res);
		if (max_xor < get<0>(temp_res)) {
			max_xor = get<0>(temp_res);
			L = get<1>(temp_res)+1;
			R = i;
		}
		tree.add(xor_res,i);
	}
	tuple<int, int, int> results(max_xor, L, R);
	return results;
}

tuple<int, int, int> comparator(vector<int> &v) {
	int len = v.size();
	int max = INT_MIN;
	int L = 0, R = 0;
	int temp_res = 0;
	for (int i = 0; i < len; ++i) {//i��β
		for (int j = i; j >= 0; --j) {
			temp_res ^= v[j];
			if (temp_res > max) {
				max = temp_res;
				L = j;
				R = i;
			}
		}
		temp_res = 0;
	}
	tuple<int, int, int> results(max, L, R);
	return results;
}

vector<int> generateVec() {
	vector<int> v;
	static default_random_engine e;
	static uniform_int_distribution<> u(-9, 9);
	for (int i = 1; i <= 10; ++i) {
		v.push_back(u(e));
	}
	return v;
}

void printVec(vector<int> &v) {
	if (!v.empty()) {
		cout << "����: " << endl;
		for (auto &a : v) {
			cout << a << " ";
		}
		cout << endl;
	}
}



int main() {
	vector<int> v = generateVec();
	printVec(v);


	//cout << get<0>(t.maxXOR(0)) << "       ";
	/*Result res = MaxSumSub(v);
	printf("����Ϊ %d ����߽磺%d ���ұ߽磺%d\n",get<0>(res), get<1>(res), get<2>(res));
	cout << "========================================" << endl;*/
	
	Result res = MaxXORSub(v);
	Result com = comparator(v);
	printf("MAX�������Ϊ %d ����߽磺%d ���ұ߽磺%d\n", get<0>(res), get<1>(res), get<2>(res));
	printf("com�������Ϊ %d ����߽磺%d ���ұ߽磺%d\n", get<0>(com), get<1>(com), get<2>(com));
	cout << "========================================" << endl;

	vector<int> v1 = generateVec();
	printVec(v1);
	/*Result res1 = MaxSumSub(v1);
	printf("����Ϊ %d ����߽磺%d ���ұ߽磺%d\n", get<0>(res1), get<1>(res1), get<2>(res1));
	cout << "========================================" << endl;*/

	Result res1 = MaxXORSub(v1);
	printf("MAX�������Ϊ %d ����߽磺%d ���ұ߽磺%d\n", get<0>(res1), get<1>(res1), get<2>(res1));
	Result com1 = comparator(v1);
	printf("com�������Ϊ %d ����߽磺%d ���ұ߽磺%d\n", get<0>(com1), get<1>(com1), get<2>(com1));
	cout << "========================================" << endl;

	vector<int> v2 = generateVec();
	printVec(v2);

	Result res2 = MaxXORSub(v2);
	printf("MAX�������Ϊ %d ����߽磺%d ���ұ߽磺%d\n", get<0>(res2), get<1>(res2), get<2>(res2));
	Result com2 = comparator(v2);
	printf("com�������Ϊ %d ����߽磺%d ���ұ߽磺%d\n", get<0>(com2), get<1>(com2), get<2>(com2));
	cout << "========================================" << endl;

	//cout << " -4: " << bitset<32>(-4) << endl;
	//cout << " 7: " << bitset<32>(7) << endl;
	//cout << " -1: " << bitset<32>(-1) << endl;
	//cout << " 3: " << bitset<32>(3) << endl;
	//cout << ((-4) ^ 7 ^ (-1) ^ 3) << endl;
	system("pause");
	return 0;
}


