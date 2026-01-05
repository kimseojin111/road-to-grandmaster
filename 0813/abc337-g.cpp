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
int in[N], out[N]; 
int pv; 
vector<int> adj[N]; 
int par[N]; 
vector<int> child[N]; 

void dfs(int v, int p){
    par[v] = p; 
    in[v] = ++pv; 
    for(int ne : adj[v]) if(ne!=p){
        child[v].pb(ne); 
        dfs(ne,v);  
    }
    out[v] = pv; 
    dbg(v,p,in[v],out[v])
}


struct fen{
    vector<ll> a; int n; 
    fen(int n) : n(n) {
        a.resize(n+1); 
    }
    void upd(int p, ll v){
        while(p<n){
            a[p]+=v; p+=p&-p; 
        }
    }
    ll qry(int p){
        ll re = 0; 
        while(p){
            re += a[p]; p-=p&-p; 
        }
        return re; 
    }
    ll qry(int l, int r){
        return qry(r) - qry(l-1); 
    }
};  

fen FE(N); 
#include <atcoder/lazysegtree>

using namespace atcoder; 

using S = ll; 
S op(S l, S r){
    return l+r; 
}
S e(){
    return 0; 
}
using F = ll; 
S mapping(F a, S s){
    if(a==0) return s; 
    return s+a; 
}

// l(r(x)) 
F composition(F l, F r){
    return l+r; 
}

F id() {
    return 0; 
}
int n; 
lazy_segtree<S,op,e,F,mapping,composition,id> ans(N+1); 
void shit(int i){
    for(int c : child[i]){
        int sz = FE.qry(in[c],out[c]); 
        if(sz){
            dbg(i,sz,c,in[c],out[c],"fuckkkk")
        }
        ans.apply(1,n+1,sz); 
        ans.apply(in[c],out[c]+1,-sz); 
    }
    int ot = FE.qry(1,n) - FE.qry(in[i],out[i]); 
    if(ot){
        dbg(i,ot,"???????",in[i],out[i])
    }
    ans.apply(in[i],out[i]+1,ot); 
    FE.upd(in[i],1); 
}

void solve(){
    cin>>n; 
    rep(i,n-1){
        int a,b; cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    dfs(1,1); 
    for(int i=1;i<=n;i++) {
        shit(i); 
    }
    rrep(i,n) cout << ans.get(in[i]) << " "; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}