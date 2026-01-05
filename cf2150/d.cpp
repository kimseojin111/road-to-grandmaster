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

const int N = 400010; 
mint fac[N]; 
mint rfac[N]; 

mint ncr(int n, int r){
    if(r<0||r>n) return mint(0);
    return fac[n]*rfac[r]*rfac[n-r]; 
}

mint nhr(int n, int r){
    if(r<0) return mint(0); 
    return ncr(n+r-1,r-1); 
}

int a[N]; 
mint pa[N]; 
mint ppa[N]; 


void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>a[i]; 
    vector<mint> P(n+1,0), PJ(n+1,0), PQ(n+1,0);
        for(int i=1;i<=n;i++){
            P[i]  = P[i-1] + mint(a[i]);
            PJ[i] = PJ[i-1] + mint(a[i]) * i;
            PQ[i] = PQ[i-1] + mint(a[i]) * mint(n - i + 1);
        }
    mint ans = 0; 
    for(int i=1;i<=n;i++) ans = ans + mint(a[i])*n; 
    for(int i=1;i+1<=n;i++){
        ans = ans + mint(n)*(n-1)*(a[i]+a[i+1])/2; 
    }
    auto ends_sum = [&](int m){
            if(m>n) return mint(0);
            mint lefts  = P[n-m+1] - P[0];
            mint rights = P[n] - P[m-1];
            return lefts + rights;
        };
    auto mids_sum = [&](int m){
            if(m<=2) return mint(0);
            mint all = PJ[m-1] + mint(m)*(P[n-m+1]-P[m-1]) + (PQ[n]-PQ[n-m+1]);
            mint ends = ends_sum(m);
            return all - ends;
        };
    for(int m=3;m<=n;m++){
        mint SumEnd = 0, SumMid = 0;
        int r = n-m;
        int t = r/2;            
        int aparam = m - 3;     

        long long nn0 = t + aparam + 1;
        mint C1 = ncr(nn0, aparam + 1);
        mint C2 = ncr(nn0, aparam + 2);
        mint C3 = ncr(nn0, aparam + 3);

        mint S0 = C1;
        mint S1 = mint(aparam + 1) * C2;
        mint S2 = mint(aparam + 1) * C2 + mint(1LL*(aparam + 1)*(aparam + 2)) * C3;

        mint Cnt = mint(r+1) * S0 - mint(2) * S1;

        SumEnd = mint(1LL*(r+1)*(r+2)/2) * S0 - mint(2*r+3) * S1 + mint(2) * S2;

        mint num = mint(r+1) * S1 - mint(2) * S2;
        mint inv_m2 = 1/(mint(m-2));
        SumMid = Cnt + mint(2) * inv_m2 * num;

        mint E = ends_sum(m);
        mint M = mids_sum(m);
        ans += SumEnd * E + SumMid * M;
    }
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   fac[0] = 1; 
   rfac[0] = 1; 
   for(int i=1;i<N;i++){
    fac[i] = fac[i-1]*i; 
    rfac[i] = 1/fac[i]; 
   }
   dbg(1)
   while(t--) solve(); 
   return 0;
}