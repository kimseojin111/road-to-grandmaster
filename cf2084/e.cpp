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

const int N = 5010; 

#include <atcoder/modint> 
using namespace atcoder; 

using mint = modint1000000007; 
mint fac[N],rfac[N];
mint ncr(int n, int r){
    if(r<0||r>n) return (mint)0; 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

int a[N]; 
// -1 이 포함된 애들 
int z[N]; 
int sum(int l, int r){
    return z[r]-z[l-1]; 
}

// 오른쪽 최소 왼최소 
int R[N],L[N]; 
int dp[N][N]; 
int found[N]; 

void init(int n){
    for(int i=0;i<=n+1;i++){
        R[i]=L[i]=found[i]=a[i]=z[i]=0; 
        for(int j=0;j<=n+1;j++) dp[i][j]=0;
    }
}
void solve(){
    int n; cin>>n;
    init(n); 
    rrep(i,n) {
        cin>>a[i]; if(a[i]==-1) z[i]=1; 
        if(a[i]!=-1) found[a[i]]=1; 
    } 
    rrep(i,n) z[i]+=z[i-1]; 
    L[0]=n,R[n+1]=n; 
    rrep(i,n) {
        if(a[i]!=-1) L[i]=min(a[i],L[i-1]); 
        else L[i]=L[i-1]; 
    }
    for(int i=n;i>0;i--){
        if(a[i]==-1)R[i]=R[i+1]; 
        else R[i]=min(a[i],R[i+1]); 
    }
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++){
        int l = sum(i,j); 
        int k = min(L[i-1],R[j+1]); 
        dbg(i,j,k,l)
        dp[0][l]++; dp[k][l]--; 
    }
    rep(j,n) rrep(i,n){
        dp[i][j] += dp[i-1][j]; 
        dbg(i,j,dp[i][j])
    }
    int c2=0; 
    mint ans = 0; 
    int t = z[n]; 
    for(int k=0;k<n;k++){
        if(!found[k]) c2++; 
        for(int j=c2;j<=n;j++){
            ans += ncr(j,c2)*fac[c2]*fac[t-c2]*dp[k][j]; 
            dbg(k,j,c2,dp[k][j],ans.val())
        }
    }
    cout << ans.val()<<"\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   fac[0]=1; 
   for(int i=1;i<N;i++) fac[i] = fac[i-1]*i; 
   for(int i=0;i<N;i++) rfac[i] = 1/fac[i]; 
   while(t--) solve(); 
   return 0;
}