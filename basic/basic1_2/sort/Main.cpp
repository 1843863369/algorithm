#include "Sorts.h"

using namespace std;

int main() {
	int run_time = 10;
	vector<int> vc, vh, vm, vq;
	while (run_time) {
		vc = generateVec();
		vq = vc;
		vm = vc;
		vh = vc;
		//printVec(vc);
		comparator(vc);
		QuickSort(vq);
		MergeSort(vm);
		HeapSort(vh);
		--run_time;
		//printVec(vm);
		cout << "MergeSort: " << (vm == vc ? "right" : "false!!!!!!!") << endl;
		//printVec(vq);
		cout << "QuickSort: " << (vq == vc ? "right" : "false!!!!!!!") << endl;
		//printVec(vh);
		cout << "HeapSort: " << (vh == vc ? "right" : "false!!!!!!!") << endl;
		cout << "=============================" << endl;
	}
	
	system("pause");
}