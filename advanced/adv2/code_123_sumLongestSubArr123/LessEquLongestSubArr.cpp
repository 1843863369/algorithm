/*
ţ�ͽ��װ�ڶ��ڵ�3��:�����������Ϊ��������0�����ۼӺ�С�ڵ���aim����������鳤��
�������i������£������ۼӳ�����С���ۼӺ� ���ұ߽磬�ֱ������������¼��
֮�����ʹ�û������ڣ���R�Ƿ���Լ������ƣ���ǰ�ͼ�����С�ۼӺ��Ƿ�ϸ��Լ��������Ƶ��ĸ�λ�ã��ұ߽磩��

@2018/1/12

*/

#include "SubFunctions.h"

using namespace std;

void getTwoVec(vector<int> &v, vector<int> &sum_right_min, vector<int> &index_right_min) {
	int len = v.size();
	if (len == 0 || sum_right_min.size()==0 || index_right_min.size()==0) {
		//��������������������ͬ��С�Ҳ�Ϊ��
		return;
	}
	
	sum_right_min[len - 1] = v[len - 1];
	index_right_min[len - 1] = len - 1;
	for (int i = len - 2; i >= 0; --i) {//��������
		if (sum_right_min[i + 1] <= 0) {//����������Ҳ���С��С�ڵ���0�����Լ������ҵ��ӣ�����ֻ������ǰֵ����
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
			// ��0��ʼ�����������С�ۼӺʹ���aim������
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

