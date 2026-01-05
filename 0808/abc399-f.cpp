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

const int N = 200010; 
mint a[N];   
mint ps[N]; 
int k; 
mint l[12],r[12]; 
mint ncr[12][12]; 

mint f(int s, int e){
    if(s==e) return a[s].pow(k); 
    int m = s+e>>1; 
    mint re = f(s,m)+f(m+1,e); 
    for(int i=0;i<=k;i++) l[i]=0,r[i]=0; 
    for(int i=0;i<=k;i++){
        for(int j=s-1;j<=m-1;j++) {
            l[i] += (ps[m]-ps[j]).pow(i); 
            dbg(j,ps[m]-ps[j])
        }
        for(int j=m+1;j<=e;j++) r[i] += (ps[j]-ps[m]).pow(i); 
    }
    for(int i=0;i<=k;i++) {
        re += ncr[k][i] * l[i] * r[k-i]; 
        dbg(i,ncr[k][i],l[i],r[k-i])
    }
    dbg(s,e,re)
    return re; 
}

void solve(){
    int n; cin>>n>>k; 
    ncr[0][0] = 1; 
    for(int i=1;i<12;i++){
        ncr[i][0] = ncr[i][i] = 1; 
        for(int j=1;j<i;j++) ncr[i][j] = ncr[i-1][j-1]+ncr[i-1][j]; 
    }
    rrep(i,n) {
        int x; cin>>x; 
        a[i]=x; 
        ps[i] = ps[i-1] + a[i]; 
        dbg(i,ps[i])
    }
    cout<<f(1,n).val(); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}