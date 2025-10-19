#include <bits/stdc++.h>
#define pb push_back
using namespace std; 

// swerc 

int xx[5]; 

bool cmp(pair<int,int> p, pair<int,int> q){
    if(p.first!=q.first) return xx[p.first] < xx[q.first]; 
    return p.second < q.second; 
}

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    cout<<__builtin_clzll(0)<<endl; 
}