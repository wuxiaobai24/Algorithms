#pragma once
#include <vector>
#include <iostream>
#include "settings.h"
using std::vector;
using std::cout;

void swap(int &a, int &b);

/*
 * a			��ʾ����������
 * n			�����ģ
 * algorithm	ѡ�������㷨
 */
void Sort(int *a, int n,int algorithm);

/*
 * n			��ʾ���Լ��Ĵ�С
 * algorithm	ѡ���㷨
 * count		���ڲ��Լ�̫Сʱ�����ܻ����0ms�������������1ms����ɣ�
 * 				��ʱ����ͨ������count�����������༸�Σ��Եõ����
 */
double  testSort(int n, int algorithm,int count);


void bubbleSort(int a[], int n);	//1
void countSort(int a[], int n);		//2
void quickSort(int a[], int n);		//3
void mergeSort(int a[], int n);		//4
void insertionSort(int a[], int n);	//5
void selectSort(int a[], int n);	//6
void shellSort(int a[], int n);		//7
void radixSort(int a[], int n);		//8
void bucketSort(int a[], int n);	//9
void heapSort(int a[], int n);		//10