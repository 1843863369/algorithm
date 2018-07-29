/*
ţ�ͽ��װ�ڶ��ڵ�1�⣺�������飬���ۼӺ�Ϊaim����������鳤��
ʹ�ô����ƶ�������L���ƣ���СR���ƣ���¼���з��ϵĽ��
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
	int fL = 0, fR = 0;//�����������Ҷ˵�

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



