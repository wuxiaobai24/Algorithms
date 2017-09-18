#pragma once

//#define OUT 0
//#define DEBUG 0

//设置DEBUG 可以测试算法是否正确

#ifdef DEBUG
#define SHOWOUT
#endif

//决定待排序数据的最大值
const int maxRandomNumber = 1000;	