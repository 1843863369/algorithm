/*
牛客算法初级班第四款第九题，三四课作业，找到数组中任意局部最小值的index；
https://www.nowcoder.com/questionTerminal/322eb1da892448f4b18d9b21a6d48c99
@2018/1/29

*/

#include <vector>
#include <iostream>

using namespace std;
//递归
int LessIndex(vector<int> &v,int l,int r) {
	if (r == l|| v[l]<v[l + 1])
		return l;
	if (v[r] < v[r - 1])
		return r;
	int mid = l + ((r - l) >> 1);
	if (v[mid] < v[mid + 1] && v[mid] < v[mid - 1]) {
		return mid;
	}
	if (v[mid] > v[mid - 1]) {
		LessIndex(v, l, mid);
	}
	return LessIndex(v, mid, r);
}
int noCurLessIndex(vector<int> &v) {
	int l = 0;
	int r = v.size() - 1;
	if (r == 0 || v[l] < v[l + 1]) return l;
	if (v[r] < v[r - 1]) return r;
	int mid = -1;
	while (l < r) {
		mid = l + ((r - l) >> 1);
		if (v[mid] < v[mid + 1] && v[mid] < v[mid - 1]) break;
		r = v[mid] > v[mid - 1] ? mid : r;
		l = v[mid] < v[mid - 1] ? mid : l;
	}
	return mid;
}

int getIndex(vector<int> &arr) {
	if (arr.empty()) return -1;
	//return LessIndex(arr, 0, arr.size() - 1);
	return noCurLessIndex(arr);
}

int main() {
	vector<int> v{ 8,7,6,7,8};
	cout << getIndex(v) << endl;
	system("pause");
	return 0;
}