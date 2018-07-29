/*
牛客进阶班第二节第1题：整数数组，求累加和为aim的最大子数组长度
使用窗口移动，过大L右移，过小R右移，记录所有符合的结果
@2018/1/9
*/

#include "SubFunctions.h"
#include <set>


using namespace std;

Results PositiveLongestArr(vector<int> &arr, int aim) {
	int len = arr.size();
	if (len == 0||aim == 0)
		return Results(0,0,0);
	int L = 0, R = 0;
	int sum = arr[0];
	int result = 0;
	int fL = 0, fR = 0;//保存结果的左右端点

	while (R < len) {
		if (sum < aim) {
			++R;
			if (R == len)
				break;
			sum += arr[R];
		}
		else if (sum>aim) {
			sum -= arr[L++];
			R = max(L, R);
		}
		else {
			if (result < R - L + 1) {
				result = R - L + 1;
				fR = R;
				fL = L;
			}
			//result = max(result, R - L + 1);
			sum -= arr[L++];
			R = max(L, R);
		}
	}
	Results results(result, fL, fR);
	return results;
}



