#include "sort.h"

//mergeSort
void merge(int a[], int first, int mid, int last);
void mergesort(int a[], int first, int last);

/*
 *	mergeSort ��qucikSortһ������ʹ�÷��η�
 *  mergeSort��ʱ�临�Ӷȴ�໨��"��",��"��"ֻ��Ҫ����ʱ�伴��
 *  ��Ҫ˼·��
 *		- ���Ƚ���������ֱ�ӷֳ����룬Ȼ��ݹ����mergeSort.
 *		- ��mergeSort�ݹ鵽����������ֻ��һ��Ԫ��ʱ����Ȼ��ʱ�����Ѿ����򣬿��Խ����ݹ�
 *		- ��ʱ��Ҫ���ǵľ��ǽ�������������н���merge��һ����������С�
 *		- ���������Ѿ�������Ӷ�һ���������н����������˽������������кϲ���һ���������С�
**/

void mergeSort(int a[],int n) {
	//ͳһ�ӿ�
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
	int *p = new int[size];					//mergeSort����ԭ��������Ҫ�µĿռ�
	
	while (k < size)
		if (j >	last ||						//��j > last ʱ����Ϊ��ѭ���������Եó�k < size,��ʱ i <= mid
				(i <= mid && a[i] < a[j]))	
			p[k++] = a[i++];
		else
			p[k++] = a[j++];

	for (k = 0, i = first; i <= last; i++, k++)
		a[i] = p[k];						//���źõ����зŻ�ԭ�����С�
	delete[] p;
}