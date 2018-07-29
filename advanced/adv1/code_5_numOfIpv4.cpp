/*(
ţ���㷨���װ��һ�ε����⣬����ݹ飬����һ���ַ�������һ����Ϲ����ʹ��м������
����������i parts��i��ʾ��i����parts��ʾ��i��ʼ���Ѿ����˼����֣���ǰ��Ķ��ǺϷ��ģ�

�����⣺�����ַ��������м���ipv4
@2018/1/9
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//�ݹ�ⷨ
int curNumIpv4(string &s, int i, int parts) {//��i��ʼ������i
	int len = s.size();
	if (i > len || parts > 4)//iλ�������ڣ�����i��ȡ�����һλ��һ����i=len
		return 0;
	if (i == len) {
		return parts == 4 ? 1 : 0;
	}
	int result = 0;
	//cout << i << ".";
	result += curNumIpv4(s, i + 1, parts + 1);//iλ������һ��part������iΪ��������
	if ((s[i]-'0') == 0) {//���iΪ0�����ɸ���һλ��ϣ�123.01.1���Ϸ�
		return result;
	}
	//cout << i << i + 1 << ".";
	result += curNumIpv4(s, i + 2, parts + 1);//i��Ϊ0�����Ը���һλ���
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