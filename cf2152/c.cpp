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


struct S {
    int cnt[2];
    int first_[2];
    int last_[2];
    int ans[2];
};
struct F { bool flip; };

vector<int> tin, tout, euler_enter_node;

S op(const S& L, const S& R){
    if (L.cnt[0]==0 && L.cnt[1]==0) return R;
    if (R.cnt[0]==0 && R.cnt[1]==0) return L;
    S res = e_unit();
    for (int p=0;p<2;++p){
        res.cnt[p] = L.cnt[p] + R.cnt[p];
        if (L.cnt[p] > 0) res.first_[p] = L.first_[p];
        else res.first_[p] = R.first_[p];
        if (R.cnt[p] > 0) res.last_[p] = R.last_[p];
        else res.last_[p] = L.last_[p];
        res.ans[p] = L.ans[p] + R.ans[p];
        if (L.cnt[p] > 0 && R.cnt[p] > 0){
            int lastIdx  = L.last_[p];
            int firstIdx = R.first_[p];
            int u = euler_enter_node[lastIdx];
            if (firstIdx > tout[u]) res.ans[p] += 1;
        }
    }
    return res;
}
S e(){ S x{};
    for (int p=0;p<2;++p){
        x.cnt[p]=0;
        x.first_[p]=-1;
        x.last_[p]=-1;
        x.ans[p]=0;
    }
    return x; 
}

S mapping(F& f, const S& s){
    if (!f.flip) return s;
    S t = s;
    for (int k=0;k<2;++k){
        t.cnt[k]    = s.cnt[k^1];
        t.first_[k] = s.first_[k^1];
        t.last_[k]  = s.last_[k^1];
        t.ans[k]    = s.ans[k^1];
    }
    return t;
}
F composition(const F& fnew, const F& fold){ return F{ bool(fnew.flip ^ fold.flip) }; }
F id(){ return F{false}; }

void solve(){
    
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}