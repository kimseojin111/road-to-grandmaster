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

// initial degree 1 -> go for it 
// other leaves must not be directly connected 
// so the leaf must be subset of independent set 
// and every independent set can be constructed as leaves 
// jsut choosing non leaf as root recursively 
// go for dp 

// dp[v][0][1] maximum independent set of v's subtree if v is chosen
// dp[v][0][0] maximum independent set of v's subtree if v is not chosen. 
// dp[v][1][1] maximum independent set of (v's subtree)^c if parent is chosen
// dp[v][1][0] maximum independent set of (v's subtree)^c if parent is not chosen. 

const int N = 200010;
int dp[N][2][2]; 
vector<int> adj[N]; 
int par[N]; 
void init(int n){
    rrep(i,n) adj[i].clear(); 
}

void dfs(int v, int p){
    int c = 0; 
    par[v] = p; 
    for(auto ne : adj[v]) if(ne!=p){
        dfs(ne,v); c++; 
    }
    if(c==0){
        dp[v][0][0] = 0; 
        dp[v][0][1] = 1; return; 
    }
    dp[v][0][1] = 1; 
    dp[v][0][0] = 0; 
    for(auto ne : adj[v]) if(ne!=p) {
        dp[v][0][1] += dp[ne][0][0]; 
        dp[v][0][0] += max(dp[ne][0][0],dp[ne][0][1]); 
    }
    return; 
}

void dfss(int v, int p){ 
    if(v==p){
        dp[v][1][0] = dp[v][1][1] = 0; 
    }
    else {
        dp[v][1][0] = dp[p][0][0] - max(dp[v][0][0],dp[v][0][1]) + max(dp[p][1][0],dp[p][1][1]); 
        dp[v][1][1] = dp[p][0][1] - dp[v][0][0] + dp[p][1][0]; 
    }
    for(auto ne : adj[v])if(ne!=p){
        dfss(ne,v); 
    }
}

void solve(){
    int n; cin>>n; 
    init(n); 
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    dfs(1,1); 
    dfss(1,1); 
    int ans  = 0 ;
    rrep(i,n){
        int t = dp[i][0][0] + max(dp[i][1][0],dp[i][1][1]) + (adj[i].size()==1); 
        ans = max(ans,t); 
    }
    cout << ans << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}