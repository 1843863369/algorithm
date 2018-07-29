/*
牛客算法初级班第一课，堆排序
@2018/1/17
*/

#include "Sorts.h"

using namespace std;

void heapify(vector<int> &v, int index, int heap_size) {
	if (heap_size <= 1) {
		return;
	}
	int left_child = index * 2 + 1;
	int largest = index;
	while (left_child <= heap_size - 1) {
		largest = (v[left_child] > v[index]) ? left_child : index;
		largest = (left_child + 1 <= heap_size - 1 && v[left_child + 1] > v[largest]) ?
			left_child + 1 : largest;//右孩子
		if (largest == index) {//largest等于当前index时，直接返回
			break;
		}
		swap(v[largest], v[index]);
		index = largest;
		left_child = index * 2 + 1;
	}
}

void heapInsert(vector<int> &v,int value) {
	int value_index = v.size();
	v.push_back(value);
	int parent = (value_index - 1) >> 1;//value的index为len
	while (parent >= 0 && v[parent] < value) {
		swap(v[parent], v[value_index]);
		value_index = parent;
		parent = (value_index - 1) >> 1;
	}

}

void heapDelet(vector<int> &v, int index) {
	int heap_size = v.size();
	if (index >= heap_size) {
		return;
	}
	swap(v[heap_size - 1], v[index]);
	--heap_size;
	heapify(v, index, heap_size);
}



void buildHeap(vector<int> &v) {
	int len = v.size();
	for (int i = len / 2 - 1; i >= 0; --i) {
		heapify(v, i,len);
	}
}

void HeapSort(vector<int> &v) {
	int heap_size = v.size();
	buildHeap(v);
	while (heap_size > 1) {
		swap(v[0], v[heap_size - 1]);
		--heap_size;
		heapify(v, 0, heap_size);
	}

}

