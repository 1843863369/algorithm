/*
牛客进阶第四课第二题：机器人走位，K步后到达P位置的走法有多少种
动态规划：K-1步到P+1和P-1的方法总和，考虑边界
@2018/3/6
*/

#include<iostream>
#include<vector>

using namespace std;

int curRobert(int n, int t, int k, int p) {
	if (n <= 0 || t >= n || k < 0 || p >= n || p < 0 || t < 0) {
		return 0;
	}
	if (k == 0) {
		return p == t ? 1 : 0;
	}
	if (p == n - 1) {
		return curRobert(n, t, k - 1, p - 1);
	}
	else if (p == 0) {
		return curRobert(n, t, k - 1, p + 1);
	}
	else {
		return curRobert(n, t, k - 1, p + 1) + curRobert(n, t, k - 1, p - 1);
	}
}

int dpRobert(int n, int t, int k, int p) {
	if (n <= 0 || t >= n || k < 0 || p >= n || p < 0 || t < 0) {
		return 0;
	}
	vector<vector<int>> dp(k + 1, vector<int>(n, 0));
	dp[0][t] = 1;
	for (int i = 1; i <= k; ++i) {
		dp[i][0] = dp[i - 1][1];
		dp[i][n - 1] = dp[i - 1][n - 2];
		for (int j = 1; j < n - 1; ++j) {
			dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
		}
	}
	return dp[k][p];
}

int main() {
	int n = 10;
	int t = 2;
	int k = 4;
	int p = 0;
	cout << curRobert(n, t, k, p) << endl;
	cout << dpRobert(n, t, k, p) << endl;
	system("pause");
	return 0;
}