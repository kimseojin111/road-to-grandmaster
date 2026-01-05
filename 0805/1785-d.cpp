#include <bits/stdc++.h>
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


const int N = (1<<20)+100; 
mint fac[N],rfac[N]; 
mint ncr(int n, int r){
    if(n<0) return (mint)0; 
    if(r<0||r>n) return (mint)0; 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

void init(){
    fac[0]=rfac[0]=1;
    for(int i=1;i<N;i++) fac[i]=i*fac[i-1],rfac[i]=rfac[i-1]/i; 
}

void solve(){
    int n; cin>>n; 
    if(n==1){
        cout << "0\n2"; return; 
    }
    int sz = (1<<n)+2; 
    vector<mint> dp(sz); 
    vector<mint> ndp(sz); 
    for(int i=n+1;i>=2;i--){
        if(i==n+1){
            for(int j=1;j<=(1<<n);j++) dp[j] = 1; continue; 
        }
        for(int j=1;j<=(1<<n);j++){
            ndp[j] = ncr(j-((1<<i-2)+1),(1<<i-2)-1)*dp[j+1]; 
        }
        //dbg(i,ndp)
        for(int j=(1<<n);j>=1;j--){
            dp[j] = dp[j+1] + ndp[j]; 
        }
    }
    //dbg(dp)
    mint tmp = 1; 
    mint two = 2; 
    tmp = two.pow(n*(n+1)/2); 
    for(int i=1;i<=n-1;i++) tmp = tmp * fac[(1<<i)-1]; 
    for(int i=1;i<=(1<<n);i++) cout << (dp[(1<<n)-i+2]*tmp).val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   init(); 
   //cin >> t;
   while(t--) solve(); 
   return 0;
}