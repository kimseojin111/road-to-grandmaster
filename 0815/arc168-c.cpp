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

int a,b,c;
const int N = 300;  
mint pa[N], pb[N], pc[N]; 
mint fac[N]; 

void solve(){
    int n,k; cin>>n>>k; 
    rep(i,n){
        char cc; cin>>cc; 
        if(cc=='A') a++; 
        if(cc=='B') b++; 
        if(cc=='C') c++; 
    }
    dbg(a,b,c)
    pa[0] = 1; 
    fac[0] = 1; 
    for(int i=1;i<N;i++) fac[i] = fac[i-1]*i; 
    for(int i=1;i<N;i++) pa[i] = pa[i-1]*(a+1-i); 
    pb[0] = 1; 
    for(int i=1;i<N;i++) pb[i] = pb[i-1]*(b+1-i); 
    pc[0] = 1; 
    for(int i=1;i<N;i++) pc[i] = pc[i-1]*(c+1-i); 
    mint ans = 0; 
    for(int p=0;2*p<=k;p++) rep(q,k+1) rep(r,k+1) rep(s,k+1){
        if(2*p+q+r+s<=k){
            mint tmp = pa[p+q+r]*pb[p+r+s]*pc[p+s+q] / (fac[q]*fac[r]*fac[s]*fac[p+q]*fac[p+r]*fac[p+s]); 
            if(p>0) tmp *= 2; 
           // dbg(p,q,r,s,tmp)
            ans += tmp; 
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