/*
牛客进阶三四课作业第四题：BFS
https://www.nowcoder.com/questionTerminal/e3fc4f8094964a589735d640424b6a47
@2018/3/6
*/

#include<iostream>
#include<set>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<memory>

using namespace std;

struct Node {
	int x;
	int y;
	int step;
	int key;
	Node(int i,int j,int s,int k):x(i),y(j),step(s),key(k){}
};

inline int nBit(int key, int n) {
	return (key >> n) & 1;
}

//int bfsMigong(vector<vector<char>> &v,int xstart,int ystart) {
//	queue<shared_ptr<Node>> que;
//	que.push(make_shared<Node>(xstart, ystart, 0, 0));
//	vector<vector<vector<int>>> filter(105, vector<vector<int>>(105, vector<int>(1030)));
//	filter[xstart][ystart][0] = 1;
//	int x, y, s;
//	while (!que.empty()) {
//		shared_ptr<Node> node = que.front();
//		que.pop();
//		x = node->x;
//		y = node->y;
//		s = node->step;
//		char cur = v[x][y];
//		if (cur == '3') return node->step;
//		if (cur >= 'a'&&cur <= 'z') {
//			node->key |= (1<<(cur - 'a'));
//		}
//
//		vector<vector<int>> nex = { { x - 1,y },{ x,y - 1 },{ x + 1,y },{ x,y + 1 } };
//		char n_cur;
//		for (auto i : nex) {
//			if ((i[0] >= 0 && i[0] < v.size()) && (i[1] >= 0 && i[1] < v[0].size())) {
//				n_cur = v[i[0]][i[1]];
//				if (n_cur == '0' || (n_cur >= 'A'&&n_cur <= 'Z' && (nBit(node->key,n_cur-'A')==0))) {
//					continue;
//				}		
//				if (!filter[i[0]][i[1]][node->key]) {
//					shared_ptr<Node> next_node = make_shared<Node>(i[0], i[1], s + 1, node->key);
//					que.push(next_node); 
//					filter[i[0]][i[1]][node->key] = 1;
//				}
//			}
//
//		}
//	}
//	return 0;
//}
vector<vector<vector<int>>> filter(105, vector<vector<int>>(105, vector<int>(1030)));
vector<vector<int>> nex(4,vector<int>(4,0));
char Map2[105][105];
int m;
int n;
int bfsMigong(int xstart, int ystart) {
	queue<Node> que;
	que.push(Node(xstart, ystart, 0, 0));
	filter[xstart][ystart][0] = 1;
	int x, y, s,k;
	while (!que.empty()) {
		Node node = que.front();
		que.pop();
		x = node.x;
		y = node.y;
		s = node.step;
		char cur = Map2[x][y];
		if (cur == '3') return node.step;
		if (cur >= 'a'&&cur <= 'z') {
			node.key |= (1 << (cur - 'a'));
		}
		k = node.key;
		nex = { { x - 1,y },{ x,y - 1 },{ x + 1,y },{ x,y + 1 } };
		char n_cur;
		for (auto i : nex) {
			if ((i[0] >= 0 && i[0] < m) && (i[1] >= 0 && i[1] < n)) {
				n_cur = Map2[i[0]][i[1]];
				if (n_cur == '0' || (n_cur >= 'A'&&n_cur <= 'Z' && (nBit(k, n_cur - 'A') == 0))) {
					continue;
				}
				if (!filter[i[0]][i[1]][k]) {
					que.push(Node(i[0], i[1], s + 1, k));
					filter[i[0]][i[1]][k] = 1;
				}
			}

		}
	}
	return 0;
}
vector<vector<char>> InPut() {
	int m, n;
	cin >> m >> n;
	vector<vector<char>> Map;
	vector<char> rows(n);
	while (m-- > 0) {
		for (int i = 0; i < n; ++i) {
			cin >> rows[i];
		}
		Map.push_back(rows);
	}
	
	return Map;
}
void printMap(vector<vector<char>> &v) {
	for (auto i : v) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
}

int main() {
	//vector<vector<char>> m = InPut();
	
	//vector<vector<char>> Map1 = { {'0','2','1','1','1'},{'0','1','a','0','A'},
	//{'0','1','0','0','3'}, {'0','1','0','0','1'},{'0','1','1','1','1'} };
	string lines;
	int x, y;
	cin >> m >> n;
	
	/*for (int i = 0; i < m; ++i) {
		cin >> lines;
		for (int j = 0; j < n; ++j) {
			Map2[i][j] = lines[j];
			if (lines[j] == '2') {
				x = i;
				y = j;
			}
		}
	}*/
	for (int i = 0; i < m; ++i) {
		cin >> lines;
		strcpy_s(Map2[i], lines.c_str());

	}
	int flag = 0;
	for (int i = 0; i<m; ++i) {
		if (flag == 1) break;
		for (int j = 0; j < n; ++j) {
			if (Map2[i][j] == '2') {
				x = i;
				y = j;
				flag = 1;
				break;
			}
		}
	}
	//printMap(Map1);
	//printMap(Map2);
	//cout << m << " " << n << endl;
	//getline(cin, lines);
	//cout << lines << endl;

	//getline(cin, lines);
	//cout << lines << endl;
	//cout << Map[0][0] <<" "<< Map[0][2] << endl;
	cout << bfsMigong(x, y) << endl;


	//cout << bfsMigong(Map1, 0, 1) << endl;
	system("pause");
	return 0;
}