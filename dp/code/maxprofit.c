#include "maxprofit.h"
#include <unistd.h>
#include  <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int maxprofit1(int **c,int m,int n) {
    int t;
    int **dp = (int **)malloc(sizeof(int*)*m+1);
    for(int i = 0;i <= m;i++) {
        dp[i] = (int *)malloc(sizeof(int)*(n+1));
        memset(dp[i],0,sizeof(int)*(n+1));
    }
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= n;j++) {
            dp[i][j] = dp[i-1][j];
            for(int k = 1;k <= j;k++) {
                t = c[i-1][k-1] + dp[i-1][j-k];
                if (t > dp[i][j]) dp[i][j] = t;
            }
        }
    int ret = dp[m][n];
    for(int i = 0;i <= m;i++)
        free(dp[i]);
    free(dp);
    return ret;
}

int maxprofit2(int **c,int m,int n) {
    int *dp = (int*)malloc(sizeof(int)*(n+1));
    memset(dp,0,sizeof(int)*(n+1));
    int i,j,k,t; 
    for(i = 1;i <= m;i++)
        for(j = n;j >= 1;j--) 
            for(k = 1;k <= j;k++) {
                t = c[i-1][k-1] + dp[j-k];
                if (t > dp[j]) {
                    dp[j] = t;
                }
            }
    
    int ret = dp[n];
    free(dp);
    return ret;
}

int maxprofit3(int **c,int m,int n) {
    int *dp = (int*)malloc(sizeof(int)*(n+1));
    int t,end;
    int i,j,k;
    memset(dp,0,sizeof(int)*(n+1));
    for (i = 1;i <= m;i++) 
        for(j = 0;j < n;j++) {
            end = n-j;
            for(k = 1;k <= end;k++) {
                t = c[i-1][k-1] + dp[j+k];
                if (t > dp[j]) {
                    dp[j] = t;
                }
            }
        }
    int ret = dp[0];
    free(dp);
    return ret;
}


//////////////////////////////////////////////////////////////////////////
//thread

typedef struct {
    int start,end;
} Arg;
int i,**out_c,out_n,out_m;
int *dp1,*dp2;
void *helper1(void *arg) {
    Arg *pa = (Arg *)arg;
    int start = pa->start, end = pa->end;
    int j,k,t;
    for(j = end;j >= start;j--) {
        dp2[j] = dp1[j];
        for(k = 1;k <= j;k++) {
            t = out_c[i-1][k-1] + dp1[j-k];
            if (t > dp2[j]){
                dp2[j] = t;
            }
        }
    }
}

int maxprofit4(int **c,int m,int n) {
    dp1 = (int *)malloc(sizeof(int)*(n+1));
    dp2 = (int *)malloc(sizeof(int)*(n+1));
    memset(dp1,0,sizeof(int)*(n+1));
    memset(dp2,0,sizeof(int)*(n+1));
    int j;
    int *p;
    Arg args[4] = {
        //n/2   n/4         n/8             n/16
        {1,n/2},{n/2,3*n/4},{3*n/4,7*n/8},{7*n/8,n}
    };
    pthread_t tid[4];
    out_c  = c;
    for(i = 1;i <= m;i++) {
        pthread_create(&tid[0],NULL,helper1,(void *)&args[0]);
        pthread_create(&tid[1],NULL,helper1,(void *)&args[1]);
        pthread_create(&tid[2],NULL,helper1,(void *)&args[2]);
        pthread_create(&tid[3],NULL,helper1,(void *)&args[3]);

        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
        pthread_join(tid[2],NULL);
        pthread_join(tid[3],NULL);

        p = dp1; dp1 = dp2; dp2 = p;
    }
    int ret = dp1[n];
    free(dp1); free(dp2);
    return ret;
}

//////////////////////////////////////////////////////////
//thread barriers
//
pthread_barrier_t barrier;
pthread_cond_t cond;
pthread_mutex_t mutex;
int thread_count = 0;

void *helper2(void *arg) {
    Arg *pa = (Arg *)arg;
    int start = pa->start,end = pa->end;
    int t,res,*p;
    int j,k;
    while(i <= out_m) {
        
        for(j = end;j >= start;j--) {
            dp2[j] = dp1[j];
            for (k = 1;k <= j;k++) {
                t = out_c[i-1][k-1] + dp1[j-k];
                if (t > dp2[j]) dp2[j] = t;
            }
        }

        //同步
        //res = pthread_barrier_wait(&barrier);
        pthread_mutex_lock(&mutex);
        thread_count = (thread_count + 1)%4;
        if (thread_count == 0) {
            //最后一个线程
            p = dp1; dp1 = dp2; dp2 = p;
            i++;
            pthread_cond_broadcast(&cond);
        } else
            pthread_cond_wait(&cond,&mutex);
        pthread_mutex_unlock(&mutex);
    }
}

