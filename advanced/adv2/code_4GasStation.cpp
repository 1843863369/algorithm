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
		cout << "输入参数错误！" << endl;
		return vector<bool>(false);
	}
	vector<bool> res(len);//默认初始化为false
	vector<int> h(len);
	int start = -1;
	for (int i = 0; i < len; ++i) {
		h[i] = gas[i] - cost[i];//油减去距离
		if (h[i] >= 0) {
			start = i;
		}
	}
	if (start < 0)
		return res;//start的初始值小于0，如果循环后i<0，说明没有大于0的点。return false
	//cout << "油量-距离:" << endl;
	//printVec(cost);
	int count = 0;
	int end = NextIndex(start,len);//end表示可到达的点，因为选取了大于0的点开始，所以第一步end必然可到达start的下一个
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
				end = NextIndex(end, len);//当前的rest>=0，必然可到达下一点
			}
			if (rest >= 0) {//跳出循环后，如果rest依旧>=0，说明end到了start的上一个点，true
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

//for test 对数器
vector<bool> comparator(vector<int> &dis, vector<int> &oil) {
	int len = dis.size();
	int sum = 0;
	if (len == 0 || len != oil.size()) {
		cout << "输入参数错误！" << endl;       
		return vector<bool>(false);
	}
	vector<int> h;
	vector<bool> res(len,true);
	for (int i = 0; i < len; ++i) {
		h.push_back(oil[i] - dis[i]);//油减去距离
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