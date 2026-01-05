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
int p[N]; 
int s[N]; 
map<int,ll> dp[N]; 

void init(int n){
    rrep(i,n){
        adj[i].clear(); dp[i].clear();  
    }
}

ll dfs(int v, int k){
    dbg(v,k)
    if(dp[v].find(k)!=dp[v].end()) return dp[v][k]; 
    if(adj[v].empty()){
        return dp[v][k] = 1LL * s[v] * k; 
    }
    int sz = adj[v].size(); 
    int base = k/sz; 
    int remainder = k%sz; 
    dp[v][k] = 1LL * s[v] * k; 
    if(remainder==0){
        for(auto ne : adj[v]) dp[v][k] += dfs(ne,base); 
        return dp[v][k]; 
    } else {
        vector<ll> pq; 
        for(auto ne : adj[v]){
            dp[v][k] += dfs(ne,base); 
            pq.pb(dfs(ne,base+1)-dfs(ne,base)); 
        }
        sort(all(pq),[](ll a, ll b){ 
            return a>b; 
        }); 
        rep(_,remainder) dp[v][k] += pq[_]; 
    }
    return dp[v][k]; 
}

void solve(){
    int n,k; cin>>n>>k; 
    init(n); 
    p[1] = 1; 
    for(int i=2;i<=n;i++){
        cin>>p[i]; 
        adj[p[i]].pb(i); 
    }
    rrep(i,n) cin>>s[i]; 
    cout << dfs(1,k) << "\n"; 
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}