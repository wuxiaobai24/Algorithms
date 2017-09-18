#include "sort.h"

/*
 * ��������Ĵ��˼·�ǣ�����һ��������飬��¼ÿһ�������ֵĸ�����
 * �����ͨ����Щ��¼ֱ�Ӹ�д�������顣
 * ���������ǱȽ�����ʱ�临�Ӷ�ΪO(n),�ռ临�Ӷ�ΪO(m)��
 *	mΪ�������������ֵ����ֵ����Сֵ�Ĳ�ֵ��������ֱ�Ӽ������ֵΪmaxRandomNumber,��СֵΪ0
 */

void countSort(int a[], int n)
{
	//int size = abs(maxRandomNumber - min(a) );	//�������Լ���һЩ�ռ临�Ӷ�
	//int offset = min(a) - 0;
	int *count = new int[maxRandomNumber];		//������������Ҫ���Ʒ�Χ�ģ����ҷ�Χ̫��ʱЧ��Ҳ����
	for (int i = 0; i < maxRandomNumber; i++)
		count[i] = 0;							//�Ƚ�count������Ԫ����Ϊ0

	for (int i = 0;i < n;i++)
		(count[ a[i] ])++;						//�������飬���м���
	
	int k = 0;
	for (auto i = 0; i < maxRandomNumber; i++) {
		while ((count[i])-- > 0) {
			a[k++] = i;							//ͨ��countֱ�����ô��������е�ֵ
		}
	}
	delete[] count;
}