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


const int N = 200010; 
vector<int> adj[N]; 
int par[N]; 
int sz[N]; 
mint fac[N],rfac[N]; 
bool vis[N]; 
mint iv[N]; 

void init(int n){
    rrep(i,n){
        par[i] = sz[i] = 0; 
        vis[i] = 0; 
        adj[i].clear(); 
    }
}

void dfs(int v, int p) {
    sz[v] = 1; 
    for(auto ne : adj[v]) if(ne!=p) {
        par[ne] = v; 
        dfs(ne,v); 
        sz[v] += sz[ne]; 
    }
}

struct union_find {
    int n; vector<int> par; 
    vector<int> sz; 
    union_find(int n) : n(n) {
        par.resize(n+1); sz.resize(n+1);
        rrep(i,n) par[i] = i; 
        rrep(i,n) sz[i] = 1; 
    }
    int find(int x){
        return x==par[x] ? x : par[x]=find(par[x]); 
    }
    bool merge(int a, int b){
        a = find(a), b = find(b); 
        if(a==b) return false; 
        par[a] = b; 
        sz[b] += sz[a]; 
        return true; 
    }
}; 

void solve(){
    int n; cin>>n; 
    init(n); 
    rep(i,n-1){
        int a,b; cin>>a>>b; 
        adj[a].pb(b); adj[b].pb(a); 
    }
    par[1] = 1; 
    dfs(1,1); 
    union_find uf(n+1); 
    for(int i=2;i<=n;i++){
        if(sz[i]%2==1){
            uf.merge(i,par[i]); 
        }
    }
    vector<int> fuck; 
    int x = uf.find(1); 
    fuck.pb(uf.sz[x]); 
    vis[x] = 1; 
    rrep(i,n) {
        int x = uf.find(i); 
        if(!vis[x]) {
            vis[x] = 1; 
            fuck.pb(uf.sz[x]); 
        }
    }
    mint ans = 1; 
    if(fuck.size()==1){
        cout << 1 << "\n"; return; 
    }
    for(int i=1;i<fuck.size();i++) ans = ans * fuck[i] * fuck[i]; 
    mint sum = 0; 
    for(int i=1;i<fuck.size();i++) sum = sum + iv[fuck[i]]; 
    ans *= sum; 
    ans *= fuck[0]; 
    ans *= fac[fuck.size()-2]; 
    cout << ans.val() << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    iv[1] =1 ; 
    for(int i=2;i<N;i++){
        iv[i] = mint(1)/i; 
    }
    fac[0] = 1; 
    for(int i=1;i<N;i++) {
        fac[i] = fac[i-1] * i; 
    }
    while(t--) solve(); 
    return 0;
}