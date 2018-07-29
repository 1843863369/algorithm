 /*
ţ���㷨�����࣬ͼ�ĳ����㷨��Kruskal�㷨��Prim�㷨,������ͼ������ͼ����С����ͼ��
K���ò��鼯�����б���С���ѣ�С���ѵ����ߣ�from��to��һ��set��Ҫ������ϲ����������Ǽ���֮��ĺϲ�
P������һ�㿪ʼ�����ٱ���С���ѣ���С�ѵ����ߣ����to��set�У��������������set���ٽ�to���ڽڵ����
@2018/1/31
*/

#include "GraphGenerator.h"
#include "UnionFind.h"
#include <queue>

struct cmp {
	bool operator()(const Edge* a, const Edge* b) {
		return a->w > b->w;//��С�ѣ����ں�
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
				if (filter.find(cur_edge->to) == filter.end()) {//to�ڵ㲻��set�У��˱߼�����,to����filter
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
		cout << i.second->data << "�����" << i.second->in << " ";
	}
	cout << endl;
	vector<Edge*> resK = KruTree(graph);
	vector<Edge*> resP = PrimTree(graph);
	for_each(resK.begin(), resK.end(), [](Edge* &n) {cout << n->w; });
	cout << endl;

	for_each(resP.begin(), resP.end(), [](Edge* &n) {cout << n->w; });
	cout << endl;
	for (auto i : nodes) {
		cout << i.second->data << "�����" << i.second->in << " ";
	}
	cout << endl;

	system("pause");
	return 0;

}