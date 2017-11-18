#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <string.h>

//#define GETANS
//#define PRINTANS
//#define PRINTDP

using namespace std;

void newC(vector<vector<int>> &c) {
    for(auto &v:c)
        for(auto &i:v)
            i = rand() % 1000;
}

void printAns(vector<vector<int>> &ans,int m,int n) {
    if (m < 0 )
        return;
    printAns(ans,m-1,n-ans[m][n]);
#ifdef PRINTANS
    cout << m <<" "<< ans[m][n] << endl;
#endif
}

int maxProfit(vector<vector<int>> &c,int m,int n) {
    //m 车间数
    //n 设备数
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
#ifdef GETANS
    vector<vector<int>> ans(m,vector<int>(n,0));
#endif
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= n;j++) {
            dp[i][j] = dp[i-1][j];
            for(int k = 1;k <= j;k++) {
             //   dp[i][j] = max(dp[i][j],c[i-1][k-1] + dp[i-1][j-k]);
                int t = c[i-1][k-1] + dp[i-1][j-k];
                if (t > dp[i][j]) {
                    dp[i][j] = t;
#ifdef GETANS
                    ans[i-1][j-1] = k;
#endif
                }
            }
        }
#ifdef GETANS
    printAns(ans,m-1,n-1);
#endif
    return dp[m][n];
}

int maxProfit2(vector<vector<int> >&c,int m,int n) {
    vector<int> dp(n+1,0);
#ifdef GETANS
    vector<vector<int>> ans(m,vector<int>(n,0));
#endif
    for(int i = 1;i <= m;i++) {
        for(int j = n;j >= 1 ;j--) { //对Cache不友好
            for(int k = 1;k <= j;k++) {
                int t = c[i-1][k-1] + dp[j-k];
                if (t > dp[j]) {
                    dp[j] = t;
#ifdef GETANS
                    ans[i-1][j-1] = k;
#endif
                }
            }
        }
#ifdef PRINTDP
        for(auto i:dp) cout << i << " ";
        cout << endl;
#endif
    }
#ifdef GETANS
    printAns(ans,m-1,n-1);
#endif
    return dp[n];
}


int maxProfit3(vector<vector<int> >&c,int m,int n) {
    vector<int> dp(n+1,0);
#ifdef GETANS
    vector<vector<int>> ans(m,vector<int>(n,0));
#endif
    for(int i = 1;i <= m;i++) {
        for(int j = 0;j < n;j++) {
            //true j is n-j
            for(int k = 1;k <= n-j;k++) {
                int t = c[i-1][k-1] + dp[j+k];
                if (t > dp[j]) {
                    dp[j] = t;
#ifdef GETANS
                    ans[i-1][j-1] = k;
#endif
                }
            }
        }
#ifdef PRINTDP
        for(auto i:dp) cout << i << " ";
        cout << endl;
#endif
    }
#ifdef GETANS
    printAns(ans,m-1,n-1);
#endif
    return dp[0];
}


int maxProfit4(vector<vector<int> >&c,int m,int n) {
//    vector<int> dp(n+1,0);
    int *dp = new int[n+1];
    memset(dp,0,sizeof(int)*(n+1));
#ifdef GETANS
    vector<vector<int>> ans(m,vector<int>(n,0));
#endif
    for(int i = 1;i <= m;i++) {
        for(int j = 0;j < n;j++) {
            //true j is n-j
            for(int k = 1;k <= n-j;k++) {
                int t = c[i-1][k-1] + dp[j+k];
                if (t > dp[j]) {
                    dp[j] = t;
#ifdef GETANS
                    ans[i-1][j-1] = k;
#endif
                }
            }
        }
#ifdef PRINTDP
        for(auto i:dp) cout << i << " ";
        cout << endl;
#endif
    }
#ifdef GETANS
    printAns(ans,m-1,n-1);
#endif
    int ret = dp[0];
    delete dp;
    return ret;
}


int maxProfit5(vector<vector<int> >&c,int m,int n) {
    int *nc = new int[m*n];
    int *dp = new int[n+1];
    memset(dp,0,sizeof(int)*(n+1));
    memset(nc,0,sizeof(int)*n);
    int *p = nc + n;
    for(int i = 1;i < m;i++) {
        for(int j = 0;j < n;j++)
            *(p++) = c[i][j] - c[i-1][j];
    }
    for(int i = 1;i < m;i++) {
        for(int j = 1;j <= n;j++)
            ;            
    }
}
typedef int (*MaxProfitFunc)(vector<vector<int>> &,int,int);

int main(int argc,char **argv) {
    if (argc < 6) {
        cout << "Usage:./a.out n m t k f\n";
        return 1;
    }
    int n = atoi(argv[1]);  //n个设备
    int m = atoi(argv[2]);  //m个车间
    int t = atoi(argv[3]);
    int k = atoi(argv[4]);  //测试k轮
    int fi = atoi(argv[5]);  //选择测试函数
    cout << "n=" << n
        << " m=" << m
        << " t=" << t
        << " k=" << k
        << " fi=" << fi << endl;
    MaxProfitFunc f = NULL;
    if (fi == 1) f = maxProfit;
    else if (fi == 2) f = maxProfit2;
    else if (fi == 3) f = maxProfit3;
    else if (fi == 4) f = maxProfit4;
    else return 1;
    vector<vector<int> > c(m,vector<int>(n,0));
    //c[i][j] i 车间分配j个设备
    if (argc == 7 && string(argv[6]) == "test") {
        for(int i = 0;i < m;i++)
            for(int j = 0;j < n;j++)
                cin >> c[i][j];
    } else
        newC(c);
    
    clock_t sum  = 0;    
    for(int j = 0;j < t;j++) {
        clock_t begTime = clock();
        for(int i = 0;i < k;i++)
            cout << f(c,m,n) << "\t";
        clock_t endTime = clock();
        sum += (endTime-begTime);
        cout << (endTime-begTime)*1.0/CLOCKS_PER_SEC << endl;
    }
    cout << "avg time:" << sum/(1.0*t*k)/CLOCKS_PER_SEC << endl;
    return 0;
}
