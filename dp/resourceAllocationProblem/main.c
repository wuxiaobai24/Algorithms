#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>


using namespace std;

void newC(vector<vector<int>> &c) {
    for(auto &v:c)
        for(auto &i:v)
            i = rand() % 1000;
}

int maxProfit(vector<vector<int>> &c,int m,int n) {
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= n;j++) {
            dp[i][j] = dp[i-1][j];
            for(int k = 1;k <= j;k++)
                dp[i][j] = max(dp[i][j],c[i-1][k-1] + dp[i-1][j-k]);
        }
    return dp[m-1][n-1];
}

int main(int argc,char **argv) {
    if (argc < 4) {
        cout << "Usage:./a.out n m k\n";
        return 1;
    }
    int n = atoi(argv[1]);  //n个设备
    int m = atoi(argv[2]);  //m个车间
    int k = atoi(argv[3]);  //测试k轮
    vector<vector<int> > c(m,vector<int>(n,0));
  //  for(int i = 0;i < n;i++)
  //      for(int j = 0;j < m;j++)
  //          cin >> c[i][j];
   // newC(c);
    
    for(int j = 0;j < 20;j++) {
        clock_t begTime = clock();
        for(int i = 0;i < k;i++)
            maxProfit(c,m,n);
        clock_t endTime = clock();
        cout << (endTime-begTime)*1.0/CLOCKS_PER_SEC << endl;
    }
    return 0;
}
