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
int chk[N],par[N]; 
vector<int> adj[N]; 
ll dp[N],dp1[N]; 
ll s[N]; 

void dfs(int v, int k){
    chk[v] = k; 
    // k개 선택 최대 dp k+1개 선택 최대 dp1 
    int d = adj[v].size(); 
    if(d==0) {
        dp[v] = s[v]*k; 
        dp1[v] = dp[v] + s[v]; 
        return; 
    }
    int ne = k/d; 
    for(auto a : adj[v]) dfs(a,ne); 
    int r = k%d; 
    ll gl = 0; 
    vector<ll> tmp; 
    for(auto a : adj[v]) {
        gl+=dp[a]; tmp.pb(dp1[a]-dp[a]); 
    }
    sort(all(tmp),[](auto p, auto q){
        return p>q; 
    }); 
    dp[v] = gl; 
    rep(j,r) dp[v] += tmp[j]; 
    dp1[v] = dp[v] + tmp[r]; 
    dp[v] += s[v]*k; 
    dp1[v] += s[v]*(k+1); 
    dbg(v,k,dp[v],dp1[v])
    return; 
}

void solve(){
    int n,k; cin>>n>>k; 
    rrep(i,n){
        chk[i]=0; adj[i].clear(); dp[i]=dp1[i]=0; 
    }
    par[1] = 1; 
    for(int i=2;i<=n;i++){
        cin>>par[i]; adj[par[i]].pb(i); 
    }
    rrep(i,n) cin>>s[i]; 
    dfs(1,k); 
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