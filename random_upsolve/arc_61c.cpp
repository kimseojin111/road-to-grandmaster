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

const int N = 100010; 
vector<int> col[N]; 
vector<pair<int,int>> adj[N*100]; 
int dp[N*100]; 
bool vis[N*100]; 

void solve(){
    int n,m; // 점 (색,점) pair<int,int> 
    cin>>n>>m; 
    map<pair<int,int>,int> M; 
    int pv = 0; 
    auto get = [&](int c, int v){
        if(M.find({c,v})==M.end()){
            M[{c,v}] = pv++; 
        }
        return M[{c,v}]; 
    }; 
    while(m--){
        int p,q,c; cin>>p>>q>>c; 
        col[p].pb(c); col[q].pb(c); 
        int gp = get(c,p), gq = get(c,q); 
        adj[gp].pb({gq,0}); adj[gq].pb({gp,0}); 
    }
    dbg(12)
    rrep(i,n){
        sort(all(col[i])); col[i].erase(unique(all(col[i])),col[i].end()); 
        int ff = get(-2,i); 
        for(int j=0;j<(int)col[i].size();j++){
            int p = col[i][j];
            int gp = get(p,i), gq = ff;
            adj[gp].pb({gq,1}); adj[gq].pb({gp,1}); 
        }
    }
    int src = get(-1,1), dst = get(-1,n); 
    for(auto x : col[1]) {
        int p = get(x,1); adj[p].pb({src,0}); adj[src].pb({p,0}); 
    }
    for(auto x : col[n]){
        int p = get(x,n); adj[p].pb({dst,0}); adj[dst].pb({p,0}); 
    }
    for(int i=0;i<pv;i++) dp[i]=1e9; 
    deque<int> dq; 
    dq.pb(src); 
    dp[src] = 0; 
    dbg(get(5,6),get(1,6))
    while(!dq.empty()){
        int f = dq.front(); dq.pop_front(); if(vis[f]) continue; 
        vis[f] = 1; 
        for(auto [ne,dd]:adj[f]) if(dp[ne]>dp[f]+dd){
            dp[ne] = dp[f]+dd; 
            if(dd==0) dq.push_front(ne); else dq.push_back(ne); 
        }
    }
    if(!vis[dst]) cout << -1; 
    else cout << (dp[dst]/2+1); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}