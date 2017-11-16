#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void newC(vector<vector<int>> &c) {
    for(auto &v:c)
        for(auto &i:v)
            i = rand() % 1000;
}

int maxProfit(vector<vector<int>> &c,int m,int n) {
    vector<int> profits(m+1,0);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++) {
            for(int k = 1;k < j;k++) {
                int t = c[k-1][i-1] + profits[j-k];
                profits[j] = max(profits[j],t);
            }
        }
    return *profits.rbegin();
}

int main(int argc,char **argv) {
    if (argc < 4) {
        cout << "Usage:./a.out n m k\n";
        return 1;
    }
    int n = atoi(argv[1]);  //n个设备
    int m = atoi(argv[2]);  //m个车间
    int k = atoi(argv[3]);  //测试k轮
    vector<vector<int> > c(n,vector<int>(m,0));
    newC(c);
    if (argc == 5 && string(argv[4]) == "test") {
    }
    cout << maxProfit(c,m,n) << endl;
    return 0;
}
