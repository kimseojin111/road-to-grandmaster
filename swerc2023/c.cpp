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

double get(int bit, vector<int> shit) { 
    // if(dp.find({bit,shit})!=dp.end()) {
    //     return dp[{bit,shit}]; 
    // }]
    int idx = shit[0]; 
    if(dp[bit][idx]>=-1e-10){
        return dp[bit][idx]; 
    }
    if(shit.size()==1) {
        //dp[{bit,shit}] = 0; return 0; 
        return dp[bit][idx] = 0; 
    }
    double ans = 1e18; 
    //for(int i=0;i<m;i++) if((shit>>i)&1) can.pb(i); 
    for(int i=0;i<n;i++) if(((bit>>i)&1)==0){
        vector<int> goo; vector<int> gee; 
        for(auto c : shit) if((x[c]>>i)&1) goo.pb(c); else gee.pb(c); 
        if(goo.size()==0||gee.size()==0) continue; 
        int bb = bit|(1LL<<i); 
        double le = get(bb,goo), re = get(bb,gee); 
        double tmp = (le*(goo.size()) + re*(gee.size()))/(goo.size()+gee.size()) + 1; 
        if(ans>tmp) ans = tmp; 
    }
    //return dp[{bit,shit}] = ans; 
    return dp[bit][idx] = ans; 
}

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
    cin>>n>>m; 
    for(int i=0;i<(1<<18)+2;i++) for(int j=0;j<120;j++) dp[i][j] = -1; 
    for(int i=0;i<m;i++){
        int p; cin>>p; 
        while(p--){
            int u; cin>>u; x[i] |= (1LL<<u); 
        }
    }
    for(int i=0;i<m;i++) for(int j=i+1;j<m;j++) if(x[i]==x[j]) {
        cout << "not possible"; return 0; 
    }
    cout << fixed; cout.precision(10); 
    vector<int> ss; 
    for(int i=0;i<m;i++) ss.pb(i); 
    cout << get(0,ss); 
    return 0; 
}