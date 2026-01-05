#include <bits/stdc++.h>
#define pb push_back
using namespace std; 
using ll = long long;
// swerc 

// x -> 31 크기 sigma i*x[i] = 30 

vector<vector<int>> b; 
int n,k,t; 
void dfs(int pos, int sum, vector<int> now){
    if(pos==n){
        if(sum==n){
            b.pb(now); 
        }
        return; 
    }
    int j = 0; 
    while(1){
        if(sum+(pos+1)*j<=n){
            vector<int> tt = now; 
            tt.pb(j);
            dfs(pos+1,sum+(pos+1)*j,tt);  
        }
        else break; 
        j++; 
    }
}

const int N = 6000; 
vector<pair<int,int>> trans[N]; 
// 다음 인덱스, 개수 

const ll MOD = 1000000007; 

ll dp[N]; 
ll ndp[N]; 



struct mint{
    int x;
    mint(): x(0){}
    mint(int x): x(x){}
    mint operator+(int ot) const{
        return x + ot >= MOD ? x - MOD + ot : x + ot;
    }
    mint operator-(int ot) const{
        return x - ot < 0 ? x - ot + MOD : x - ot;
    }
    mint operator(int ot) const{
        return 1LL x * ot % MOD;
    }
    mint operator+=(int ot){
        return this =this + ot;
    }
    mint operator-=(int ot){
        return this =this - ot;
    }
    mint operator=(int ot){
        returnthis = this ot;
    }
    operator int() const{
        return x;
    }
};
mint mpow(mint x, ll r){
       mint res = 1;
       while(r){
               if(r & 1) res * = x;
               x *= x;
               r >>= 1;
       }
       return res;
}


int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
    cin>>n>>k>>t; 
    for(int i=0;i<=n;i++) {
        vector<int> t; t.pb(0); t.pb(i); dfs(1,i,t); 
    }
    auto get = [&](vector<int> v){
        return lower_bound(b.begin(),b.end(),v) - b.begin(); 
    };
    for(int t=0; t<b.size(); t++){
        auto v = b[t]; 
        for(int i=1;i<=n;i++) if(v[i]) {
            for(int j=1;j*2<=i;j++){
                if(j*2!=i){
                    int k = i-j; 
                    ll gesu = v[i]*i;
                    auto w = v; 
                    w[i]--; w[j]++; w[k]++; 
                    int idx = get(w); 
                    trans[t].pb({idx,gesu}); 
                }
                else {
                    int k = i-j; 
                    ll gesu = v[i]*i/2;
                    auto w = v; 
                    w[i]--; w[j]++; w[k]++; 
                    int idx = get(w); 
                    trans[t].pb({idx,gesu}); 
                }
            }
        }
        for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) if(v[i]&&v[j]){
            ll gesu = 0; 
            if(i==j&&v[i]==1) continue; 
            if(i!=j) gesu = v[i]*v[j]*i*j; 
            else gesu = (v[i]*(v[i]-1)/2)*i*j; 
            auto w = v; 
            if(i+j>n){
                for(auto x : v) cout << x << " "; 
                return 0; 
            }
            w[i+j]++; w[i]--,w[j]--; 
            int idx = get(w); 
            trans[t].pb({idx,gesu}); 
        }
    }
    vector<int> w(n+1,0); 
    w[1] = n; 
    int idx = get(w); 
    cout << idx; 
    dp[idx] = 1; 
    // 1,2,3,1,1,1  -> dp[]   `

    auto calc = [&](vector<int> v){
        mint s = 1; 

    }; 
    for(int u=0;u<k;u++){
        memset(ndp,0,sizeof(ndp)); 
        for(int i=0;i<N;i++) {
            for(auto [idx,gesu]:trans[i]){
                ndp[idx] += dp[i]*gesu; 
                ndp[idx] %= MOD; 
            }
        }
        for(int i=0;i<N;i++) dp[i] = ndp[i]; 
    }
    for(int i=0;i<N;i++) if(dp[i]) {
        auto v = b[i]; 

    }
}