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

const int N = 300010; 
int p[N],in[N],out[N]; 
int a[N];
int tmp[N];  
vector<int> adj[N], oka[N]; 
void init(int n){
    rrep(i,n) adj[i].clear(), oka[i].clear(); 
    rrep(i,n) tmp[i] = 0,in[i]=out[i]=0; 
}
ll ans = 0; 
int pv=0; 
void dfs(int v){
    int prv = 0; 
    in[v] = ++pv; 
    if(tmp[a[v]]) {
        dbg(v,a[v],'?')
        oka[tmp[a[v]]].pb(v); prv = tmp[a[v]]; 
    }
    tmp[a[v]] = v; 
    for(int ne : adj[v]) dfs(ne); 
    tmp[a[v]] = prv; 
    out[v] = pv; 
}

#include <atcoder/lazysegtree>
using S = int; 

S op(S l, S r){
    return max(l,r); 
}

S e(){
    return 0; 
}

using F = int; 

S mapping(F a, S s){
    return s+a; 
}

// l(r(x)) 
F composition(F l, F r){
    return l+r; 
}

F id() {
    return 0; 
}

atcoder::lazy_segtree<S,op,e,F,mapping,composition,id> seg(N); 

// lazy_segtree<S,op,e,F,mapping,composition,id> seg(int n); 
// lazy_segtree<S,op,e,F,mapping,composition,id> seg(vector<S> v); 
// https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html

void dfss(int v){
    dbg(v)
    for(int ne : adj[v]) dfss(ne); 
    for(auto x : oka[v]){
        dbg(x,in[x],out[x])
        seg.apply(in[x],out[x]+1,-1); 
    }
    seg.apply(in[v],out[v]+1,1); 
    vector<int> shit; 
    for(int ne : adj[v]) shit.pb(seg.prod(in[ne],out[ne]+1)); 
    sort(all(shit),[](auto p, auto q){
        return p>q; 
    }); 
    if(shit.empty()) return; 
    if(shit.size()==1) ans = max(ans, (ll)shit[0]); 
    else ans = max(ans,1LL*shit[0]*shit[1]); 
}

void solve(){
    int n; cin>>n; 
    init(n); 
    p[1] = 1; 
    for(int i=2;i<=n;i++){
        cin>>p[i]; adj[p[i]].pb(i);  
    }pv=0; 
    rrep(i,n) cin>>a[i]; 
    dfs(1); 
    ans = 0; 
    rrep(i,n) seg.set(i,0); 
    //dfsss(1); 
    dfss(1); 
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