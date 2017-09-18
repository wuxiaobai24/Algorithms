#include "sort.h"

/*
 * selectSort与bubbleSort类似，同样是两个循环，只是对逆序对的处理不一样罢了。
 * selectSort在内层过程中会找出最小的元素，然后把放在当前序列的最前面
 * 同样的继续找出次小的，放在第二位，这样一直到最后，所以得元素已经在适当的位置。

**/

void selectSort(int a[],int n) {
	for (int i = 0; i < n; ++i) {
		int min = i;						//假定a[i]是最小的元素
		for (int j = i + 1; j < n; ++j) {
			if (a[j] < a[i])
				min = j;					//发现一个比当前最小元素还要小的元素时，改变min的值
		}
		if (min != i)
			swap(a[i], a[min]);				//只有min的值被改变才会交换。
	}
}