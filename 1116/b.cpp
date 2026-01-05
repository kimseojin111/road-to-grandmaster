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

const int N = 5010; 
int cnt[N]; 
mint dp[N]; 
mint d[N][N];  
mint dd[N][N]; 
mint ddd[N]; 
mint ndp[N]; 

void init(){
    for(int j=0;j<N;j++) dd[0][j] = 1; 
    for(int i=1;i<N;i++) {
        for(int j=1;j<=i;j++){
            d[i][j] += dd[i-j][j];
            if(i==3){
                dbg(j,d[i][j])
            } 
        }
        for(int j=1;j<N;j++) dd[i][j] = dd[i][j-1] + d[i][j]; 
        ddd[i] = dd[i][i]; 
        //dbg(i,ddd[i])
    }
}

void solve(){
    int n; cin>>n; 
    rrep(i,n) cnt[i] = 0; 
    rrep(i,n){
        int a; cin>>a; cnt[a]++; 
    }
    vector<int> t; 
    rrep(i,n) if(cnt[i]) t.pb(cnt[i]); 
    sort(all(t)); 
    int m = t.back(); 
    mint ans = 0; 
    for(int i=0;i<=n;i++) dp[i] = 0; 
    dp[0] = 1; 
    dbg(ans)
    for(auto y : t) {
        for(int i=0;i<=n;i++) ndp[i] = 0; 
        for(int i=n;i>=0;i--) for(int x=y;x>=0;x--) {
            ndp[min(n,i+x)] += dp[i]*ddd[x]; 
        }
        for(int i=0;i<=n;i++) dp[i] += ndp[i];  
    }
    for(int u=m;u<=n;u++) {
        dbg(u,dp[u])
        ans += dp[u]; 
    }
    cout << ans.val()<<"\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    init(); 
    while(t--) solve(); 
    return 0;
}