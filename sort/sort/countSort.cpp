#include "sort.h"

/*
 * 计数排序的大概思路是：遍历一遍待排数组，记录每一个数出现的个数，
 * 最后再通过这些记录直接改写待排数组。
 * 计数排序不是比较排序，时间复杂度为O(n),空间复杂度为O(m)，
 *	m为待排数组中数字的最大值和最小值的差值，下面是直接假设最大值为maxRandomNumber,最小值为0
 */

void countSort(int a[], int n)
{
	//int size = abs(maxRandomNumber - min(a) );	//这样可以减少一些空间复杂度
	//int offset = min(a) - 0;
	int *count = new int[maxRandomNumber];		//计数排序是需要限制范围的，而且范围太大时效率也不高
	for (int i = 0; i < maxRandomNumber; i++)
		count[i] = 0;							//先将count数组中元素设为0

	for (int i = 0;i < n;i++)
		(count[ a[i] ])++;						//遍历数组，进行计数
	
	int k = 0;
	for (auto i = 0; i < maxRandomNumber; i++) {
		while ((count[i])-- > 0) {
			a[k++] = i;							//通过count直接设置待排数组中的值
		}
	}
	delete[] count;
}