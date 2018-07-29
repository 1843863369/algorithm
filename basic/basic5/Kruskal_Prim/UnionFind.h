#pragma once
#ifndef U_F_H
#define U_F_H

#include "GraphGenerator.h"
#include <algorithm>

using namespace std;


class UnionFind {
	map<Node*, Node*> parents;
	map<Node*, int> rank;
public:
	UnionFind() = default;
	UnionFind(vector<Node*> &v) {
		for_each(v.begin(), v.end(), [&](Node* &n) {
			this->rank.insert({ n,1 }); this->parents.insert({ n,n }); });
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

#endif