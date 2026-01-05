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
using mint = modint998244353; 

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

// a[i] 에 대해서 a[j] > a[i], j<i 인 최대의 j -> l[j]
// a[i] 에 대해서 a[j] > a[i], j>i 인 최소의 j -> r[j]
//  l[i] <  l_i < r_i <= r[i]
//  or l_i == r_i   
// r[i] = l[i+1]   !!! 
// dp[i][j] = r[i] = j 
// dp[i][j] = sigma  l[i] < l_i < j  dp[i-1][l_i] 
// or dp[i][j] = dp[i-1][j] 
// dp[0][1] = 1 

const int N = 5010; 
mint dp[N][N]; 
mint ndp[N][N]; 

int a[N]; 

void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>a[i]; 
    a[0] = a[n+1] = 1e9; 
    dp[0][1] = 1; 
    for(int i=1;i<=n+1;i++) ndp[0][i] = 1; 
    for(int i=1;i<=n;i++){
        int j = i-1; 
        while(a[j]<=a[i]) j--; 
        int l = j; 
        j = i+1; 
        while(a[j]<=a[i]) j++; 
        int r = j; 
        dbg(i,l,r)
        for(int j=0;j<=n+1;j++){
            dp[i][j] = dp[i-1][j]; 
        }
        for(int j=l+1;j<=r;j++) dp[i][j] += (ndp[i-1][j-1]-ndp[i-1][l]); 
        for(int j=0;j<=n+1;j++) ndp[i][j] = dp[i][j]; 
        for(int j=1;j<=n+1;j++) ndp[i][j] += ndp[i][j-1]; 
    }
    cout << dp[n][n+1].val(); 
}

signed main() {
cin.tie(0)->ios::sync_with_stdio(0);
cout.tie(nullptr);
int t = 1;
//cin >> t;
while(t--) solve(); 
return 0;
}