#include "sort.h"

void quicksort(int a[], int first, int last);
int partition(int a[], int first, int last);

void quickSort(int a[], int n) {
	//quickSort入口，为统一接口
	quicksort(a, 0, n - 1);
}


/*
 * quicksort 的思路是：
	- 先选定一个元素作为轴点，把轴点放到适当的位置，
	  保证在其前面的任意元素x和在其后面的任意元素y满足 x <= key <= y
	  很容易得出这就是轴点在排好序后的数组的位置
	- 假设轴点最后的位置为mi，这时我们可以把整个序列分成[first,mid),[mid+1,last]
	  我们可以递归的调用quicksort,递归结束的条件是first>=last
	- 快排是典型的分治法，其时间复杂度主要花在“分”，而“治”只需要常熟时间即可。
 */

												
void quicksort(int a[], int first, int last) {	//注意待排序列为: a[first,last]
	if (first < last) {							//递归结束条件：first >= last
		int p = partition(a, first, last);		//找出轴点的位置
		quicksort(a, first, p - 1);				
		quicksort(a, p + 1, last);
	}
}

int partition(int a[], int first, int last) {	//O(last-first + 1)

	swap(a[first], a[first + rand() % (last - first + 1)]);//使得轴点的选取随机化，减少最坏情况的出现的概率
	
	int key = a[first];
	while (first < last) {									
		//在两个循环中，当last在动时，first所指向的元素是多余的，反之亦然。
		//所以当first和last指向同一个元素时，这个元素显然是多余的，而这个位置就是key最后的位置。

		while (first < last && a[last] >= key) last--;		//注意要满足的是x <= k <= y	
		a[first] = a[last];
		while (first < last && a[first] <= key) first++;	//如果内层循环中的条件缺少=，会出现死循环。
		a[last] = a[first];
	}
	a[first] = key;
	return first;
}