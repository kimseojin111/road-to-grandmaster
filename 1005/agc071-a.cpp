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

const int N = 510; 
ll dp[N][N]; 
ll a[N]; 
ll p[N]; 
void chmax(ll&x, ll y) {
    x = min(x,y); 
}
void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>a[i]; 
    rrep(i,n) p[i] = p[i-1] ^ a[i]; 
    rrep(i,n) dp[i][i] = a[i]; 

    for(int dif=1;dif<=n-1;dif++) {
        for(int i=1;i+dif<=n;i++){
            int j = i+dif; 
            dp[i][j] = 2e18; 
            if((j-i+1)%2==0){
                for(int k=i;k<j;k++){
                    // [I,K] [k+1,j]
                    if((k-i+1)%2==0){
                        // 짝, 짝 
                        chmax(dp[i][j],dp[i][k]+dp[k+1][j]); 
                    } else {
                        // 홀 홀 
                        ll left = p[k]^p[i-1], right = p[j]^p[k]; 
                        // left   right     ->    left^right    left^right 
                        chmax(dp[i][j],dp[i][k]+dp[k+1][j]-left-right+(left^right)+(left^right)); 
                    }
                }
            } else {
                for(int k=i;k<j;k++){
                    // [I,K] [k+1,j]
                    ll left = p[k]^p[i-1], right = p[j]^p[k]; 
                    if((k-i+1)%2==0){
                        // 짝, 홀 
                        chmax(dp[i][j],dp[i][k]+dp[k+1][j]-right+(left^right)); 
                    } else {
                        // 홀 홀 
                        ll left = p[k]^p[i-1], right = p[j]^p[k]; 
                        // left   right     ->    left^right    left^right 
                        chmax(dp[i][j],dp[i][k]+dp[k+1][j]-left+(left^right)); 
                    }
                }
            }
            //dbg(i,j,dp[i][j])
        }
    }
    cout << dp[1][n];
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}