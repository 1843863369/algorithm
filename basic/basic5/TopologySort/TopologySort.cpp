/*
牛客算法初级班图的常见算法
@2018/1/31
*/
#include "GraphGenerator.h"
#include <queue>

vector<Node*> TopologySort(Graph graph) {
	map<Node*,int> in_of_node;//节点：节点入度，防止排序操作改变原图
	queue<Node*> nodes_in_0;//入度为0的节点
	vector<Node*> res;
	Node *tmp = nullptr;
	if (graph.nodes.empty())
		return res;
	for (auto &i : graph.nodes) {//入度为0的点入队
		tmp = i.second;
		in_of_node.insert({ tmp,i.second->in });
		if (in_of_node[tmp] == 0) {
			nodes_in_0.push(tmp);
		}
	}
	while (!nodes_in_0.empty()) {
		tmp = nodes_in_0.front();
		nodes_in_0.pop();
		res.push_back(tmp);
		for (auto &i : tmp->neighbors) {
			if (--in_of_node[i] == 0) {
				nodes_in_0.push(i);
			}
		}
	}
	return res;
}

int main() {
	vector<vector<int>> v{ { 1,2,3 },{ 2,3,4 },{ 2,4,1 },{ 3,4,2 } };
	Graph *graph = GraphGenetator(v);
	auto nodes = graph->nodes;
	for (auto i : nodes) {
		cout << i.second->data << "的入度" << i.second->in << " ";
	}
	cout << endl;
	vector<Node*> res = TopologySort(*graph);
	for_each(res.begin(), res.end(), [](Node* &n) {cout << n->data; });
	cout << endl;
	for (auto i : nodes) {
		cout << i.second->data << "的入度" << i.second->in << " ";
	}
	cout << endl;

	system("pause");
	return 0;

}