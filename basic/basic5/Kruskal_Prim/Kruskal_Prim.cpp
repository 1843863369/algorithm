 /*
牛客算法初级班，图的常见算法：Kruskal算法，Prim算法,（无向图，有向图叫最小树形图）
K：用并查集，所有边入小根堆，小根堆弹出边，from和to在一个set不要，否则合并。本质上是集合之间的合并
P：任意一点开始，相临边入小根堆，最小堆弹出边，如果to在set中，舍弃，否则加入set，再将to的邻节点入堆
@2018/1/31
*/

#include "GraphGenerator.h"
#include "UnionFind.h"
#include <queue>

struct cmp {
	bool operator()(const Edge* a, const Edge* b) {
		return a->w > b->w;//最小堆，大于号
	}
};

vector<Edge*> PrimTree(Graph *graph) {
	priority_queue<Edge*, vector<Edge*>, cmp> less_edge;
	set<Node*> filter;
	vector<Edge*> res;
	Node *cur_node = nullptr;
	Edge *cur_edge = nullptr;
	for (auto &i : graph->nodes) {
		cur_node = i.second;
		if (filter.find(cur_node) == filter.end()) {
			filter.insert(cur_node);
			for (auto &e : cur_node->edges) {
				less_edge.push(e);
			}
			while (!less_edge.empty()) {
				cur_edge = less_edge.top();
				less_edge.pop();
				if (filter.find(cur_edge->to) == filter.end()) {//to节点不在set中，此边加入结果,to加入filter
					res.push_back(cur_edge);
					filter.insert(cur_edge->to);
					for (auto &n : cur_edge->to->edges) {
						less_edge.push(n);
					}
				}
			}
		}
	}
	return res;

}

vector<Edge*> KruTree(Graph *graph) {
	vector<Node*> node;
	vector<Edge*> res;
	for (auto &n : graph->nodes) {
		node.push_back(n.second);
	}
	if (node.empty())
		return res;
	priority_queue<Edge*, vector<Edge*>, cmp> less_edge;
	UnionFind uf(node);
	for (auto &e : graph->edges) {
		less_edge.push(e);
	}
	Edge *cur_e = nullptr;
	while (!less_edge.empty()) {
		cur_e = less_edge.top();
		less_edge.pop();
		if (!uf.isSameSet(cur_e->from, cur_e->to)) {
			res.push_back(cur_e);
			uf.Union(cur_e->from, cur_e->to);
		}
	}
	return res;
}

int main() {
	vector<vector<int>> v{ { 1,2,3 },{ 2,3,4 },{ 2,4,1 },{ 3,4,2 },
						   { 2,1,3 },{ 3,2,4 },{ 4,2,1 },{ 4,3,2 } };
	Graph *graph = GraphGenetator(v);
	auto nodes = graph->nodes;
	for (auto i : nodes) {
		cout << i.second->data << "的入度" << i.second->in << " ";
	}
	cout << endl;
	vector<Edge*> resK = KruTree(graph);
	vector<Edge*> resP = PrimTree(graph);
	for_each(resK.begin(), resK.end(), [](Edge* &n) {cout << n->w; });
	cout << endl;

	for_each(resP.begin(), resP.end(), [](Edge* &n) {cout << n->w; });
	cout << endl;
	for (auto i : nodes) {
		cout << i.second->data << "的入度" << i.second->in << " ";
	}
	cout << endl;

	system("pause");
	return 0;

}