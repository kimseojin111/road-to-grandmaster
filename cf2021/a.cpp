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

const ll inf = 2e18; 
void solve(){
    int n,m; cin>>n>>m; 
    vector<vector<ll>> a(n+1,vector<ll>(m+2,0)); 
    rrep(i,n) rrep(j,m) cin>>a[i][j]; 
    vector<vector<ll>> dp(n+1,vector<ll>(m+1)); 
    vector<vector<ll>> dpL(n+1,vector<ll>(m+1)); 
    vector<vector<ll>> dpR(n+1,vector<ll>(m+1)); 
    rrep(i,n){
        vector<ll> sum(m+1); 
        if(i==1){
            dpL[1][m-1] = a[1][m]; 
            for(int i=m-2;i>=0;i--) dpL[1][i] = max(0LL,dpL[1][i+1]) + a[1][i+1];
            dpR[1][1] = a[1][1]; 
            for(int j=2;j<=m;j++) dpR[1][j] = a[1][j] + max(0LL,dpR[1][j-1]); 
            rrep(j,m-1) dp[1][j] = max(dpL[1][j],dpR[1][j]); 
            continue; 
        }
        rrep(j,m) sum[j] = sum[j-1]+a[i][j]; 
        vector<ll> sfM(m+1),pfm(m+1); 
        pfm[1] = sum[0]; 
        for(int p=2;p<=m-1;p++) pfm[p] = min(pfm[p-1],sum[p-1]); 
        sfM[m-1] = sum[m]; 
        for(int p=m-2;p>=1;p--) sfM[p] = max(sfM[p+1],sum[p+1]); 
        ll mx = -inf; 
        for(int l=m-2;l>=0;l--){
            mx = max(mx,dp[i-1][l+1]+sfM[l+1]); 
            dpL[i][l] = mx-sum[l]; 
        }
        mx = -inf; 
        for(int r=2;r<=m;r++){
            mx = max(mx,dp[i-1][r-1]-pfm[r-1]); 
            dpR[i][r] = mx+sum[r]; 
        }
        for(int j=1;j<=m-1;j++) {
            dp[i][j] = max(dpL[i][j],dpR[i][j]); 
            dbg(i,j,dpL[i][j],dpR[i][j])
        }
    }
    ll mx = -inf; 
    for(int j=1;j<=m-1;j++) mx=max(mx,dp[n][j]); 
    mx = max(mx,dpL[n][0]); 
    mx = max(mx,dpR[n][m]); 
    cout << mx << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}