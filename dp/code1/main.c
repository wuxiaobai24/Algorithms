#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "maxprofit.h"
#define MAXPROFITFUNC_COUNT 7
MaxProfitFunc maxprofitfuncs[MAXPROFITFUNC_COUNT] = {
    maxprofit1,maxprofit2,maxprofit3,maxprofit4,maxprofit5,maxprofit6,maxprofit7
};

void newC(int **c,int m,int n) {
//    printf("newC start\n");
    for(int i = 0;i < n;i++)
        for(int j = 0;j < m;j++)
//            c[i][j] = rand() % 1000 + 1000*j;
            c[i][j] = rand() % 100000;
//    printf("newC over\n");
}

void test() {
    int m,n;
    scanf("%d %d",&m,&n);
    int **c = (int **)malloc(sizeof(int*)*n);
    
    for(int i = 0;i < n;i++) {
        c[i] = (int*)malloc(sizeof(int)*m);
        for(int j = 0;j < m;j++)
            scanf("%d",&c[i][j]);
    }

    int ans;
    scanf("%d",&ans);
    printf("ans = %d\n",ans);
    for(int i = 0;i < MAXPROFITFUNC_COUNT;i++)
        printf("maxprofit%d ans is %d\n",i+1,maxprofitfuncs[i](c,m,n) );

    for(int i = 0;i < n;i++)
        free(c[i]);
    free(c);
}

int main (int argc,char **argv) {
    if (argc == 2 && strcmp(argv[1],"test") == 0) {
        test();
        return 0;
    }

    if (argc < 5) {
        printf("Usage:./a.out m n t f [test]\n");
        return 0;
    }
    
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int t = atoi(argv[3]);
    int f = atoi(argv[4]);
    if (f > MAXPROFITFUNC_COUNT || f <= 0) return 1;
    MaxProfitFunc func = maxprofitfuncs[f-1];
    
    int **c = (int **)malloc(sizeof(int*)*n); 
    for(int i = 0;i < n;i++) c[i] = (int *)malloc(sizeof(int)*m);
    
    clock_t sum = 0;
//    newC(c,m,n);
    printf("start\n");
    for(int i = 0;i < t;i++) {
        newC(c,m,n);
        clock_t begtime = clock();
        printf("%d\t",func(c,m,n));
        clock_t endtime = clock();
        sum += (endtime - begtime);
        printf("%lfms\n",(endtime - begtime)*1000.0/CLOCKS_PER_SEC);
    }
    double avg_time = sum*1000.0/(CLOCKS_PER_SEC*t);
    printf("avg time:%lfms\n",avg_time);
    for(int i = 0;i < n;i++)
        free(c[i]);
    free(c);

    return 0;
}
