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

const int N = 200100; 
vector<pair<int,ll>> adj[N]; 

ll dist[20][20]; 

bool vis[20]; 
ll dis[20]; 
int n; 

void bfs(int v){
    memset(vis,0,sizeof(vis)); 
    queue<int>q; 
    for(int i=1;i<=n;i++) dis[i] = 1e18; 
    dis[v] = 0; 
    q.push(v); 
    while(!q.empty()){
        int f =q.front(); q.pop(); if(vis[f]) continue;
        vis[f] = 1; 
        for(auto [ne,dd] : adj[f]) if(!vis[ne]) {
            q.push(ne); dis[ne] = dis[f] + dd; 
        }
    }
    rrep(i,n) dist[v][i] = dis[i]; 
}

mint p[20]; 
mint ncr[20][20]; 

ll k,l; 

void solve1(){
    ncr[0][0] = 1; 
    for(int i=1;i<20;i++){
        ncr[i][0] = ncr[i][i] = 1; 
        for(int j=1;j<i;j++) ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j]; 
    }
    rrep(i,n) bfs(i); 
    rrep(i,n) rrep(j,n){
        dbg(i,j,dist[i][j])
    }
    // k 개를 뽑는데 b 가 나올 확률 
    // b 가 또 돼야함 
    mint ans = 0; 
    p[0] = 0; 
    mint pp = (mint)1/n; 
    for(int i=1;i<=n;i++) {
        dbg(i)
        if(k<i) {
            p[i] = 0; continue; 
        }
        // i 개만 나올 확률
        p[i] = (i*pp).pow(k); 
        for(int j=i-1;j>0;j--){
            p[i] += ((j-i)%2 ? -1 : 1) * ncr[i][j] * (j*pp).pow(k); 
        }
    }
    dbg(l)
    for(int b=1;b<(1<<n);b++){
        bool dd = true; 
        rep(i,n) rep(j,n) if(i!=j){
            int bi = (b>>i)&1, bj = (b>>j)&1; 
            if(bi&&bj&&dist[i+1][j+1]>l) dd=false; 
        }
        if(dd) {
            ans += p[__builtin_popcount(b)];
            dbg(b)
        }
    }
    cout << ans.val();
}

// 

ll d[3010];
void dfs(int p, int v){
    d[v] = d[p] + 1; 
    
}


void solve2(){
    // 중심이 어느 점 i 
    // 중심이 어느 점 i 와 j 사이 
    

    // 중심이 어느 점 i 
    ll L = l/2; 

}


void solve(){
    cin>>n>>k>>l; 
    bool allc = true; 
    rep(i,n-1){
        int a,b,c; cin>>a>>b>>c; 
        adj[a].pb({b,c}); 
        adj[b].pb({a,c}); 
        if(c!=1) allc = false; 
    }
    l = l*2; 
    if(n<=14) {
        solve1(); return; 
    }
    if(allc && n<=3000){
        solve2(); return; 
    }

}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}