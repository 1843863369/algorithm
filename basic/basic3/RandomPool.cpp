/*
牛客算法初级班第三课，第六题： 实现O(1)的insert，delete，getRandom:等概论随机返回任何一个key
@2018/1/23
*/

#include <iostream>
#include <random>
#include <map>
#include <vector>

using namespace std;

template <typename T>
class RandomPool {
public:
	void insert(T n) {
		if (my_set.find(n) == my_set.end()) {
			my_set.insert({n,index});
			help.insert({ index,n });
			++index;
		}
		
	}
	void erase(T n) {
		int i = my_set[n];
		T ende = help.rbegin()->second;
		if (n == ende) {
			my_set.erase(n);
			help.erase(i);
			return;
		}
		my_set.erase(n);
		my_set[ende] = i;
		help[i] = ende;
		help.erase(--help.end());
	}
	
	T getRandom() {
		int index = randomValue(my_set.size());
		return help[index];
	}
	void printSet() {
		if (!my_set.empty()) {
			for (auto &a : my_set) {
				cout << a.first << " "<<a.second;
			}
			cout << endl;
		}
	}
private:
	map<T, int> my_set;
	map<int, T> help;
	int index = 0;
	int randomValue(int n) {
		static default_random_engine e;
		static uniform_int_distribution<> u(0, n - 1);
		return u(e);
	}

};

int main() {
	string s = "abcdabcdqqqwetz";
	RandomPool<char> rpc;
	for (auto &a : s) {
		rpc.insert(a);
	}
	rpc.printSet();
	rpc.erase('z');
	rpc.printSet();
	rpc.erase('a');
	rpc.printSet();
	rpc.erase('d');
	rpc.printSet();
	int times = 30;
	while (times-- > 0) {
		cout << rpc.getRandom() << endl;
	}
	
	
	system("pause");
	return 0;
}