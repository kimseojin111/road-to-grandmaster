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

const int N = 520; 
mint dp[N][N]; 
vector<array<int,2>> chk[N]; // <l,r,x> 에 대해서 chk[r]  에 {l,x} pb 
int lm[N]; // 고정된 x 에서 최대의 l 
mint fac[N*2]; 
mint rfac[N*2]; 
mint ncr(int n, int r){
    if(r<0||r>n) return (mint)0; 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

void solve(){
    int n,m; cin>>n>>m; 
    rep(i,m){
        int l,r,x;cin>>l>>r>>x; chk[r].pb({l,x}); 
    }
    rrep(i,n+1) dp[i][i-1] = 1; 
    rrep(i,n){
        for(auto [l,x]:chk[i]) lm[x] = max(lm[x],l); 
        for(int j=i;j>0;j--){
            for(int k=j;k<=i;k++){
                if(j<=lm[k]) continue; 
                dp[j][i] += dp[j][k-1]*dp[k+1][i] * ncr(i-j,k-j); 
            }
           // dbg(j,i,dp[j][i])
        }
    }
    cout << dp[1][n].val();
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   fac[0] = rfac[0] = 1; 
   for(int i=1;i<N*2;i++) fac[i] = fac[i-1]*i, rfac[i] = rfac[i-1]/i; 
   //cin >> t;
   while(t--) solve(); 
   return 0;
}