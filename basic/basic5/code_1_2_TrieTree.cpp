 /*
 牛客算法初级班第五课第一二题，前缀树的应用
 @2018/1/30
 */
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int pass = 0;
	int end = 0;
	map<const char, shared_ptr<Node>> nodes;
};

class TrieTree {
public:
	TrieTree() {
		root = make_shared<Node>();
	}
	shared_ptr<Node> GetRoot() {
		return root;
	}
	void Add(const string &s) {
		shared_ptr<Node> tmp = root;
		decltype(tmp->nodes.insert({ 'a',make_shared<Node>() })) ad;//pair:第一项为map的pair，第二项为bool。第一项的第一项为char，第二项为指针
		for (auto &i : s) {
			ad = tmp->nodes.insert({ i,make_shared<Node>() });
			tmp = ad.first->second;
			++tmp->pass;
		}
		++tmp->end;
	}
	void Delete(const string &s) {
		shared_ptr<Node> tmp = root;
		if (Search(s)) {
			for (auto &i : s) {
				if (--tmp->nodes[i]->pass == 0) {
					tmp->nodes.erase(i);
					return;
				}
				tmp = tmp->nodes[i];
			}
			--tmp->end;
		}
	}
	bool Search(const string &s) {
		shared_ptr<Node> tmp = root;
		map<const char, shared_ptr<Node>>::iterator it;
		for (auto &i : s) {
			it = tmp->nodes.find(i);
			if (it == tmp->nodes.end()) {
				return false;
			}
			tmp = it->second;
		}
		return tmp->end != 0;
	}
	bool PreSearch(const string &s) {
		shared_ptr<Node> tmp = root;
		decltype(tmp->nodes.find('a')) it;
		for (auto &i : s) {
			it = tmp->nodes.find(i);
			if (it == tmp->nodes.end()) {
				return false;
			}
			tmp = it->second;
		}
		return true;
	}
private:
	shared_ptr<Node> root;
};

int main() {
	TrieTree tree;
	vector<string> vs1{ "qwe","qwer","qwert","asd","asdfg" };
	vector<string> vs2{ "qwer","asd","asdfga","asdf" };
	//string s = "bac";
	//string s2 = "bcd";
	//cout << tree.GetRoot()->nodes.size()<<" " ;
	//tree.Add(s);
	//cout << tree.GetRoot()->nodes.size() << " ";
	//cout << tree.GetRoot()->nodes['b']->pass << " ";
	//tree.Add(s2);
	//cout << tree.GetRoot()->nodes.size() << " ";
	//cout << tree.GetRoot()->nodes['a']->pass << " ";
	//cout << tree.Search("sc");
	//tree.Delete(s);
	for_each(vs1.begin(), vs1.end(), [&tree](const string &s) {tree.Add(s); });
	for_each(vs2.begin(), vs2.end(), [&tree](const string &s)
	{if (tree.PreSearch(s)) { cout << s << " "; }});
	system("pause");
}