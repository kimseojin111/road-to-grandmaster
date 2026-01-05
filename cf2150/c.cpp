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
ll v[N],a[N],b[N],ra[N]; 
ll bb[N], vv[N]; 
int rb[N]; 

#include <atcoder/modint>
#include <atcoder/lazysegtree>

using namespace atcoder; 

using S = ll; 

S op(S l, S r){
    return max(l,r); 
}

S e(){
    return -1e18; 
}
struct F {
    ll add; ll mx; 
}; 

S mapping(F a, S s){
    return max(a.mx,s+a.add); 
}

// l(r(x)) 
F composition(F l, F r){
    return {l.add+r.add,max(l.mx,r.mx+l.add)}; 
}

const ll inf = 1e18;
F id() {
    return {0,-inf}; 
}

// lazy_segtree<S,op,e,F,mapping,composition,id> seg(int n); 
// lazy_segtree<S,op,e,F,mapping,composition,id> seg(vector<S> v); 
// https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html


void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>v[i]; 
    rrep(i,n) cin>>a[i];
    rrep(i,n) cin>>b[i]; 
    rrep(i,n) ra[a[i]] = i; 
    rrep(i,n){
        //dbg(ra[i])
        bb[i] = ra[b[i]];
        vv[i] = v[a[i]];  
    }
    rrep(i,n){
        rb[bb[i]] = i; 
    }
    lazy_segtree<S,op,e,F,mapping,composition,id> seg(vector<ll>(n+1,0)); 
    rrep(i,n){
        dbg(bb[i],vv[i])
    }
    for(int i=1;i<=n;i++){
        
        int t = rb[i]; 
        seg.apply(0,t,{vv[i],-inf}); 
        ll dd = seg.get(t-1); 
        seg.apply(t,n+1,{0,dd}); 
    } 
    // dp[n][n] 을 구하자. 
    cout << seg.get(n) << "\n"; 
    //cout << ans << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}