#include "sort.h"

/*
 * selectSort��bubbleSort���ƣ�ͬ��������ѭ����ֻ�Ƕ�����ԵĴ���һ�����ˡ�
 * selectSort���ڲ�����л��ҳ���С��Ԫ�أ�Ȼ��ѷ��ڵ�ǰ���е���ǰ��
 * ͬ���ļ����ҳ���С�ģ����ڵڶ�λ������һֱ��������Ե�Ԫ���Ѿ����ʵ���λ�á�

**/

void selectSort(int a[],int n) {
	for (int i = 0; i < n; ++i) {
		int min = i;						//�ٶ�a[i]����С��Ԫ��
		for (int j = i + 1; j < n; ++j) {
			if (a[j] < a[i])
				min = j;					//����һ���ȵ�ǰ��СԪ�ػ�ҪС��Ԫ��ʱ���ı�min��ֵ
		}
		if (min != i)
			swap(a[i], a[min]);				//ֻ��min��ֵ���ı�Żύ����
	}
}