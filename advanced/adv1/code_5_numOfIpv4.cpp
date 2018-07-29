/*(
牛客算法进阶班第一课第五题，经典递归，给定一个字符串，和一种组合规则，问共有几种情况
两个变量：i parts，i表示第i个，parts表示从i开始，已经有了几部分，且前面的都是合法的；

第五题：给定字符串，问有几种ipv4
@2018/1/9
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//递归解法
int curNumIpv4(string &s, int i, int parts) {//从i开始，不算i
	int len = s.size();
	if (i > len || parts > 4)//i位不算在内，所以i可取到最后一位加一，即i=len
		return 0;
	if (i == len) {
		return parts == 4 ? 1 : 0;
	}
	int result = 0;
	//cout << i << ".";
	result += curNumIpv4(s, i + 1, parts + 1);//i位单独成一个part，不管i为几都可以
	if ((s[i]-'0') == 0) {//如果i为0，不可跟后一位组合：123.01.1不合法
		return result;
	}
	//cout << i << i + 1 << ".";
	result += curNumIpv4(s, i + 2, parts + 1);//i不为0，可以跟后一位组合
	if (i + 2 < len) {
		int sum = (s[i] - '0') * 100 + (s[i + 1] - '0') * 10 + (s[i + 2]);
		if (sum <= 256) {
			//cout << i <<i+1 << i + 2 << endl;
			result += curNumIpv4(s, i + 3, parts + 1);
		}
	}
	return result;
}

int noCurNumIpv4(string &s) {
	int len = s.size();
	if (s.size() < 4 || s.size() > 12) {
		return 0;
	}	
	vector<vector<int>> c(len + 3, vector<int>(5, 0));
	c[len][4] = 1;
	for (int parts = 3; parts >= 0; --parts) {
		for (int i = min(len - 1,parts*3); i >= parts; --i) {
		//for (int i = len - 1; i >= parts; --i) {
			c[i][parts] += c[i + 1][parts + 1];
			if (s[i] - '0' != 0) {
				c[i][parts] += c[i + 2][parts+1];
				if (i + 2 < len) {
					int sum = (s[i] - '0') * 100 + (s[i + 1] - '0') * 10 + (s[i + 2]-'0');
					if (sum <= 256) {
						cout << sum << endl;
						c[i][parts] += c[i + 3][parts+1];
					}
				}
			}

		}
	}
	for (auto &row : c) {
		for (auto &e : row) {
			cout << e << " ";
		}
		cout << endl;
	}
	return c[0][0];
	

}

int main() {
	string numbers("111111211111");
	int n = noCurNumIpv4(numbers);
	cout << n << endl;
	system("pause");
	return 0;
}