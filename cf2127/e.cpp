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

const int N = 200010; 
vector<int> adj[N]; 

int par[N]; 
ll w[N]; 
int c[N]; 
ll ans = 0; 
set<int> dp[N]; 
void init(int n){
    rrep(i,n) {
        adj[i].clear(); dp[i].clear(); 
    }
}

void dfs(int v, int p){
    int cc = 0; 
    for(auto ne : adj[v]) if(ne!=p) {
        cc++; 
    }
    if(cc==0) {
        if(c[v]!=0) dp[v].insert(c[v]); 
        return; 
    }
    set<int> g; 
    for(auto ne : adj[v]) if(ne!=p){
        dfs(ne,v); 
        if(dp[ne].size()>dp[v].size()) swap(dp[v],dp[ne]); 
        for(auto x : dp[ne]) {
            if(dp[v].count(x)) g.insert(x); 
            else dp[v].insert(x); 
        }
    }
    if(g.size()>1) {
        ans += w[v]; if(c[v]==0) {
            c[v] = *g.begin(); 
        }
    } else if(g.size()==1){
        int t = *g.begin(); 
        if(c[v]!=0&&c[v]!=t) ans += w[v]; 
        if(c[v]==0) c[v] = *g.begin(); 
    } else {
        if(dp[v].size()&&c[v]==0) c[v] = *(dp[v].begin()); 
    }
    if(c[v]!=0) dp[v].insert(c[v]); 
}

void shit(int v, int p){
    for(auto ne : adj[v]) if(ne!=p) {
        if(c[ne]==0) {
            c[ne] = c[v]; 
        }
        shit(ne,v); 
    }
}

void solve(){
    int n,k; cin>>n>>k; 
    init(n); 
    rrep(i,n) cin>>w[i]; 
    rrep(i,n) cin>>c[i]; 
    ans = 0; 
    rep(i,n-1){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    dfs(1,1); 
    cout << ans << "\n";
    if(c[1]==0){
        rrep(i,n) c[i] = 1; 
    }
    else {
        shit(1,1); 
    }
    rrep(i,n){
        cout << c[i] << " \n"[i==n];
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}