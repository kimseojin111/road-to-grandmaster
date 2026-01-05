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

#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace atcoder; 

using S = modint998244353; 
using mint = modint998244353; 
S op(S a, S b){
    return a+b; 
}
S e() {
    return (S)0; 
}

using F = mint; 
F composition(F l, F r){
    return l*r; 
}
S mapping(F l, S r){
    return l*r; 
}
F id() {
    return (F)1; 
}

int x[200010]; 

void solve(){
    int n; cin>>n; rrep(i,n) cin>>x[i]; 
    auto get = [&](vector<pair<int,int>> v) {
        mint re = 0; 
        sort(all(v),[](auto p, auto q){
            if(p.ss!=q.ss) return p.ss<q.ss; 
            return p.ff<q.ff; 
        }); 
       // dbg(v)
        int p = 0;
        lazy_segtree<S,op,e,F,mapping,composition,id> seg(vector<mint>(n,1));  
        rrep(i,n-1){
            while(p<v.size()&&v[p].ss==i){
                int x = v[p].ff; if(x>=1&&x<=n-1){
          //          dbg(x)
                    seg.apply(x,n,(mint)2); 
                }
                p++; 
            }
            re = re + seg.prod(1,n); 
           // dbg(seg.prod(1,n).val())
        }
        return re; 
    }; 
    mint ans = 0; 
    mint two = 2; 
    ans += two.pow(n)*(n-1)*(n-1); 
    ans -= (two.pow(n)-2)*4*(n-1);

    rep(u,2) rep(w,2){
        vector<pair<int,int>> v; 
        rrep(i,n) {
            int p = u==1 ? n+1-i:i; 
            int y = w==1 ? n+1-x[i]:x[i]; 
            v.pb({p,y}); 
        }
        dbg(get(v).val())
        ans += get(v); 
    }
    ans -= (mint)(n-1)*(n-1);
    cout << ans.val(); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}