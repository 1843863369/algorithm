/*
牛客进阶班第二节第3题:数组的数可能为正、负、0，求累加和小于等于aim的最大子数组长度
必须包含i的情况下，向右累加出的最小的累加和 和右边界，分别用两个数组记录。
之后继续使用滑动窗口，看R是否可以继续右移（当前和加上最小累加和是否合格）以及可以右移到哪个位置（右边界）。

@2018/1/12

*/

#include "SubFunctions.h"

using namespace std;

void getTwoVec(vector<int> &v, vector<int> &sum_right_min, vector<int> &index_right_min) {
	int len = v.size();
	if (len == 0 || sum_right_min.size()==0 || index_right_min.size()==0) {
		//传入的三个数组必须有相同大小且不为空
		return;
	}
	
	sum_right_min[len - 1] = v[len - 1];
	index_right_min[len - 1] = len - 1;
	for (int i = len - 2; i >= 0; --i) {//从右向左
		if (sum_right_min[i + 1] <= 0) {//两种情况，右侧最小和小于等于0，可以继续向右叠加，否则只包含当前值本身
			sum_right_min[i] = v[i] + sum_right_min[i + 1];
			index_right_min[i] = index_right_min[i + 1];
		}
		else {
			sum_right_min[i] = v[i];
			index_right_min[i] = i;
		}
	}
}

Results LessEquLongestSubArr(vector<int> &v,int aim) {
	int len = v.size();
	if (len == 0) {
		//return Results(0, -1, -1);
		return Results(0,-1,-1);
	}
	vector<int> sum_r_min(len);
	vector<int> index_r_min(len);
	//cout << index_r_min.size();
	getTwoVec(v, sum_r_min, index_r_min);
	//printVector(sum_r_min);
	//printVector(index_r_min);
	int R = 0;
	int temp = 0;
	int max_len = 0;
	int result_sum = 0 ;
	int fL = -1, fR = -1;
	
	for (int i = 0; i < len; ++i) {
		if (sum_r_min[i] > aim) {
			// 从0开始，如果向右最小累加和大于aim，右移
			continue;
		}
		temp = sum_r_min[i];
		R = max(R, index_r_min[i]);
		while (R < len - 1 && sum_r_min[R + 1] + temp <= aim) {
			temp = sum_r_min[R + 1] + temp;
			R = index_r_min[R + 1];
		}
		if (R - i + 1>max_len) {
			fL = i;
			fR = R;
			max_len = R - i + 1;
			result_sum = temp;
		}
	}
	return Results(result_sum, fL, fR);
}

