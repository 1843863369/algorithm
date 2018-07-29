#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> vv;

vv Lcs(string &x, string& y) {
	size_t m = x.size();
	size_t n = y.size();
	vv c(m + 1, vector<int>(n + 1, 0));
	//cout << c[0][0] << " ";
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (x[i] == y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				//cout << x[i] << " ";
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
			}
			else {
				c[i][j] = c[i][j - 1];
			}
		}
	}
	//cout << c[0][0] << " ";
	return c;
}

void ConstructLcs(vv& c,string& x,int i,int j) {
	if (i != 0 && j != 0) {
		if (c[i-1][j] >= c[i][j - 1]&& c[i][j] == c[i - 1][j]) {
			ConstructLcs(c, x, i-1, j);
		}
		else if (c[i][j] == c[i][j-1]) {
			ConstructLcs(c, x, i, j-1);
		}
		else if (c[i][j] == c[i - 1][j - 1] + 1) {

			ConstructLcs(c, x, i - 1, j - 1);
			cout << x[i - 1] << " ";
		}
	}
}
int main() {
	string x = "abcbdab";
	string y("bdcaba");
	vv c = Lcs(x, y);
	for (auto &i : c) {
		for (auto & j : i)
			cout << j << " ";
		cout << endl;
	}
	cout << "LCSµÄ³¤¶È: " << endl;
	cout << c[x.size()][y.size()] << endl;
	cout << "LCS: " << endl;
	ConstructLcs(c, x, x.size(), y.size());
	system("pause");
}