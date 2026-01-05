//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
#include <chrono> 
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rrep(i, n) for (int i = 1; i <= n; ++i)
#define ff first
#define ss second
using namespace std;
typedef long long ll;
#include <atcoder/modint> 
using namespace atcoder; 
using mint = modint998244353; 

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
void __print(mint x) {cerr << (x.val());}

template <typename T, typename V> void __print(const pair<T, V> &x) {
cerr << '{';
__print(x.first);
cerr << ", ";
__print(x.second);
cerr << '}';
}
template <typename T> void __print(const T &x) {
int f = 0;
cerr << '{';
for (auto &i : x)
    cerr << (f++ ? ", " : ""), __print(i);
cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V> void _print(T t, V... v) {
__print(t);
if (sizeof...(v))
    cerr << ", ";
_print(v...);
}
#ifndef ONLINE_JUDGE
#define dbg(x...)                                                              \
cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = [";    \
_print(x);                                                                   \
cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

mt19937 rng(static_cast<int>(chrono::steady_clock::now().time_since_epoch().count()));
ll randint(ll lb, ll ub) { return uniform_int_distribution<ll>(lb, ub)(rng); }

long long inv(long long a, long long b){
    return 1<a ? b - inv(b%a,a)*b/a : 1;
}
using namespace atcoder; 
using mint = modint998244353; 

const int N = 20000;
mint fac[N],rfac[N]; 
mint ncr(int n, int r){
    if(r<0||r>n) return (mint)0; 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

void init_(){
    fac[0]=rfac[0]=1;
    for(int i=1;i<N;i++) fac[i]=i*fac[i-1],rfac[i]=rfac[i-1]/i; 
}


int par[N]; 
int a[N]; 
vector<int> g[N]; 
int pp[N]; 
vector<int> gp[N]; 

int sz[N]; 
mint dp[N]; 

void init(int n){
    rep(i,n+1){
        par[i] = 0; a[i] = 0; g[i].clear(); pp[i] = 0; gp[i].clear(); 
        sz[i] = 0; dp[i] = 0; 
    }
}

void dfs(int v, int p) { 
    // gp 
    int child = gp[v].size(); 
    dp[v] = 1; 
    if(child==0) {
        sz[v] = 1; dp[v] = 1; return; 
    }
    for(auto c : gp[v]) if(c!=v) {
        dfs(c,v); 
        sz[v] += sz[c]; 
        dp[v] *= dp[c] * rfac[sz[c]]; 
        dbg(c,dp[c],sz[c])
    }
    dp[v] *= fac[sz[v]];
    sz[v] += 1; 
}

void solve(){
    int n; cin>>n; 
    init(n); 
    dbg(n)
    par[1] = 1; 
    for(int i=2;i<=n;i++) cin >> par[i]; 
    rrep(i,n) {
        cin >> a[i]; g[a[i]].pb(i); 
    }
    rrep(i,n){
        if(i==1) continue; 
        int s = par[i]; 
        while(s!=1){
            if(a[s]==a[i]) {
                pp[i] = s; gp[s].pb(i); break; 
            }
            s = par[s]; 
        }
        if(pp[i]==0 && a[s]==a[i]) {
            pp[i] = s; gp[s].pb(i); 
        }
        dbg(i,pp[i])
    }
    mint ans = 1; 
    for(int s=0;s<=n;s++) if(!g[s].empty()) {
        dbg(s,g[s])
        vector<int> ss; 
        mint dd = 1; 
        for(auto x : g[s]) if(pp[x]==0){
            dfs(x,x); 
            dd *= dp[x]; 
            ss.pb(sz[x]);  
            dbg(x,dp[x],sz[x])
            dd *= rfac[sz[x]]; 
        }
        int sum = accumulate(all(ss),0); 
        dd *= fac[sum]; 
        ans *= dd; 
    }
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   init_(); 
   cin >> t;
   while(t--) solve(); 
   return 0;
}