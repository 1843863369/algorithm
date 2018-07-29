/*
牛客算法进阶第三课第六题：统计和生成所以不同的二叉树
动态规划，对每个i，结果等于左侧的结果×右侧的结果，再累加
@2018/3/5
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int CurBTree(int n) {
	if (n <= 1) {
		return 1;
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		res += CurBTree(i - 1)*CurBTree(n - i); //只关心节点个数
	}
	return res; 
}

int dpBTree(int n) {
	if (n <= 1)
		return 1;
	vector<int> dp(n + 1, 0);
	dp[0] = 1;
	dp[1] = 1;
	for (int j = 2; j <= n; j++) {
		for (int i = 1; i <= j; ++i) {
			dp[j] += dp[i - 1] * dp[j - i];
		}
	}
	return dp[n];
}

struct Node {
	Node() = default;
	Node(const int i):data(i),left(nullptr),right(nullptr){}
	int data;
	Node *left;
	Node *right;

};

Node* copyTree(Node* head) {
	if (head == nullptr)
		return nullptr;
	Node* res = new Node(head->data);
	res->left = copyTree(head->left);
	res->right = copyTree(head->right);
	return res;
}

vector<Node*> generateTree(int l, int r) {
	vector<Node*> res;
	if (l > r) {
		res.push_back(nullptr);
		return res;
	}
	if (l == r) {
		res.push_back(new Node(l));
		return res;
	}
	vector<Node*> le;
	vector<Node*> ri;
	for (int i = l; i <= r; ++i) {
		le = generateTree(l, i - 1);
		ri = generateTree(i + 1, r);
		for (auto nl : le) {
			for (auto nr : ri) {
				Node* node = new Node(i);
				node->left = copyTree(nl);
				node->right = copyTree(nr);
				res.push_back(node);
			}
		}
	}
	return res;
}

//vector<Node*> Trees(int n) {
//	vector<Node*> res;
//	for (int i = 1; i <= n; ++i) {
//		res.push_back(generateTree(i,n));
//	}
//	
//	return res;
//}
void InPrint(Node* root) {
	cout << "InPrint:" << endl;
	stack<Node*> s;
	while (!s.empty() || root != nullptr) {
		if (root != nullptr) {
			s.push(root);
			root = root->left;
		}
		else {
			root = s.top();
			cout << root->data << " ";
			s.pop();
			root = root->right;
		}
	}
	cout << endl;
}
void printPreTree(Node *head) {
	stack<Node*> s;
	s.push(head);
	while (!s.empty()) {
		head = s.top();
		s.pop();
		cout << head->data << " ";
		if (head->right != nullptr) {
			s.push(head->right);
		}
		if (head->left != nullptr) {
			s.push(head->left);
		}
	}
	cout << endl;
}
int main() {
	int n = 3;
	/*while (n-- > 0) {
		cout << CurBTree(n) << " " << dpBTree(n) << endl;
	}*/
	cout << dpBTree(n) << endl;

	Node *head = new Node(1);
	head->left = new Node(2);
	head->right = new Node(3);
	head->left->left = new Node(4);
	head->left->right = new Node(5);
	head->right->left = new Node(6);

	//Node *headc = copyTree(head);
	//head->left->data = 9;
	//printPreTree(head);
	//printInTree(headc);
	vector<Node*> nodes = generateTree(1,n);
	cout << nodes.size() << endl;
	for (auto n : nodes) {
		//InPrint(n);
		printPreTree(n);
		//cout << n->data << " ";
	}
	system("pause");
	return 0;
}