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

mint dp[110][110][14][14]; 
// * -> 13
const int lim = 13; 
int s[110]; 
mint fac[110]; 

mint ncr[110][110]; 


void solve(){
    int n; cin>>n; 
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) rep(k,14) rep(l,14) dp[i][j][k][l] = 0; 
    rrep(i,n) cin>>s[i]; 
    for(int i=0;i<=n;i++) {
        for(int a : {0,13}) for(int b : {0,13}) dp[i+1][i][a][b] = 1; 
    }
    rrep(i,n){
        if(s[i]>13) {
            cout << 0 << "\n"; return; 
        }
    }
    for(int j=1;j<=n;j++){
        for(int i=j;i>=1;i--){
            for(int a=0;a<=lim;a++) for(int b=0;b<=lim;b++) {
                if(i==1&&a!=lim) continue; 
                if(j==n&&b!=lim) continue; 
                for(int k=i;k<=j;k++)  {
                    int na = (k <= (i+j)/2); 
                    int nb = 1-na; 
                    if(i==1) nb=1; 
                    if(j==n) na=1;
                    if(na&&a==0) continue; 
                    if(nb&&b==0) continue; 
                    int aa = a==lim ? lim : a-na; 
                    int bb = b==lim ? lim : b-nb; 
                    // dp[i][j][a][b] += dp[i][k-1][aa][?] * dp[k+1][j][?][bb]; 
                    if(s[k]==-1) dp[i][j][a][b] += dp[i][k-1][aa][lim] * dp[k+1][j][lim][bb] * ncr[j-i][k-i]; 
                    else {
                        for(int x=0;x<=s[k];x++) {
                            dp[i][j][a][b] += dp[i][k-1][aa][x] * dp[k+1][j][s[k]-x][bb] * ncr[j-i][k-i]; 
                        }
                    }
            }
        }
    }
}
    cout << dp[1][n][lim][lim].val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   fac[0] = 1; 
   for(int i=1;i<110;i++) fac[i] = fac[i-1]*i; 
   for(int i=0;i<110;i++) for(int j=0;j<=i;j++) {
    ncr[i][j] = fac[i]/fac[i-j]/fac[j]; 
   }
   while(t--) solve(); 
   return 0;
}