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
using mint = modint1000000007; 

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

const int N = 2100; 
mint dp[N][N]; 
mint ndp[N][N]; 
mint dp1[N][N]; 

struct BIT2D {
    int n, m;
    vector<vector<mint>> t;
    BIT2D(int n_=0, int m_=0){ init(n_, m_); }
    void init(int n_, int m_){
        n=n_; m=m_;
        t.assign(n+2, vector<mint>(m+2, mint(0)));
    }
    static inline int lowbit(int x){ return x & -x; }
    void add(int x, int y, mint v){
        for(int i=x+1; i<=n+1; i+=lowbit(i))
            for(int j=y+1; j<=m+1; j+=lowbit(j))
                t[i][j] += v;
    }
    mint sum(int x, int y) const {
        mint r = 0;
        for(int i=x+1; i>0; i-=lowbit(i))
            for(int j=y+1; j>0; j-=lowbit(j))
                r += t[i][j];
        return r;
    }
    void suffixRectAdd(int r, int c, mint v){
        add(r, c, v);
        add(n+1, c, -v);
        add(r, n+1, -v);
        add(n+1, n+1, v);
    }
};

void solve(){
    int n; cin >> n;
    BIT2D bit(n+1, n+1); 
    bit.suffixRectAdd(0, 0, mint(1));

    rep(aaaaa,n){
        int k; cin>>k; 
        for(int b=0; b<k; ++b){
            mint cur = bit.sum(k, b) - (b ? bit.sum(k, b-1) : mint(0));
            bit.suffixRectAdd(k, b, cur);
        }
        for(int a=k+1; a<=n; ++a){
            mint cur = bit.sum(a, k) - (a ? bit.sum(a-1, k) : mint(0));
            bit.suffixRectAdd(a, k, cur);
        }
    }
    cout << bit.sum(n, n).val() << '\n';
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}