/*
牛客算法初级，图的遍历：BFS
@2018/1/30
*/
#include "GraphGenerator.h"
#include <queue>
#include <stack>

void BFS(Node *head) {
	set<Node*> filter;
	queue<Node*> buf;
	Node *tmp = head;
	buf.push(head);
	filter.insert(head);
	while (!buf.empty()) {
		tmp = buf.front();
		for (auto i : tmp->neighbors) {
			if (filter.find(i) == filter.end()) {
				filter.insert(i);
				buf.push(i);
			}
		}
		cout << tmp->data << " ";
		buf.pop();
	}
}

void DFS(Node *head) {
	stack<Node*> buf;
	set<Node*> filter;
	buf.push(head);
	while (!buf.empty()) {
		head = buf.top();
		buf.pop();
		cout << head->data << " ";
		for (auto &i : head->neighbors) {
			if (filter.insert(i).second) {
				buf.push(i);
			}
		}
		
	}
}


int main() {
	vector<vector<int>> v{ { 1,2,3 },{ 2,4,4 },{ 2,5,2 },{4,8,1},{ 5,8,1 },{1,3,1},{3,6,7},{3,7,1},{6,7,1} };
	Graph *graph = GraphGenetator(v);

	for (auto &i : graph->edges) {
		cout << i->w << " ";
	}
	cout << endl;
	for (auto &i : graph->nodes) {
		cout << i.second->in << " ";
	}
	cout << endl;
	DFS(graph->nodes[1]);
	

	system("pause");
	return 0;
}