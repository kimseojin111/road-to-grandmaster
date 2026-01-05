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

const int N = 5010; 
int p[N]; 
ll ans[N]; 
vector<ll> dp[N]; 
vector<int> child[N]; 
ll a[N]; 
const ll inf = 2e18; 

void init(int n){
    rrep(i,n){
        p[i] = 0; 
        dp[i].clear(); child[i].clear(); 
        ans[i] = 0; 
    }
}

void dfs(int v){
    if(child[v].empty()){
        dp[v].pb(inf); 
        return; 
    }
    dp[v].pb(0); 
    ll dif = a[v]; 
    for(auto ne : child[v]){
        dfs(ne); 
        dif -= a[ne]; 
        ans[v] += ans[ne]; 
        for(int i=0;i<dp[ne].size();i++){
            if(i+1<dp[v].size()) {
                if(dp[v][i+1]<inf) dp[v][i+1] += dp[ne][i];
            }
            else {
                dp[v].pb(dp[ne][i]);     
            }
        }
    }
    if(dif<=0){
        dp[v][0] = -dif; 
    } else {
        for(int i=1;i<dp[v].size();i++){
            if(dif>0){
                ll x = min(dif,dp[v][i]); 
                dif -= x; 
                ans[v] += x*i; 
                if(dp[v][i]==inf) break; 
                else dp[v][i] -= x; 
            }
        }
        assert(dif==0);
    }
}

void solve(){
    int n; cin>>n; 
    init(n); 
    rrep(i,n) cin>>a[i]; 
    for(int i=2;i<=n;i++) {
        cin>>p[i]; child[p[i]].pb(i); 
    }
    p[1] = 1; 
    dfs(1); 
    cout << ans[1] << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}