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

const int N = 100100; 
ll a[N],b[N]; 
vector<pair<int,ll>> adj[N]; 

ll dist[22][22]; 

bool vis[22]; 
ll dis[22]; 
int n; 

void bfs(int v){
    dbg(v)
    memset(vis,0,sizeof(vis)); 
    queue<int>q; 
    for(int i=0;i<=n;i++) dis[i] = 1e18; 
    dis[v] = 0; 
    q.push(v); 
    while(!q.empty()){
        int f =q.front(); q.pop(); if(vis[f]) continue;
        vis[f] = 1; 
        
        for(auto [ne,dd] : adj[f]) if(!vis[ne]) {
            q.push(ne); dis[ne] = dis[f] + dd; 
        }
    }
    rep(i,n) dist[v][i] = dis[i]; 
}

void solve(){
    dbg('?')
    cin>>n; 
    rep(i,n) cin>>a[i]>>b[i]; 
    rep(i,n-1){
        ll a,b,c; cin>>a>>b>>c; 
        dbg(a,b)
        a--; b--; 
        adj[a].pb({b,c}); adj[b].pb({a,c}); 
    }
    dbg("@@@")
    if(n>20) {
        cout << 0 << endl; return; 
    }
    dbg(n)
    rep(i,n) bfs(i); 
    ll ans = 2e18; 
    for(int bi=1;bi<(1<<n);bi++){
        dbg(bi)
        ll tmp = 0; 
        rep(i,n) if((bi>>i)&1) tmp += a[i]; 
        ll dd = 0; 
        rep(i,n) if((bi>>i)&1) {
            rep(j,n) if(dist[i][j]<=b[i]) dd |= (1<<j); 
        }
        if(dd==(1<<n)-1) ans = min(ans,tmp); 
    }
    cout << ans; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}