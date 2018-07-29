/*
图生成器
@2018/1/30
*/

#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;
 
class Edge;

struct Node {
	Node() = default;
	Node(const int i):data(i),in(0),out(0){}
	int data;
	int in;
	int out;
	list<Edge*> edges;
	list<Node*> neighbors;
};

class Edge {
public:
	Edge() = default;
	Edge(const int i, Node* f, Node* t) :w(i), from(f), to(t) {}
	Node* from;
	Node* to;
	int w;
};

struct Graph {
	map<int, Node*> nodes;
	set<Edge*> edges;

};
//给定的数据是二维数组，每一行：from，to，weight
Graph* GraphGenetator(vector<vector<int>> &v) {
	Graph* graph = new Graph();
	Node *from_tmp;
	Node *to_tmp;
	int from;
	int to;
	int weight;
	decltype(graph->nodes.insert({ from,new Node(0) })) insert_from;
	decltype(graph->edges.insert(new Edge(weight, from_tmp, to_tmp))) insert_edge;
	auto insert_to = insert_from;
	for (auto &i : v) {
		from = i[0];
		to = i[1];
		weight = i[2];
		insert_from = graph->nodes.insert({ from,new Node(from) });
		insert_to = graph->nodes.insert({ to,new Node(to) });
		//first：pair，second：bool,  first.first: from/to的值，first.second:Node*
		from_tmp = insert_from.first->second;
		to_tmp = insert_to.first->second;
		insert_edge = graph->edges.insert(new Edge(weight, from_tmp, to_tmp));
		++from_tmp->out;
		++to_tmp->in;
		from_tmp->edges.push_back(*insert_edge.first);
		from_tmp->neighbors.push_back(to_tmp);
	}
	return graph;
}

int main() {
	vector<vector<int>> v{ {1,2,3},{2,3,4},{2,4,1},{3,4,2} };
	Graph *graph = GraphGenetator(v);
	auto nodes = graph->nodes;
	for (auto i : nodes) {
		cout << i.first << " ";
	}
	cout << endl;
	auto nei = nodes[2]->neighbors;
	for (auto i : nei) {
		cout << i->data << " ";
	}

	system("pause");
	return 0;
}