int maxprofit5(int **c,int m,int n) {
    dp1 = (int *)malloc(sizeof(int)*(n+1));
    dp2 = (int *)malloc(sizeof(int)*(n+1));
    memset(dp1,0,sizeof(int)*(n+1));
    memset(dp2,0,sizeof(int)*(n+1));
    Arg args[4] = {
        {1,n/2},{n/2,3*n/4},{3*n/4,7*n/8},{7*n/8,n}
    };
    pthread_t tid[4];
    i = 1;
    out_m = m;
    out_c = c;
    thread_count = 0;
    //pthread_barrier_init(&barrier,NULL,4);
    pthread_cond_init(&cond,NULL);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&tid[0],NULL,helper2,(void *)&args[0]);
    pthread_create(&tid[1],NULL,helper2,(void *)&args[1]);
    pthread_create(&tid[2],NULL,helper2,(void *)&args[2]);
    pthread_create(&tid[3],NULL,helper2,(void *)&args[3]);


    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    //pthread_barrier_destroy(&barrier);

    int ret = dp1[n];
    free(dp1);
    free(dp2);
    return ret;
}

//////////////////////////////////////////////////////////////////////
//thread
//
int **dp;
int out_i;
void *helper3(void *args)  {
    Arg *pa = (Arg *)args;    
    int start = pa->start;
    int end = pa->end;
    int j,k,t;
    while(out_i <= out_m) {
        for(j = start;j <= end;j++) {
            dp[out_i][j] = dp[out_i-1][j];
            for(k = 1;k <= j;k++) {
                t = out_c[out_i-1][k-1] + dp[out_i-1][j-k];
                if (t > dp[out_i][j]) dp[out_i][j] = t;
            }
        }
        out_i++;
    }
}

int maxprofit6(int **c,int m,int n) {
    pthread_t tid;

    out_m = m,out_c = c;

    dp = (int **) malloc(sizeof(int *)*(m+1));
    for(int i = 0;i <= m;i++) {
        dp[i] = (int *)malloc(sizeof(int *)*(n+1));
        memset(dp[i],0,sizeof(int)*(n+1));
    }

    Arg arg[2] = {
        {1,3*n/5},{3*n/5,15*n/16}
    };
    out_i = 1;
    pthread_create(&tid,NULL,helper3,(void *)&arg);
    int i,j,k,t;
    int count = 0;
    for(i = 1;i <=m;i++) {
        for(j = 3*n/5;j <= n;j++) {
            dp[i][j] = dp[i-1][j];
            for(k = 1;k <= j;k++) {
                t = c[i-1][k-1] + dp[i-1][j-k];
                if (t > dp[i][j]) dp[i][j] = t;
            }
        }
        while(i >= out_i) { sleep(0.001); count++;}
    }
    printf("%d\n",count);
    pthread_join(tid,NULL);
    int ret = dp[m][n];
    for(int i = 0;i <= m;i++) 
        free(dp[i]);
    free(dp);
    return ret;
}

typedef struct newArg {
    int start,end;
    int index;
}newArg;

int out_i_n[4] = {1,1,1,1};

void *helper4(void *arg) {
    newArg *pa = (newArg *)arg;
    int start = pa->start;
    int end = pa->end;
    int index = pa->index;
    int j,k,t;
    for(int i = 1;i <= out_m;) {
  //      printf("thread %d'i = %d",index,i);
        for(j = start;j <= end;j++) {
            for(k = 1;k <= j;k++) {
                t = out_c[i-1][k-1] + dp[i-1][j-k];
                if (t > dp[i][j]) dp[i][j] = t;
            }
        }
        pthread_mutex_lock(&mutex);
        i++;
        out_i_n[index] = i;
        pthread_cond_broadcast(&cond);
//        printf("broadcast from %d\n",index);
        if (index != 0) {
            while(i <= out_m && out_i_n[index-1] <= i)
                pthread_cond_wait(&cond,&mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int maxprofit7(int **c,int m,int n) {
   pthread_t tid[4];
   out_m = m;out_c = c;
   out_n = n;
   dp = (int **)malloc(sizeof(int*)*(m+1));
   for(int i = 0;i <= m;i++) {
        dp[i] = (int *)malloc(sizeof(int)*(n+1));
        memset(dp[i],0,sizeof(int)*(n+1));
   }

   newArg arg[4] = {
    {1,n/2,0},{n/2,3*n/4,1},{3*n/4,15*n/16,2},{15*n/16,n,3}
   };
   pthread_mutex_init(&mutex,NULL);
   pthread_cond_init(&cond,NULL);
   pthread_create(&tid[0],NULL,helper4,(void*)&arg[0]);
   pthread_create(&tid[1],NULL,helper4,(void*)&arg[1]);
   pthread_create(&tid[2],NULL,helper4,(void*)&arg[2]);
   pthread_create(&tid[3],NULL,helper4,(void*)&arg[3]);


   pthread_join(tid[0],NULL);
   pthread_join(tid[1],NULL);
   pthread_join(tid[2],NULL);
   pthread_join(tid[3],NULL);
   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond);
   int ret = dp[m][n];
   for(int i = 0;i <=m;i++) free(dp[i]);
   free(dp);
   return ret;
}
