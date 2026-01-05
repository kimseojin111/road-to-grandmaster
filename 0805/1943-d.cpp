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
using mint = modint; 
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


mint dp[500][500]; 
mint ndp1[500][500]; 
mint ndp2[500][500]; 

void solve(){
    int n,k,p; cin>>n>>k>>p; 
    mint::set_mod(p); 
    for(int i=0;i<=k;i++) for(int j=0;j<=k;j++) dp[i][j] = 0; 
    dp[0][0]=1; 
    for(int s=1;s<=n;s++){
        for(int i=0;i<=k;i++) for(int j=0;j<=k;j++) ndp1[i][j] = ndp2[i][j] = 0; 
        for(int i=0;i<=k;i++) for(int j=0;j<=k-i;j++) {
            ndp1[0][i]+=dp[i][j]; ndp1[0][i+j+1]-=dp[i][j]; 
            ndp2[1][i+j]+=dp[i][j]; ndp2[k-i-j+1][i+j]-=dp[i][j]; 
        }
        for(int i=0;i<=k;i++) for(int j=0;j<=k;j++){
            if(j>0) ndp1[i][j] += ndp1[i][j-1]; 
            if(i>0) ndp2[i][j] += ndp2[i-1][j]; 
        }
        for(int i=0;i<=k;i++) for(int j=0;j<=k;j++) dp[i][j] = ndp1[i][j] + ndp2[i][j]; 
    }
    mint ans = 0; for(int i=0;i<=k;i++) ans += dp[0][i]; 
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}