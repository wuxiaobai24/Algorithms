#include "sort.h"

void quicksort(int a[], int first, int last);
int partition(int a[], int first, int last);

void quickSort(int a[], int n) {
	//quickSort��ڣ�Ϊͳһ�ӿ�
	quicksort(a, 0, n - 1);
}


/*
 * quicksort ��˼·�ǣ�
	- ��ѡ��һ��Ԫ����Ϊ��㣬�����ŵ��ʵ���λ�ã�
	  ��֤����ǰ�������Ԫ��x��������������Ԫ��y���� x <= key <= y
	  �����׵ó������������ź����������λ��
	- �����������λ��Ϊmi����ʱ���ǿ��԰��������зֳ�[first,mid),[mid+1,last]
	  ���ǿ��Եݹ�ĵ���quicksort,�ݹ������������first>=last
	- �����ǵ��͵ķ��η�����ʱ�临�Ӷ���Ҫ���ڡ��֡��������Ρ�ֻ��Ҫ����ʱ�伴�ɡ�
 */

												
void quicksort(int a[], int first, int last) {	//ע���������Ϊ: a[first,last]
	if (first < last) {							//�ݹ����������first >= last
		int p = partition(a, first, last);		//�ҳ�����λ��
		quicksort(a, first, p - 1);				
		quicksort(a, p + 1, last);
	}
}

int partition(int a[], int first, int last) {	//O(last-first + 1)

	swap(a[first], a[first + rand() % (last - first + 1)]);//ʹ������ѡȡ����������������ĳ��ֵĸ���
	
	int key = a[first];
	while (first < last) {									
		//������ѭ���У���last�ڶ�ʱ��first��ָ���Ԫ���Ƕ���ģ���֮��Ȼ��
		//���Ե�first��lastָ��ͬһ��Ԫ��ʱ�����Ԫ����Ȼ�Ƕ���ģ������λ�þ���key����λ�á�

		while (first < last && a[last] >= key) last--;		//ע��Ҫ�������x <= k <= y	
		a[first] = a[last];
		while (first < last && a[first] <= key) first++;	//����ڲ�ѭ���е�����ȱ��=���������ѭ����
		a[last] = a[first];
	}
	a[first] = key;
	return first;
}