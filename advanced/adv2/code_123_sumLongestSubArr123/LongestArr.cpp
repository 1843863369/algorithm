/*
牛客进阶班第二节第2题:数组的数可能为正、负、0，求累加和为aim的最大子数组长度
在1的基础上使用map，key：和，value:和为key的最早index，查看sum-aim是否在map
如果在，记录结果，对每个i结尾的子数组都遍历

@2018/1/9

*/

#include "SubFunctions.h"

#include <map>

using namespace std;

typedef std::tuple<int, int, int> Results;

Results LongestSubArr(vector<int> &v, int aim) {
	int R = 0;
	int fL = 0, fR = 0;//保存结果的左右端点
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



