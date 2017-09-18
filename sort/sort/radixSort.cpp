#include "sort.h"


int getNumberPos(int num, int t);

/*
 *	radixSort 的大概思路是：
 *	-	先按待排元素的个位数的大小进行排序，再按十位数的大小进行排序，以此类推
 *  -	由于一个数字的某个位只可能是0到9之间元素，所以可以利用计数排序的方法（设置10个桶），大大加快排序速度
 *  -   由于数位越高，对整个数字大小的影响越大，所以，这样在排完序后，序列显然整体有序
 *  -
**/

void radixSort(int a[],int n) {
	vector<vector<int> > iivec(10);
	//std::cout << iivec[0].size() << "\n";
	for (int t = 1; t == 1 || t % 10 == 0; t *= 10) {
		//将元素按照一定规则放入桶中
		for (int i = 0;i < n;i++)
			iivec[getNumberPos(a[i], t)].push_back(a[i]);

		int k = 0,size = 0;		//从桶中取出元素
		for (auto &ivec : iivec) {
			for (auto i : ivec)
				a[k++] = i;
			ivec.clear();
		}
	}
}

int getNumberPos(int num, int t) {
	return (num / t) % 10;
}