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

const int N = 5010; 
int M[N][N]; 
int a[N]; 
int p[N],s[N]; 
mint ncr[N][N]; 
int ra[N]; 
mint fac[N]; 

void solve(){
    int n; cin>>n; 
    rep(i,n) ra[i] = -1; 
    rrep(i,n) cin>>a[i]; 
    rrep(i,n) if(a[i]!=-1) ra[a[i]] = 1; 
    rep(i,n+1) rep(j,n+1) M[i][j] = 0; 
    rep(i,n+2) p[i] = s[i] = 0; 
    p[0] = n; 
    rrep(i,n) {
        if(a[i]!=-1) p[i] = min(p[i-1],a[i]); 
        else p[i] = p[i-1]; 
    }
    s[n+1] = n; 
    for(int i=n;i>=1;i--){
        if(a[i]!=-1) s[i] = min(s[i+1],a[i]); 
        else s[i] = s[i+1]; 
    }
    rrep(i,n) {
        // 지금까지 빈칸 개수 
        int cnt = 0; 
        for(int j=i;j<=n;j++){
            if(a[j]==-1) cnt++; 
            int mi = min(p[i-1],s[j+1]); 
            if(mi>0) M[mi-1][cnt]++; 
        }
    }
    for(int i=n-1;i>0;i--) for(int j=0;j<=n;j++) M[i-1][j] += M[i][j]; 
    mint ans = 0; 
    int cnt = 0; 
    int al = 0; 
    rrep(i,n) if(a[i]==-1) al++; 
    for(int k=0;k<n;k++){
        if(ra[k]==-1) cnt++; 
        for(int s = cnt; s<= n; s++) {
            //dbg(k,s,M[k][s],fac[al-cnt] * fac[cnt] * ncr[s][cnt] * M[k][s])
            // M[k][s] * (al-s)! * s! * ncr[s][cnt]
            
            ans += fac[al-cnt] * fac[cnt] * ncr[s][cnt] * M[k][s]; 
        }
    }
    cout << ans.val() << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    ncr[0][0] = 1; 
    fac[0] = 1; 
    for(int i=1;i<N;i++) {
        fac[i] = i*fac[i-1]; 
        ncr[i][0] = ncr[i][i] = 1; 
        for(int j=1;j<i;j++) ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j]; 
    }
    while(t--) solve(); 
    return 0;
}