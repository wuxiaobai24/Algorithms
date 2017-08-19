#include <iostream>
#include <vector>

using namespace std;

void insertion_sort(vector<int>& ivec){
    for(int i = 1;i!=ivec.size();i++){
      int key = ivec[i];
      int j = i-1;
      while(j >= 0 && ivec[j] > key){
        ivec[j + 1] = ivec[j];
        j = j-1;
      }
      ivec[j + 1] = key;
    }
}

int main (){
    vector<int> ivec {1,2,4,5,1,23,1,414,1};
    insertion_sort(ivec);
    for(auto i: ivec)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
