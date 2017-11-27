#!/usr/bin/python
# -*- coding:utf-8 -*-

import random
from timeit import timeit
import sys

def ReadFromFile(filename):
    c = []
    with open(filename,'r') as f:
        for line in f:
            c.append(list(map(int,line.split())))
    return c

def createC(n,m):
    """
    :type n:int 设备数
    :type m:int 车间数
    :rtype: [[]] c[i][j] 第i+1个车间分配了j+1台设备产生的盈利
    """
    return [[ random.randint(0,1000) for j in range(n) ] for i in range(m)]

def maxProfits(c,n,m):
    """
    :type n int #设备数
    :type m int #车间数
    :type c List[List[int]]
    :rtype int
    """
    dp = [[ 0 for j in range(n+1)] for i in range(m+1)]
    ans = [0 for i in range(m)]
    for i in range(1,m+1):
        for j in range(1,n+1):
            dp[i][j] = dp[i-1][j]
            for k in range(1,j+1):
                dp[i][j] = max(dp[i][j],c[i-1][k-1] + dp[i-1][j-k])
#    print dp
    return dp[-1][-1]

def maxProfits2(c,n,m):
    dp = [0 for i in range(n+1)]
    for i in range(1,m+1):
        for j in range(n,0,-1):
            t = dp[j]
            for k in range(1,j+1):
                t = max(t,dp[j-k] + c[i-1][k-1])
            dp[j] = t
    return dp[-1]

def maxProfits3(c,n,m):
    dp = [0]*(n+1)
    for i in range(1,m+1):
        pass

class MaxProfit:
    def __init__(self,c,n,m):
        self.c = c
        self.n = n # 设备数
        self.m = m # 车间数
        self.ans = []
        self.maxAns = []
        self.maxProfits = 0
    def reset(self,c,n,m):
        self.c = c
        self.n = n
        self.m = m
        self.ans = []
        self.maxAns = []
        self.maxProfits = 0
    def check(self,k):
        if sum(self.ans) + k > self.n:
            return False
        else:
            return True
    def GetAns(self):
        if len(self.ans) == self.m or sum(self.ans) == self.n:
            profit = self.calAns()
            if profit > self.maxProfits:
                self.maxProfits = profit
                self.ansVec = self.ans[:]

                #print '#',self.ans
        else:
            for i in range(self.n + 1):
                if self.check(i):
                    self.ans.append(i)
                    self.GetAns()
        if len(self.ans) != 0:
            self.ans.pop()
    def calAns(self):
        profit = 0
        for i in range(len(self.ans)):
            if self.ans[i] != 0:
                profit += self.c[i][self.ans[i] - 1]
        return profit

def test():
    """test"""
    c = [[30,40,50],[20,30,50],[20,25,30]]
    print maxProfits(c,3,3)
    mp = MaxProfit(c,3,3)
    mp.GetAns()
    print mp.ansVec
    print mp.maxProfits
    for i in range(10):
        n = random.randint(1,8)
        m = random.randint(1,8)
        c = createC(n,m)
        p1 = maxProfits2(c,n,m)
        mp.reset(c,n,m)
        mp.GetAns()
        if p1 != mp.maxProfits:
            print "error:"
            print p1,mp.maxProfits
            print mp.maxAns
            print c
            print "================================="

def writeToFile(filename,c,m,n,ans):
    with open(filename,'w') as f:
        f.write(str(m) + ' ' + str(n) + '\n')
        for vec in c:
            for i in vec:
                f.write(str(i) + ' ')
            f.write('\n')
        f.write(str(ans))
if __name__ == '__main__':
    test()
    m = int(sys.argv[1])
    n = int(sys.argv[2])
    filename = sys.argv[3]
    c = createC(m,n)
    
    mp = MaxProfit(c,m,n)
    mp.GetAns()
    #print(m,n)
    #print(c)
    #print(ans)
    writeToFile(filename,c,m,n,mp.maxProfits)
    #c = createC(m,n)
    #for v in c:
    #    for i in c:
    #        i = int(input())
    #t = timeit('maxProfits2(c)','from __main__ import maxProfits2,c',number = 100)
    #print t
