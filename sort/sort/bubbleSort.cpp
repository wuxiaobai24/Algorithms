#include "sort.h"



void bubbleSort(int a[],int n){
	
	bool sorted = false;			//增加flag，可以减少不必要的迭代。

	for (int i = 0; i < n && !sorted; ++i) {
		sorted = true;				//每次先假设当前数组已经排好序了
		for (int j = i + 1; j < n; ++j)
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
				sorted = false;		//只有发现存在逆序对的时候，将sorted 设置为false
									//如果某次迭代时，没有交换元素，
									//这表示当前数组已经排好序了，注意外循环结束条件
			}
	}
}