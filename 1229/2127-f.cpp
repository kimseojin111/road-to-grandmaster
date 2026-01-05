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
using mint = modint1000000007; 

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

const int N = 700010; 
mint fac[N],rfac[N]; 
mint ncr(int n, int r){
    if(r<0||r>n) return mint(0); 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

mint nhr(int n, int r){
    return ncr(n+r-1,n-1); 
}

mint fuck(int n, int mx, int k){
    // 최대 mx로 k개로 합 n을 만드는 가짓수 
    // mx+1 이상인 개수 i 
    if(n<0) return mint(0);  
    mint ans = 0; 
    for(int i=0;i*(mx+1)<=n&&i<=k;i++){
        mint tmp = ncr(k,i) * nhr(k,n-i*(mx+1)); 
        if(i%2==0) ans += tmp; 
        else ans -= tmp; 
    }
    return ans; 
}

void solve(){
    int n,m; cin>>n>>m; 
    mint ans = 0; 
    for(int mx=1;mx<=m;mx++){
        // 1 에서 하는거 
        // 평균 값 : (mx - (m-mx)/(n-1) ) 
        mint tmp = fuck(m-mx,mx,n-1) * (mint(mx) - mint(m-mx)/(n-1)); 
        ans += tmp; 
        // 2에서 하는거 
        // 평균 값 : (mx - (m-mx*2)/(n-2))
        if(n>2){
            mint shit = fuck(m-mx*2,mx,n-2) * (mint(mx) - mint(m-mx*2)/(n-2)); 
            ans += shit * (n-2); 
        }
    }
    cout << ans.val() << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    fac[0] = rfac[0] = 1; 
    for(int i=1;i<N;i++){
        fac[i]=fac[i-1]*i; 
        rfac[i]=rfac[i-1]/i; 
    }
    while(t--) solve(); 
    return 0;
}