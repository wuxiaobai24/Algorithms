#include "sort.h"



void bubbleSort(int a[],int n){
	
	bool sorted = false;			//����flag�����Լ��ٲ���Ҫ�ĵ�����

	for (int i = 0; i < n && !sorted; ++i) {
		sorted = true;				//ÿ���ȼ��赱ǰ�����Ѿ��ź�����
		for (int j = i + 1; j < n; ++j)
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
				sorted = false;		//ֻ�з��ִ�������Ե�ʱ�򣬽�sorted ����Ϊfalse
									//���ĳ�ε���ʱ��û�н���Ԫ�أ�
									//���ʾ��ǰ�����Ѿ��ź����ˣ�ע����ѭ����������
			}
	}
}