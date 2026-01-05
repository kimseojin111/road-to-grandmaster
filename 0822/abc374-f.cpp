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

const int N = 120; 
ll a[N]; 
ll pa[N];
ll dp[N][N*120]; 
ll dpm[N][N*120]; 
ll n,k,x; 

void solve(){
    cin>>n>>k>>x; 
    rrep(i,n) cin>>a[i]; 
    vector<ll> tmp; 
    tmp.pb(0); 
    rrep(i,n){
        for(int j=0;j<=101;j++) tmp.pb(a[i]+j*x); 
        pa[i] = pa[i-1] + a[i]; 
    }
    sort(all(tmp)); 
    tmp.erase(unique(all(tmp)),tmp.end()); 
    int sz = tmp.size(); 
    rrep(i,n) rep(j,sz) dp[i][j] = 2e18; 
    rrep(i,n) {
        rep(_,sz){
            ll T = tmp[_]; if(T<a[i]) continue; 
            for(int j=max(i-k,0LL);j<i;j++){
                // tmp[l] >= a[j] && tmp[l] <= tmp[_] - x 
                if(j==0){
                    dp[i][_] = min(dp[i][_],T*(i-j) - (pa[i]-pa[j])); 
                    continue; 
                }
                int l = upper_bound(all(tmp),T-x) - tmp.begin(); 
                l--; 
                if(l<0) continue; 
                dp[i][_] = min(dp[i][_],dpm[j][l] + T*(i-j) - (pa[i]-pa[j])); 
                if(i==5&&T==12){
                    dbg(j,l,tmp[l],dpm[j][l] + T*(i-j) - (pa[i]-pa[j]))
                }
            }
            //dbg(i,T,dp[i][_])
        }
        dpm[i][0] = 2e18;
        for(int j=1;j<sz;j++) {
            dpm[i][j] = min(dp[i][j],dpm[i][j-1]); 
            if(dp[i][j]==69279374648LL){
                dbg(i,j,"????")
            }
        }
    }
    ll ans = 2e18; 
    rep(_,sz) ans = min(ans,dp[n][_]); 
    cout << ans ; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}