#include "sort.h"


int getNumberPos(int num, int t);

/*
 *	radixSort �Ĵ��˼·�ǣ�
 *	-	�Ȱ�����Ԫ�صĸ�λ���Ĵ�С���������ٰ�ʮλ���Ĵ�С���������Դ�����
 *  -	����һ�����ֵ�ĳ��λֻ������0��9֮��Ԫ�أ����Կ������ü�������ķ���������10��Ͱ�������ӿ������ٶ�
 *  -   ������λԽ�ߣ����������ִ�С��Ӱ��Խ�����ԣ��������������������Ȼ��������
 *  -
**/

void radixSort(int a[],int n) {
	vector<vector<int> > iivec(10);
	//std::cout << iivec[0].size() << "\n";
	for (int t = 1; t == 1 || t % 10 == 0; t *= 10) {
		//��Ԫ�ذ���һ���������Ͱ��
		for (int i = 0;i < n;i++)
			iivec[getNumberPos(a[i], t)].push_back(a[i]);

		int k = 0,size = 0;		//��Ͱ��ȡ��Ԫ��
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