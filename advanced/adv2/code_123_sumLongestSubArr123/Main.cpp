#include "SubFunctions.h"

using namespace std;


void runPosEqu() {
	Results results(0, 0, 0);
	vector<int> v = generatePosVector();
	cout << "���飺" << endl;
	printVector(v);
	int aim = 13;
	results = PositiveLongestArr(v, aim);
	printf("�ۼӺ�Ϊ%d����������鳤��Ϊ��%d����߽磺%d���ұ߽磺%d\n",
		aim, get<0>(results), get<1>(results), get<2>(results));

	cout << "=============================================================" << endl;
}

void runEqu() {
	vector<int> v = { 1,1,4,-1,1,1,-1,-2,1 };
	int aim = 5;
	Results results = LongestSubArr(v, aim);
	cout << "���飺" << endl;
	printVector(v);
	printf("�ۼӺ�Ϊ %d ����������鳤��Ϊ��%d ����߽磺%d ���ұ߽磺%d\n",
		aim, get<0>(results), get<1>(results), get<2>(results));
	cout << "=============================================================" << endl;
	vector<int> v1 = { 1,1,-1,1,1,1,-1,-1,-1,-1,1,1 };
	int aim1 = 0;
	Results results1 = LongestSubArr(v1, aim1);
	cout << "���飺" << endl;
	printVector(v1);
	printf("�ۼӺ�Ϊ %d ����������鳤��Ϊ��%d ����߽磺%d ���ұ߽磺%d\n",
		aim1, get<0>(results1), get<1>(results1), get<2>(results1));
	cout << "=============================================================" << endl;
}

void runLess() {
	vector<int> v = generateVector();
	cout << "���飺 " << endl;
	printVector(v);
	int aim = -16;
	Results r = LessEquLongestSubArr(v, aim);
	printf("�ۼӺ�С�ڵ��� %d �������������߽磺%d ���ұ߽磺%d����Ϊ��%d\n",
		aim, get<1>(r), get<2>(r), get<0>(r));
	cout << "=============================================================" << endl;

	vector<int> v1 = generateVector();
	cout << "���飺 " << endl;
	printVector(v1);
	int aim1 = -12;
	Results r1 = LessEquLongestSubArr(v1, aim1);
	printf("�ۼӺ�С�ڵ��� %d �������������߽磺%d ���ұ߽磺%d����Ϊ��%d\n",
		aim1, get<1>(r1), get<2>(r1), get<0>(r1));
	cout << "=============================================================" << endl;

	vector<int> v2 = generatePosVector();
	cout << "���飺 " << endl;
	printVector(v2);
	int aim2 = -1;
	Results r2 = LessEquLongestSubArr(v2, aim2);
	printf("�ۼӺ�С�ڵ��� %d �������������߽磺%d ���ұ߽磺%d����Ϊ��%d\n",
		aim2, get<1>(r2), get<2>(r2), get<0>(r2));
	cout << "=============================================================" << endl;

}

int main() {
	runPosEqu();
	runEqu();
	runLess();
	
	system("pause");
	return 0;
}
