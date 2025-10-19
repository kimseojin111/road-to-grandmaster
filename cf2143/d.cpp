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
    vector<vector<mint>> A, B, C, D; 

    BIT2D(int n_=0, int m_=0){ init(n_, m_); }
    void init(int n_, int m_){
        n = n_; m = m_;
        A.assign(n+2, vector<mint>(m+2, 0));
        B.assign(n+2, vector<mint>(m+2, 0));
        C.assign(n+2, vector<mint>(m+2, 0));
        D.assign(n+2, vector<mint>(m+2, 0));
    }
    static inline int lowbit(int x){ return x & -x; }

    void _add(vector<vector<mint>>& T, int x, int y, mint v){
        for(int i=x; i<=n+1; i+=lowbit(i))
            for(int j=y; j<=m+1; j+=lowbit(j))
                T[i][j] += v;
    }
    void rectAdd(int x, int y, mint v){
        int X = x+1, Y = y+1;
        _add(A, X, Y, v);
        _add(B, X, Y, v * (-mint) (Y-1));
        _add(C, X, Y, v * (-mint) (X-1));
        _add(D, X, Y, v * (mint) (X-1) * (mint) (Y-1));
    }
    mint _sum(const vector<vector<mint>>& T, int x, int y) const {
        mint r = 0;
        for(int i=x; i>0; i-=lowbit(i))
            for(int j=y; j>0; j-=lowbit(j))
                r += T[i][j];
        return r;
    }
    mint pointQuery(int x, int y) const {
        int X = x+1, Y = y+1;
        mint a = _sum(A, X, Y);
        mint b = _sum(B, X, Y);
        mint c = _sum(C, X, Y);
        mint d = _sum(D, X, Y);
        return a*(mint)X*(mint)Y + b*(mint)X + c*(mint)Y + d;
    }
};

void solve(){
    int n; cin>>n; 
    rep(i,n+1) rep(j,n+1) dp[i][j] = ndp[i][j] = dp1[i][j] = 0; 
    dp[0][0] = ndp[0][0] = 1; 
    rep(i,n+1) rep(j,n+1){
        dp1[i][j] = dp[i][j]; 
        if(i>0) dp1[i][j] += dp1[i-1][j]; 
        if(j>0) dp1[i][j] += dp1[i][j-1]; 
        if(i>0&&j>0) dp1[i][j] -= dp1[i-1][j-1]; 
    }
    rep(aaaaa,n){
        rep(i,n+1) rep(j,n+1) ndp[i][j] = dp[i][j]; 
        int k; cin>>k; 
        for(int b=k-1;b>=0;b--){
            ndp[k][b] += (dp1[k][b]-(b==0 ? 0 : dp1[k][b-1])); 
        }
        for(int a=k+1;a<=n;a++){
            ndp[a][k] += (dp1[a][k]-(a==0 ? 0 : dp1[a-1][k])); 
        }
        rep(i,n+1) rep(j,n+1) dp[i][j] = ndp[i][j]; 
        rep(i,n+1) rep(j,n+1){
            dp1[i][j] = dp[i][j]; 
            if(i>0) dp1[i][j] += dp1[i-1][j]; 
            if(j>0) dp1[i][j] += dp1[i][j-1]; 
            if(i>0&&j>0) dp1[i][j] -= dp1[i-1][j-1]; 
        }
        dbg(dp1[n][n])
    }   
    cout << dp1[n][n].val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}