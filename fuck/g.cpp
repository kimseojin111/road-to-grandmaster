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
ll dp[N],dpv[N]; 
int l[N],r[N]; 

void init(int n){
    rrep(i,n){
        dp[i] = dpv[i] = 0; 
        adj[i].clear(); 
    }
}

void dfs(int v, int p){
    dbg(v,p)
    int c = 0; 
    ll st = 0; 
    for(auto ne : adj[v]) if(ne!=p){
        dfs(ne,v); 
        st = max(st,dpv[ne]); 
        dp[v] += dp[ne];
        c++;  
    }
    dbg(v,dp[v])
    if(c==0){
        dpv[v] = l[v]; return;  
    }
    if(st<=l[v]) {
        dpv[v] = l[v]; 
    }
    else if(st<=r[v]) {
        dpv[v] = st; 
    }
    else if(st>r[v]) dpv[v] = r[v]; 
    for(auto ne : adj[v]) if(ne!=p){
        dp[v] += max(0LL,dpv[ne]-dpv[v]); 
    }
    dbg(v,dp[v],dpv[v],"wtf")
    if(v==1) dp[v] += dpv[v]; 
    return;
}

void solve(){
    int n; cin>>n; 
    init(n); 
    rrep(i,n) cin>>l[i]>>r[i]; 
    if(n==1){
        cout << l[1] << "\n"; return;
    }
    rep(i,n-1){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    dfs(1,1); 
    cout << dp[1] << "\n"; 
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}