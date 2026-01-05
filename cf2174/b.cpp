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

const ll inf = 2e18; 
void chmax(ll&x, ll y){
    x = max(x,y); return; 
}

const int K = 370; 
ll dp[K][K]; 
ll dpp[K][K]; 
ll l[K],r[K]; 
ll x[K]; 
int ra[K]; 

void solve(){
    int n,k; cin>>n>>k; 
    for(int i=0;i<=k+1;i++){
        for(int j=0;j<=k+1;j++) dp[i][j] = dpp[i][j] = -inf; 
        l[i]=r[i]=x[i] = 0; 
    }
    int mx=0,id=0; 
    int pv = 0; 
    ra[0] = 0; 
    rrep(i,n){
        int a; cin>>a; 
        if(a>mx){
            pv++; 
            l[pv] = r[pv-1]+1; 
            r[pv] = a; 
            mx = a; 
            x[pv] = i; 
            for(int j=l[pv];j<=r[pv];j++) ra[j] = pv; 
            dbg(pv,x[pv],l[pv],r[pv])
        }
    }
    dp[0][0] = 0; 
    ll ans = 0; 
    for(int mx=1;mx<=r[pv];mx++) for(int s=mx;s<=k;s++){
        int idx = ra[mx]; 
        for(int j=0;j<mx;j++) if(ra[j]!=idx) {
            chmax(dp[mx][s],dp[j][s-mx]+1LL*(n+1-x[idx])*mx - 1LL*(n+1-x[idx])*j);
            chmax(ans,dp[mx][s]); 
        }
    }
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