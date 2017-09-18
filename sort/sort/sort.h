#pragma once
#include <vector>
#include <iostream>
#include "settings.h"
using std::vector;
using std::cout;

void swap(int &a, int &b);

/*
 * a			表示待排序数组
 * n			数组规模
 * algorithm	选择排序算法
 */
void Sort(int *a, int n,int algorithm);

/*
 * n			表示测试集的大小
 * algorithm	选择算法
 * count		由于测试集太小时，可能会出现0ms的情况，即不用1ms就完成，
 * 				这时可以通过设置count来让排序做多几次，以得到结果
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