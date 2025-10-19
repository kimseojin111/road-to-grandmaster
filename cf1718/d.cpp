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

#include <atcoder/segtree>
using namespace atcoder; 

// {최대, idx} 
using S = pair<int,int>;
S op(S a, S b){
    if(a.ff>b.ff) return a; 
    return b; 
}

S id() {return {-1,0};} 

vector<int> p; 
vector<int> a; 
vector<int> to; 

bool build(int s, int e, segtree<S,op,id>& P, segtree<S,op,id>& A){
    if(s>e) return true; 
    auto [val,idx] = P.prod(s,e+1); 
    auto [tt,dd] = A.prod(s,e+1); 
    //dbg(s,e,val,idx,tt,dd)
    if(a[idx]!=0){
        if(a[idx]!=tt) return false; 
        bool re = true; 
        re &= build(s,idx-1,P,A); 
        re &= build(idx+1,e,P,A); 
        return re; 
    }
    to.pb(tt); 
    bool re = true; 
    re &= build(s,idx-1,P,A); 
    re &= build(idx+1,e,P,A); 
    return re; 
}

void solve(){
    int n,q; cin>>n>>q; 
    int k = 0; 
    p.clear(); a.clear(); 
    p.resize(n+1); a.resize(n+1); 
    to.clear(); 
    rrep(i,n) cin>>p[i]; 
    rrep(i,n) {
        cin>>a[i];
        if(a[i]==0)k++; 
    } 
    segtree<S,op,id> P(n+1); 
    segtree<S,op,id> A(n+1); 
    rrep(i,n) P.set(i,{p[i],i}); 
    rrep(i,n) A.set(i,{a[i],i}); 
    bool flag = build(1,n,P,A); 
    dbg(to)
    vector<int> f; 
    rep(i,k-1){
        int x;cin>>x; f.pb(x); 
    }
    int L = 0,R=1e9; 
    sort(all(to)); 
    if(flag){
        auto chk = [&](int x){
            auto ff = f; 
            ff.pb(x); 
            sort(all(ff)); 
            assert(to.size()==ff.size()); 
            rep(i,to.size()) if(ff[i]<=to[i]) return false; 
            return true; 
        }; 

    }
    while(q--){
        int x; cin>>x; 
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}