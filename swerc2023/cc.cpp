#include <bits/stdc++.h>
#define pb push_back
using namespace std; 
using ll = long long; 
 
 
ll x[100]; 
 
int n,m; 
 
//map<pair<int,ll>,double> dp; 
 
ll got(vector<int> aa){
    ll re = 0; 
    for(auto c : aa) re |= (1LL<<c); 
    return re; 
}
 
double dp[(1<<18)+2][120]; 
 
int leftmost(ll b){
    return 64-__builtin_clzll(b); 
}



// has[i] -> i 번째 노드를 가지고 있는 노선들의 집합 
ll has[200]; 

int popcnt(ll x){
    if(x==0) return 0; 
    return __builtin_popcountll(x); 
}
 
double get(int bit, ll shit) { 
    // if(dp.find({bit,shit})!=dp.end()) {
    //     return dp[{bit,shit}]; 
    // }]
    int idx = leftmost(shit); 
    if(dp[bit][idx]>=-1e-10){
        return dp[bit][idx]; 
    }
    if(__builtin_popcountll(shit)==1) {
        //dp[{bit,shit}] = 0; return 0; 
        return dp[bit][idx] = 0; 
    }
    double ans = 1e18; 
    for(int i=0;i<n;i++) if(((bit>>i)&1)==0){
        ll goo = shit&has[i]; ll gee = shit-goo; 
        if(popcnt(goo)==0||popcnt(gee)==0) continue; 
        int bb = bit|(1LL<<i); 
        double le = get(bb,goo), re = get(bb,gee); 
        double tmp = (le*(popcnt(goo)) + re*(popcnt(gee)))/(popcnt(goo)+popcnt(gee)) + 1; 
        if(ans>tmp) ans = tmp; 
    }
    //return dp[{bit,shit}] = ans; 
    return dp[bit][idx] = ans; 
}
 
int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
    cin>>n>>m; 
    //cout<<__builtin_clzll(1)<<endl; 
    for(int i=0;i<(1<<18)+2;i++) for(int j=0;j<120;j++) dp[i][j] = -1; 
    for(int i=0;i<m;i++){
        int p; cin>>p; 
        while(p--){
            int u; cin>>u; x[i] |= (1LL<<u); 
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) if((x[j]>>i)&1) has[i] |= (1LL<<j);
    }
    for(int i=0;i<m;i++) for(int j=i+1;j<m;j++) if(x[i]==x[j]) {
        cout << "not possible"; return 0; 
    }
    cout << fixed; cout.precision(10); 
    cout << get(0,(1LL<<m)-1); 
    return 0; 
}