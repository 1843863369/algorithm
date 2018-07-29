/*
ţ�����������һ������ҵ���͹�����
https://www.nowcoder.com/questionTerminal/d2cced737eb54a3aa550f53bb3cc19d0
@2018/1/21
*/

#include <iostream>
#include <string>
#include <vector>
#include<map>
#include <set>
#include <algorithm>

using namespace std;

void BuildPath(vector<vector<int>> &path, int i, int j, vector<int> &t, vector<int> &g, vector<int> &c);

int DPMaxBenifit(vector<int> &t, vector<int> &g, vector<int> &c) {
	int m = g.size();
	int n = t.size();
	if (m == 0 || n == 0 | m != c.size()) {
		return 0;
	}
	vector<vector<int>> table(m + 1, vector<int>(n + 1, 0));
	vector<vector<int>> path(m + 1, vector<int>(n + 1, 0));//��������Ϊ1����Ϊ0����Ϊ-1
	for (int j = 0; j < n; ++j) {//��j��
		for (int i = 0; i < m; ++i) {//��i��˿�
			if (g[i] <= t[j]) {
				table[i + 1][j + 1] = max(table[i][j] + c[i], max(table[i][j + 1], table[i + 1][j]));
				path[i + 1][j + 1] = (table[i + 1][j + 1] == table[i][j] + c[i]) ? 1 :
					(table[i + 1][j + 1] == table[i][j + 1] ? 0 : -1);
			}
			else {
				table[i + 1][j + 1] = max(table[i][j + 1],table[i+1][j]);
				path[i + 1][j + 1] = table[i][j + 1] >= table[i + 1][j] ? 0 : -1;
			}
		}
	}
	for (auto &i : table) {
		for (auto &j : i) {
			cout.width(2);
			cout << j << " ";
		}
		cout << endl;
	}
	BuildPath(path, m, n,t,g,c);

	return table[m][n];
}

int GreedyBenifit(multiset<int> &t, multimap<int,int> &m) {//consum:people
	int res = 0;
	multiset<int>::iterator min_table;
	
	for ( auto i = m.rbegin();i != m.rend(); ++i) {
		min_table = t.lower_bound(i->second);
		if (min_table != t.end()) {
			res += i->first;
			printf("%d�ˣ�����%d�Ŀ�����%d����\n", i->second, i->first, *min_table);
			t.erase(min_table);
		}
	}
	return res;
}
void BuildPath(vector<vector<int>> &path,int i,int j, vector<int> &t, vector<int> &g,vector<int> &c) {//�˿���i������j
	if (i == 0 || j == 0) {
		return;
	}
	if (path[i][j] == 1) {
		BuildPath(path, i - 1, j - 1, t, g, c);
		printf("%d�ˣ�����%d�Ĺ˿�����%d������\n", g[i-1], c[i-1],t[j-1]);
	}
	else if(path[i][j] == 0){
		BuildPath(path, i - 1, j, t, g, c);
	}
	else {
		BuildPath(path, i, j - 1, t, g, c);
	}
}



template <typename T>
void printVec(T &v) {
	if (v.size() == 0) {
		return;
	}
	for (auto &a : v) {
		cout.width(2);
		cout << a << " ";
	}
	cout << endl;
}



int main() {
	/*int num_table, num_guest;
	cout << "�����������ͱ���������" << endl;
	cin >> num_table >> num_guest;
	multiset<int> tables;
	multimap<int,int> guestm;
	vector<int> tablev(num_table);
	vector<int> guest;
	vector<int> consume;
	int i = num_table;
	int temp;
	int temp1;
	while (i-- > 0) {
		cin >> temp;
		tables.insert(temp);
	}
	tablev = { tables.begin(), tables.end() };
	printVec<multiset<int>>(tables);
	printVec<vector<int>>(tablev);
  	i = num_guest;
	while (i-- > 0) {
		cin >> temp >> temp1;;
		guestm.insert({ temp,temp1 });
	}
	for (auto &a : guestm) {
		guest.push_back(a.first);
		consume.push_back(a.second);
	}

	printVec<vector<int>>(guest);
	printVec<vector<int>>(consume);*/
	vector<int> tablev{ 1,4,7,12 };
	multiset<int> tables{ 1,4,7,12 };
	//vector<int> guest{ 1,1,3,3,5 };
	//vector<int> consume{ 3,10,5,7,9 };
	vector<int> guest{ 3,5,6,11,12,35 };
	vector<int> consume{ 10,9,7,3,10,10 };
	multimap<int, int> c_g;
	for (int j = 0; j < guest.size(); ++j) {
		c_g.insert({ consume[j],guest[j] });
	}
	

	cout << DPMaxBenifit(tablev, guest, consume) << endl;
	cout << GreedyBenifit(tables, c_g) << endl;
	system("pause");
}