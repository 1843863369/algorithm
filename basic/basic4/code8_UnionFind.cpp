/*
牛客算法初级班第四课第八题，并查集
@2018/1/31
*/

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	Node() = default;
	Node(const int i):data(i){}
	int data;
};
class UnionFind {
	map<Node*, Node*> parents;
	map<Node*, int> rank;
public:
	UnionFind() = default;
	UnionFind(vector<Node*> &v)	{
		for_each(v.begin(), v.end(), [&](Node* &n) { 
			this->rank.insert({ n,1 }); this->parents.insert({ n,n });});
	}
	
	Node* FindParent(Node* n) {
		if (parents[n] != n) {
			parents[n] = FindParent(parents[n]);
		}
		return parents[n];
	}

	bool isSameSet(Node* a, Node *b) {
		Node *ap = FindParent(a);
		Node *bp = FindParent(b);
		return ap == bp;
	}

	void Union(Node* a, Node* b) {
		Node* ap = FindParent(a);
		Node* bp = FindParent(b);
		if (ap != bp) {
			if (rank[ap] >= rank[bp]) {
				parents[bp] = ap;
				rank[ap] = rank[ap] + rank[bp];
				rank.erase(bp);
			}
			else {
				parents[ap] = bp;
				rank[bp] = rank[ap] + rank[bp];
				rank.erase(ap);
			}
		}
	}
};
//Node* FindParent(Node* n, map<Node*, Node*> &parents) {
//	if (parents[n] != n) {
//		parents[n] = FindParent(parents[n],parents);
//	}
//	return n;
//}

int main() {
	Node* h1 = new Node(1);
	Node* h2 = new Node(2);
	Node* h3 = new Node(3);
	Node* h4 = new Node(4);
	vector<Node*> v{ h1,h2 };
	map<Node*, Node*> parents{ {h1,h2},{h2,h3},{h3,h4},{h4,h4} };
	/*for (auto &i : parents) {
		cout << i.first->data << " " << i.second->data << endl;
	}
	FindParent(h1, parents);
	for (auto &i : parents) {
		cout << i.first->data << " " << i.second->data << endl;
	}*/


	
	//for_each(v.begin(), v.end(), [&](Node* &n) {parents.insert({ n,n }); rank.insert({ n,1 }); });
	//u(v);
		//for_each(v.begin(), v.end(), [&](Node* &n) { rank.insert({ n,1 }); });
		//cout << parents.size();
	
	UnionFind uf(v);
	cout << uf.isSameSet(h1, h2);
	
	system("pause");
	return 0;
}