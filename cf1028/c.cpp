//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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
//#define double long double
double dp[4010][402][22]; 
double dpp[4010][8011]; 
int a[4111]; 

void solve(){
    int n,m,pp; cin>>n>>m>>pp; 
    double p = (double)pp/100; 
    //for(int i=0;i<=m;i++) for(int k=0;k<=n;k++) for(int j=0;j<=401;j++) dp[i][j][k] = 0; 
    dp[0][0][0] = 1; 
    for(int s=1;s<=m;s++){
        dp[s][0][0] = 1; 
        for(int x=0;x<=400;x++) for(int h=0;h<n;h++){
            if(x==0&&h==0) continue; 
            dp[s][x][h] = p*(x==0 ? dp[s-1][0][h] : dp[s-1][x-1][h]); 
            if(h>0) dp[s][x][h] += (1-p)*dp[s-1][x][h-1]; 
            else dp[s][x][h] += (1-p)*max(dp[s-1][x-1][n-1],dp[s-1][x][h]); 
        }
    }
    rrep(i,n) {
        cin>>a[i]; a[i]--; 
    }
    int x = 1e9,h=0; 
    rrep(i,n){
        x = min(x,a[i]); 
    }
    rrep(i,n) h += (a[i]-x); 
    dbg(h)
    cout << fixed; cout.precision(9); 
    if(h==0) cout << dp[m][x][0] << "\n";
    else if(h>m){
        cout << 0 << "\n"; 
    } 
    else {
        double ans = 0; 
        //for(int i=0;i<=m;i++) for(int j=0;j<=x;j++) dpp[i][j] = 0; 
        dpp[0][0] = 1; 
        for(int i=1;i<=m;i++) {
            for(int j=0;j<=h;j++){
                if(j==0) dpp[i][j] = dpp[i-1][j]*(p); 
                else if(j==h) dpp[i][j] = dpp[i-1][j-1]*(1-p); 
                else dpp[i][j] = p*dpp[i-1][j] + (1-p)*dpp[i-1][j-1]; 
            }
            ans = ans + dpp[i][h]*dp[m-i][max(0,x-(i-h))][0]; 
        }
        cout << ans << "\n";
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