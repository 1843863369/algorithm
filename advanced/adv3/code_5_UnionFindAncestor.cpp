/*
牛客进阶第三课第五题，查找二叉树中两个节点的最近公共祖先，O(M+N)
使用并查集
@2018/3/4
*/

#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

class Node {
public:
	Node(const int i):data(i),left(nullptr),right(nullptr){}
	int data;
	Node* left;
	Node* right;
};
class UnionFind {
public:
	void makeSet(Node *head) {
		if (head == nullptr)
			return;
		father.insert({ head,head });
		rank.insert({ head,0 });
		makeSet(head->left);
		makeSet(head->right);
	}
	Node* findFather(Node *node) {
		if (father[node] != node) {
			father[node] = findFather(father[node]);
		}
		return father[node];
	}
	bool isSame(Node *a, Node *b) {
		Node *af = findFather(a);
		Node *bf = findFather(b);
		return af == bf;
	}
	void Union(Node* a, Node* b) {
		if (a == nullptr || b == nullptr)
			return;
		Node *af = findFather(a);
		Node *bf = findFather(b);
		if (af != bf) {
			if (rank[a] > rank[b]) {
				father[bf] = af;
				rank[af] = rank[af] + rank[bf];
				rank.erase(bf);
			}
			else {
				father[af] = bf;
				rank[bf] = rank[bf] + rank[af];
				rank.erase(af);
			}
		}
	}

private:
	map<Node*, Node*> father;
	map<Node*, int> rank;
};

class Query {
public:
	Node *o1;
	Node *o2;
	Query(Node *o11, Node *o22) :o1(o11), o2(o22){}
};

class Tarjan {
public:
	vector<Node*> query(Node *head, vector<Query*> &que) {
		sets.makeSet(head);
		vector<Node*> ans(que.size());
		setQuery(que, ans);
		setAns(head, ans);
		return ans;

	}
	//将que的内容扩展为两倍，添加到queryMap
	void setQuery(vector<Query*> &que, vector<Node*> &ans) {
		int len = que.size();
		Node *o1_t = nullptr;
		Node *o2_t = nullptr;
		for (int i = 0; i < len; ++i) {
			o1_t = que[i]->o1;
			o2_t = que[i]->o2;
			if (o1_t == o2_t || nullptr == o1_t || nullptr == o2_t) {
				ans[i] = o1_t != nullptr ? o1_t : o2_t;
			}
			else {
				queryMap[o1_t].push_back(o2_t);
				ansMap[o1_t].push_back(i);
				queryMap[o2_t].push_back(o1_t);
				ansMap[o2_t].push_back(i);
			}
		}
	}

	void setAns(Node *head, vector<Node*> &ans) {
		if (head == nullptr)
			return;
		setAns(head->left, ans);
		sets.Union(head->left, head);
		anscetorMap.insert({ sets.findFather(head),head });
		setAns(head->right, ans);
		sets.Union(head->right, head);
		anscetorMap.insert({ sets.findFather(head),head });
		vector<Node*> nVec;
		vector<int> iVec;
		Node *node = nullptr;
		Node *nFather = nullptr;
		int index = 0;
		if (queryMap.find(head) != queryMap.end()) {
			nVec = queryMap[head];
			iVec = ansMap[head];
			while (!nVec.empty()) {
				node = nVec.back();
				nVec.pop_back();
				index = iVec.back();
				iVec.pop_back();
				nFather = sets.findFather(node);
				if (anscetorMap.find(nFather) != anscetorMap.end()) {
					ans[index] = anscetorMap[nFather];
				}
			}
		}
	}
private:
	map<Node*, vector<Node*>> queryMap;
	map<Node*, vector<int>> ansMap;
	map<Node*, Node*> anscetorMap;
	UnionFind sets;

};

vector<Node*> ComAnscetor(Node *head, vector<Query*> &que) {
	vector<Node*> ans;
	Tarjan tar;
	ans = tar.query(head, que);
	return ans;
}

int main() {
	Node *head = new Node(1);
	head->left = new Node(2);
	head->right = new Node(3);
	head->left->left = new Node(4);
	head->left->right = new Node(5);
	head->right->left = new Node(6);
	head->right->right = new Node(7);
	head->right->right->left = new Node(8);
    
	vector<Query*> qs(7);
	qs[0] = new Query(head->left->right, head->right->left);
	qs[1] = new Query(head->left->left, head->left);
	qs[2] = new Query(head->right->left, head->right->right->left);
	qs[3] = new Query(head->left->left, head->right->right);
	qs[4] = new Query(head->right->right, head->right->right->left);
	qs[5] = new Query(head, head);
	qs[6] = new Query(head->left, head->right->right->left);

	vector<Node*> ans = ComAnscetor(head, qs);
	for_each(ans.begin(), ans.end(), [](Node* n) {cout << n->data << endl; });

	system("pause");
	return 0;

}