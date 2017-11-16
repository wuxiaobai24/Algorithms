#!/usr/bin/python
# -*- coding:utf-8 -*-

import random
from timeit import timeit
import sys

def createC(n,m):
    """
    :type n:int 设备数
    :type m:int 车间数
    :rtype: [[]] c[i][j] means 第i个车间有j台设备时产生的盈利
    """
    return [[ random.randint(0,1000) for j in range(m) ] for i in range(n)]

def maxProfits(c):
    """
    :type c List[List[int]]
    :rtype int
    """
    m = len(c) # 设备数
    n = len(c[0]) # 车间数
    profits = [[0 for j in range(n+1)] for i in range(m+1)]
    for i in range(1,m+1):
        for j in range(1,n+1):
            t =[c[k-1][j-1]+profits[i-k][j-1] for k in range(1,i)]
            t.append(profits[i][j-1])
            profits[i][j] = max(t)
    print(m,n)
    return profits[-1][-1]

def maxProfits2(c):
    """
    :type c List[List[int]]
    :rtype int
    """
    m = len(c)
    n = len(c[0])
    profits = [[0 for j in range(m+1)] for i in range(n+1)]
    #profits[i][j] 前i个车间分配j个设备时的最大盈利
    for i in range(1,n+1):
        for j in range(1,m+1):
            t = [c[k-1][i-1] + profits[i-1][j-k] for k in range(1,j)]
            t.append(profits[i-1][j])
            profits[i][j] = max(t)
    return profits[-1][-1]

def maxProfits3(c):
    """
    :type List[List[int]]
    :rtype int
    """
    m = len(c)
    n = len(c[0])
    profits = [0 for j in range(m+1)]
    for i in range(1,n+1):
        for j in range(1,m+1):
            t = [c[k-1][i-1] + profits[j-k] for k in range(1,j)]
            t.append(profits[j])
            profits[j] = max(t)
    return profits[-1]

def maxProfitBF(c,m,n):
    """
    :type c: List[List[int]]
    :type m: int #设备数
    :type n: int #车间数
    :rtype int
    """
    if m == 0 or n == 0:
        return 0
    t = [c[k-1][n-1] + maxProfitBF(c,m-k,n-1) for k in range(1,m)]
    t.append(maxProfitBF(c,m,n-1))
    return max(t)


if __name__ == '__main__':
    m = int(sys.argv[1])
    n = int(sys.argv[2])
    c = createC(m,n)
    #print c
    #print maxProfits(c)
    #print maxProfits2(c)
    #print maxProfitBF(c,3,4)
    t = timeit('maxProfits2(c)','from __main__ import maxProfits2,c',number = 100)
    print t
