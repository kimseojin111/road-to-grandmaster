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


#include <atcoder/modint>
#include <atcoder/lazysegtree>

using namespace atcoder; 

using S = int; 
S op(S l, S r){
    return min(l,r); 
}

S e(){
    return 1e9; 
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

// lazy_segtree<S,op,e,F,mapping,composition,id> seg(int n); 
// lazy_segtree<S,op,e,F,mapping,composition,id> seg(vector<S> v); 
// https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html


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

void solve(){
    int n; cin>>n; 
    ll ans = 0; 
    vector<pair<int,int>> tmp; 
    tmp.pb({0,0}); 
    vector<int> v(n+1); rrep(i,n) {
        cin>>v[i]; tmp.pb({v[i],i}); 
    }
    fen FF(n+100); 
    vector<int> sss(n+2,n+10); 
    lazy_segtree<S,op,e,F,mapping,composition,id> seg(sss); 
    set<int> in; in.insert(0); 
    seg.set(0,0); 
    sort(all(tmp)); 
    rrep(i,n){
        ans += v[i]; 
        auto pos = lower_bound(all(tmp),pair{v[i],i}) - tmp.begin(); 
        auto it = *prev(in.lower_bound(pos)); 
        in.insert(pos); 
        int k = tmp[it].ff - seg.get(it); 
        ans -= k; 
        FF.upd(pos,1); 
        seg.set(pos,tmp[pos].ff-k); 
        auto g = [&](S s){
            return s>0; 
        }; 
        int r = seg.max_right(pos,g); 
        dbg(pos,r)
        ans -= FF.qry(pos,r-1); 
        seg.apply(pos,r,-1); 
        cout<<ans<<" "; 
    }   
    cout<<"\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}