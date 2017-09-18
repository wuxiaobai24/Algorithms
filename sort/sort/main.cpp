#include <iostream>

#include <vector>
#include <string.h>
#include "sort.h"
#include "settings.h"
using namespace std;


/*
 * Usage： ./sort n a count 
 * For example: ./sort 10 1			//对规模为10的数组进行冒泡排序
				./sort 10 1 1000	//规模太小时,设置count以修正测试结果
 */

int main(int argc,char **argv) {


	if (argc < 3) {
		exit(1);
	}

	int n = atoi(argv[1]);			//元素个数
	int a = atoi(argv[2]);			//采用的算法1~10

#ifdef DEBUG
	testSort(n, a, 1);
	exit(0);
#endif

	int count = 1;
	if (argc == 4) {
		count = atoi(argv[3]);
	}
	//sort
	double amount = 0;

	for (int i = 0; i < 20; i++) {
		double ret = testSort(n, a, count);
		cout << ret << "ms ";
		amount += ret;
	}
	cout << amount/20 <<"ms\n";		//get average
	return 0;
}