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

mint dpL[2010][2010];
mint dpR[2010][2010]; 
// dpL[i][k] = 1~i 까지 최소가 j 
// dpR[i][k] = i~n 까지 최대가 j  
mint tmp[2010]; 
int a[2010]; 
int n,m; 
void solve(){
    cin>>n>>m; 
    rrep(i,n) cin>>a[i]; 
    if(a[1]==-1) for(int j=1;j<=m;j++) dpL[1][j] = 1;
    else dpL[1][a[1]] = 1; 
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m;j++) tmp[j] = tmp[j-1] + dpL[i-1][j]; 
        if(a[i]==-1){
            for(int j=1;j<=m;j++){
                // 내가 j 혹은 j보다 크면?
                dpL[i][j] = tmp[m] - tmp[j-1] + dpL[i-1][j]*(m-j); 
                if(j==1){
                    dbg(tmp[m]-tmp[j-1])
                }
            }
        }
        else {
            for(int j=1;j<=m;j++){
                if(j<a[i]) dpL[i][j] = dpL[i-1][j]; 
                else if(j==a[i]) dpL[i][j] = tmp[m] - tmp[j-1]; 
            }
        }
        rrep(j,m){
            dbg(i,j,dpL[i][j])
        }
    }
    if(a[n]==-1) for(int j=1;j<=m;j++) dpR[n][j] = 1; 
    else dpR[n][a[n]] = 1; 
    for(int i=n-1;i>=0;i--){
        for(int j=1;j<=m;j++) tmp[j] = tmp[j-1] + dpR[i+1][j]; 
        if(a[i]==-1){
            for(int j=1;j<=m;j++) {
                // 내가 j  혹은 j 미만
                dpR[i][j] = tmp[j] + (j-1)*dpR[i+1][j]; 
            }
        }
        else {
            for(int j=1;j<=m;j++){
                if(j>a[i]) dpR[i][j] = dpR[i+1][j]; 
                else if(j==a[i]) dpR[i][j] = tmp[j]; 
            }
        }
    }
    int cnt = 0; rrep(i,n) if(a[i]==-1) cnt++; 
    mint f = m; 
    mint ans = f.pow(cnt);
    dbg(ans)
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++) tmp[j] = tmp[j-1] + dpR[i+1][j]; 
        for(int j=1;j<=m;j++) {
            ans += dpL[i][j] * tmp[j-1]; 
            dbg(j,dpL[i][j])
        }
    }
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