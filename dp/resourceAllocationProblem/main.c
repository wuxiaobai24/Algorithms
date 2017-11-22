#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <pthread.h>

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
        for(int i = 0;i < n+1;i++) cout << dp[i] << " ";
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


typedef struct {
    int start,end;
}Args;

int *dp1,*dp2;
int i;
vector<vector<int>> *pc;
Args args[4];
int outside_n,outside_m;

pthread_barrier_t barrier1,barrier2;

void *thread_helper(void *arg) {
    Args* pa = (Args *)arg;
    int start = pa->start;
    int end = pa->end;
    vector<vector<int>> &c = *pc;
    int t = 0;
    int res;

    do {
    
        for(int j = start;j < end;j++) {
            t = 0;
            for(int k = 1;k <= outside_n-j;k++) {
                t = c[i-1][k-1] + dp1[j+k];
                if (t > dp2[j]) {
                    dp2[j] = t;
                }
            }
        }

        res = pthread_barrier_wait(&barrier1);
        if (res == PTHREAD_BARRIER_SERIAL_THREAD) {
            i++;
            swap(dp1,dp2);
        }
        pthread_barrier_wait(&barrier2);
    } while(i <= outside_m );
}


int maxProfit5(vector<vector<int> >&c,int m,int n) {
    dp1 = new int[n+1];
    dp2 = new int[n+1];
    outside_n = n;
    outside_m = m;
    pc = &c;
    memset(dp1,0,sizeof(int)*(n+1)); 
    memset(dp2,0,sizeof(int)*(n+1)); 
    args[0] = {0,n/2};
    args[1] = {n/2,n};
//    args[2] = {n/2,n/2 + n/4};
//    args[3] = {n/2 + n/4,n};
    i = 1;
    pthread_t tid[4];


    pthread_barrier_init(&barrier1,NULL,2);
    pthread_barrier_init(&barrier2,NULL,2);

    pthread_create(&tid[0],NULL,thread_helper,(void *)&args[0]);
    pthread_create(&tid[1],NULL,thread_helper,(void *)&args[1]);
//    pthread_create(&tid[2],NULL,thread_helper,(void *)&args[2]);
//    pthread_create(&tid[3],NULL,thread_helper,(void *)&args[3]);


#ifdef PRINTDP
        for(int i = 0;i < n+1;i++) cout << dp1[i] << " ";
        cout << endl;
#endif

    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
//    pthread_join(tid[2],NULL);
//    pthread_join(tid[3],NULL);

    pthread_barrier_destroy(&barrier1);
    pthread_barrier_destroy(&barrier2);

#ifdef PRINTDP
    for(int i = 0;i < n+1;i++) cout << dp1[i] << " ";
    cout << endl;
#endif
    int ret = dp1[0];
    delete dp1;
    delete dp2;
    return ret;
}
typedef int (*MaxProfitFunc)(vector<vector<int>> &,int,int);

int main(int argc,char **argv) {
    srand(time(NULL));
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
    else if (fi == 5) f = maxProfit5;
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
//        newC(c);
    }
    cout << "avg time:" << sum/(1.0*t*k)/CLOCKS_PER_SEC << endl;
    return 0;
}
