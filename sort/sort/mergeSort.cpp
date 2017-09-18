#include "sort.h"

//mergeSort
void merge(int a[], int first, int mid, int last);
void mergesort(int a[], int first, int last);

/*
 *	mergeSort 和qucikSort一样都是使用分治法
 *  mergeSort的时间复杂度大多花在"治",而"分"只需要常数时间即可
 *  主要思路：
 *		- 首先将待排序列直接分成两半，然后递归调用mergeSort.
 *		- 到mergeSort递归到，待排序列只有一个元素时，显然这时序列已经有序，可以结束递归
 *		- 这时需要考虑的就是将两个有序的序列进行merge成一个有序的序列。
 *		- 现在我们已经将问题从对一个无序序列进行排序变成了将两个有序序列合并成一个有序序列。
**/

void mergeSort(int a[],int n) {
	//统一接口
	int first = 0;
	int last = n - 1;
	mergesort(a, first, last);
}

void mergesort(int a[], int first, int last) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergesort(a, first, mid);
		mergesort(a, mid + 1, last);
		merge(a, first, mid, last);
	}
}

void merge(int a[], int first, int mid, int last) {
	int i = first, j = mid + 1, k = 0;
	int size = last - first + 1;
	int *p = new int[size];					//mergeSort不是原地排序，需要新的空间
	
	while (k < size)
		if (j >	last ||						//当j > last 时，因为从循环条件可以得出k < size,这时 i <= mid
				(i <= mid && a[i] < a[j]))	
			p[k++] = a[i++];
		else
			p[k++] = a[j++];

	for (k = 0, i = first; i <= last; i++, k++)
		a[i] = p[k];						//将排好的序列放回原数组中。
	delete[] p;
}