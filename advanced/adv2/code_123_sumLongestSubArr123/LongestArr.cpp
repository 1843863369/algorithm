/*
ţ�ͽ��װ�ڶ��ڵ�2��:�����������Ϊ��������0�����ۼӺ�Ϊaim����������鳤��
��1�Ļ�����ʹ��map��key���ͣ�value:��Ϊkey������index���鿴sum-aim�Ƿ���map
����ڣ���¼�������ÿ��i��β�������鶼����

@2018/1/9

*/

#include "SubFunctions.h"

#include <map>

using namespace std;

typedef std::tuple<int, int, int> Results;

Results LongestSubArr(vector<int> &v, int aim) {
	int R = 0;
	int fL = 0, fR = 0;//�����������Ҷ˵�
	int sum = 0;
	int len = v.size();
	int result = 0;
	if (len == 0)
		return Results(0, 0, 0);
	map<int, int> records{ { 0,-1 } };
	while (R < len) {
		sum += v[R];
		if (records.find(sum) == records.end()) {
			records[sum] = R;
		}
		auto L = records.find(sum - aim);
		if (L != records.end()) {
			//result = max(result, R - (L->second));
			if (result < R - (L->second)) {
				result = R - (L->second);
				fR = R;
				fL = L->second + 1;
			}
		}
		++R;
	}
	Results results(result, fL, fR);
	return results;
}



