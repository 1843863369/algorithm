#include <iostream>
#include <vector>
#include <random>


using namespace std;

template <typename T>
void printVec(vector<T> &v);
inline int LastIndex(int index, int size) {
	return index == 0 ? (size - 1) : (index - 1);
}
inline int NextIndex(int index, int size) {
	return index == size - 1 ? 0 : (index + 1);
}

vector<bool> GasStation(vector<int> &gas, vector<int> &cost) {
	int len = cost.size();
	if (len == 0 || len != gas.size()) {
		cout << "�����������" << endl;
		return vector<bool>(false);
	}
	vector<bool> res(len);//Ĭ�ϳ�ʼ��Ϊfalse
	vector<int> h(len);
	int start = -1;
	for (int i = 0; i < len; ++i) {
		h[i] = gas[i] - cost[i];//�ͼ�ȥ����
		if (h[i] >= 0) {
			start = i;
		}
	}
	if (start < 0)
		return res;//start�ĳ�ʼֵС��0�����ѭ����i<0��˵��û�д���0�ĵ㡣return false
	//cout << "����-����:" << endl;
	//printVec(cost);
	int count = 0;
	int end = NextIndex(start,len);//end��ʾ�ɵ���ĵ㣬��Ϊѡȡ�˴���0�ĵ㿪ʼ�����Ե�һ��end��Ȼ�ɵ���start����һ��
	int need = 0;
	int rest = 0;
	while (count < len) {
		if (h[start] < need) {
			need -= h[start];
		}
		else {
			rest += h[start] - need;
			need = 0;
			while (rest >= 0 && end != start) {		
				rest += h[end];
				end = NextIndex(end, len);//��ǰ��rest>=0����Ȼ�ɵ�����һ��
			}
			if (rest >= 0) {//����ѭ�������rest����>=0��˵��end����start����һ���㣬true
				res[start] = true;				
				end = LastIndex(end, len);	
				rest = rest - h[end];
			}
		}
		start = LastIndex(start, len);
		++count;
	}
	return res;
}

//for test ������
vector<bool> comparator(vector<int> &dis, vector<int> &oil) {
	int len = dis.size();
	int sum = 0;
	if (len == 0 || len != oil.size()) {
		cout << "�����������" << endl;       
		return vector<bool>(false);
	}
	vector<int> h;
	vector<bool> res(len,true);
	for (int i = 0; i < len; ++i) {
		h.push_back(oil[i] - dis[i]);//�ͼ�ȥ����
	}
	// cout << "h:" << endl;
	//printVec(h);
	for (int k = 0; k < len; ++k) {
		sum = 0;
		for (int count = 0; count < len; ++count) {
			sum += h[(k + count)%len];
			if (sum < 0) {
				res[k] = false;
				break;
			}
		}
	}
	return res;
		
}

//for test
vector<int> getPosVec(int l,int r) {
	vector<int> v;
	static default_random_engine e;
	static uniform_int_distribution<unsigned> u(l,r);
	for (int i = 0; i < 10; ++i) {
		v.push_back(u(e));
	}
	return v;
}
//for test
template <typename T>
void printVec(vector<T> &v) {
	if (v.size() == 0) {
		cout << "no vector to print" << endl;
		return;
	}
	for (auto &i : v) {
		cout.width(3);
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<int> dis, oil;
	vector<bool >res, com;
	for (int i = 0; i < 10; ++i) {
		dis = getPosVec(0,9);
		//cout << "distance:" << endl;
		//printVec(dis);
		oil = getPosVec(7,19);
		//cout << "oil:" << endl;
		//printVec(oil);
		com = comparator(dis, oil);
		res = GasStation(oil, dis);
		//cout << "result:" << endl;
		//printVec(com);
		//printVec(res);
		/*if (com == res) {
			cout << "right!" << endl;
		}*/
		if(com != res) {
			cout << "distance:" << endl;
			printVec(dis);
			cout << "oil:" << endl;
			printVec(oil);
			cout << "result:" << endl;
			printVec(com);
			cout << "====================================" << endl;
		}
	}
	
	//cout << boolalpha<<true;
	system("pause");
	return 0;

}