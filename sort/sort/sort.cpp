#include "sort.h"
#include <iostream>
#include <ctime>
#include <Windows.h>


using namespace std;
void Sort(int *a,int n,int algorithm) {
	switch (algorithm) {
		case 1:
			bubbleSort(a,n);
			break;
		case 2:
			countSort(a, n);
			break;
		case 3:
			quickSort(a, n);
			break;
		case 4:
			mergeSort(a, n);
			break;
		case 5:
			insertionSort(a, n);
			break;
		case 6:
			selectSort(a, n);
			break;
		case 7:
			shellSort(a, n);
			break;
		case 8:
			radixSort(a, n);
			break;
		case 9:
			bucketSort(a, n);
			break;
		case 10:
			heapSort(a, n);
			break;
		default:
			std::cout << "error\n" << a;
			exit(-1);
	}
}

void swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}


double testSort(int n, int algorithm,int count) {
	//cout << "sort" << endl;
	
	//产生待排数组
	srand((unsigned)time(NULL));
	int *a = new int[n*count];
	for (int i = 0; i < n*count; i++)
		a[i] = rand() % maxRandomNumber;
	//记时
	time_t time1 = clock();
	for(int i = 0;i<count;i++)
		Sort(a + i*n,n,algorithm);
	time_t time2 = clock();

#ifdef SHOWOUT
	for (int i = 0;i < n;i++)
		cout << a[i] << " ";
	cout << endl;
#endif 

	delete[] a;
	double ret = static_cast<double>(time2 - time1)/CLOCKS_PER_SEC * 1000;
	return ret/count;
}