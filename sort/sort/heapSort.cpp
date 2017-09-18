#include "sort.h"

#define parent(i) (i/2 - 1)
#define leftChild(i) ((i+1)*2 - 1)
#define rightChild(i) ((i+1)*2)

//¶Ñµ÷Õû
void maxHeapify(int a[],int i, int heapSize) {
	int left = leftChild(i);
	int right = rightChild(i);
	int largest = i;
	if (left < heapSize && a[i] < a[left])
		largest = left;
	if (right < heapSize && a[largest] < a[right])
		largest = right;
	if (largest != i) {
		swap(a[i], a[largest]);
		maxHeapify(a, largest,heapSize);
	}
}
//½¨¶Ñ
void buildMaxHeap(int a[],int n) {
	int heapSize = n;
	for (int i =  n / 2 - 1; i >= 0; i--) {
		maxHeapify(a, i, heapSize);
	}
}
void heapSort(int a[], int n) {
	buildMaxHeap(a, n);
	int heapSize = n;
	for (int i = n - 1; i > 0; --i) {
		swap(a[i], a[0]);
		heapSize--;
		maxHeapify(a, 0, heapSize);
	}
}