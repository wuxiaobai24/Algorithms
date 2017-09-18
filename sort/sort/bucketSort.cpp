#include "sort.h"

const int bucketNumber = 100;

void bucketSort(int a[], int n) {
	vector<int> *bucket = new vector<int>[bucketNumber];
	int t = maxRandomNumber / bucketNumber;
	for (int i = 0; i < n; i++) {
		bucket[a[i] / t].push_back(a[i]);
	}
	int h = 0;
	for (int i = 0; i < bucketNumber; i++) {
		//insertionSort
		int size = bucket[i].size();
		for (int j = 1; j < size; j++) {
			int key = bucket[i][j];
			int k;
			for (k = j - 1; k > 0 && bucket[i][k] > key; k--)
				bucket[i][k + 1] = bucket[i][k];
			bucket[i][k+1] = key;
		}
		for (int j = size - 1; j >= 0; --j)
			a[h++] = bucket[i][j];
	}
	delete[] bucket;
}


void bucketSort(vector<int> &vec) {
	
	vector<vector<int> > bucket(bucketNumber);
	int t = maxRandomNumber / bucketNumber;
	for (auto i : vec) {
		bucket[i / t].push_back(i);
	}
	int k = 0;
	for (auto &v : bucket) {
		//quickSort(v);
		//insertionSort(v);
		for(int i = v.size() -1;i>=0;i--)
			vec[k++] = v[i];
	}
}