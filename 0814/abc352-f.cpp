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
//#include <atcoder/modint> 
//using namespace atcoder; 
//using mint = modint998244353; 

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
//void __print(mint x) {cerr << (x.val());}

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

int a[1000],b[1000],c[1000]; 
vector<pair<int,int>> g[20]; 
bool vis[20]; 
int v[20]; 
int par[20]; 
int sex[20]; 
int ans[20]; 

void solve(){
    int n,m; cin>>n>>m; 
    rep(i,m){
        int a,b,c; cin>>a>>b>>c; a--; b--; 
        g[a].pb({b,-c}); g[b].pb({a,c}); 
    }
    rep(i,n) par[i] = -1; 
    rep(i,n) if(!vis[i]){
        queue<int> q; q.push(i); 
        int mx = 0; 
        while(!q.empty()){
            int f = q.front(); 
            q.pop(); 
            if(vis[f]) continue; 
            vis[f] = 1; par[f] = i; 
            for(auto [ne,vv] : g[f]) if(!vis[ne]) {
                v[ne] = v[f] + vv; 
                q.push(ne); mx=min(mx,v[ne]); 
            }
        }
        int shit = 0; 
        rep(j,n) if(par[j]==i) {
            shit |= (1<<v[j]-mx); v[j]-=mx; 
        }
        sex[i] = shit; 
        dbg(i,sex[i])
    }
    dbg(1)
    rep(i,n) if(par[i]==i){
        vector<bool> dp(1<<n); 
        dp[0] = 1; 
        rep(j,n) if(j!=i&&par[j]==j){
            vector<bool> ndp = dp; 
            int xx = sex[j]; 
            while(xx<(1<<n)){
                rep(k,1<<n) if(dp[k]&&((k&xx)==0)) ndp[k|xx] = 1; 
                xx <<= 1;  
            }
            dp = ndp; 
        }
        int cnt = 0; 
        int xx = sex[i]; int ff = 0; 
        while(xx<(1<<n)){
            if(dp[(1<<n)-1-xx]) {
                dbg(xx,'?????????????')
                cnt++; ff=xx;  
            }
            xx <<= 1; 
        }
        dbg(cnt)
        if(cnt>=2) {
            rep(j,n) if(par[j]==i) ans[j] = -1; 
        }
        else {
            // ff 의 최소 비트 
            int k = __builtin_ctz(ff); 
            dbg(ff,k)
            rep(j,n) if(par[j]==i) ans[j] = k+v[j]; 
        }
    }
    rep(i,n) cout << (ans[i]==-1 ? -1 : ans[i]+1) << " "; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}