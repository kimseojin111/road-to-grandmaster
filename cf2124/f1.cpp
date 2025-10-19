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

#include <atcoder/modint>
using namespace atcoder; 

using mint = modint998244353; 

const int N = 520; 
vector<pair<int,int>> dpL[N]; 
vector<pair<int,int>> dpR[N];  
int cnt[N*3]; 

mint dp[N][N]; 
mint dpp[N]; 

void solve(){
    int n,m; cin>>n>>m; 
    rrep(i,n) dpL[i].clear(), dpR[i].clear(); 
    vector<pair<int,int>> v; 
    rep(_,m){
        int i,x; cin>>i>>x; 
        for(int p=i-x+1;p<=i;p++) if(p>=1&&p<=n){
            dpL[p].pb({x+p-i,p+x-1}); 
        }
        if(i>=x) {
            for(int q=i;q<=n;q++){
                dpR[q].pb({x+q-i+1,q-x+1}); 
            }
        }
    }
    rrep(i,n){
        sort(all(dpL[i])); dpL[i].erase(unique(all(dpL[i])),dpL[i].end()); 
        sort(all(dpR[i])); dpR[i].erase(unique(all(dpR[i])),dpR[i].end()); 
    }
    dbg(dpL[2],dpR[3])
    auto get = [&](int i, int j){
        rrep(k,j-i+1) cnt[k] = 1; 
        for(auto [x,r] : dpL[i]) if(j>=r) cnt[x] = 0; 
        for(auto [x,l] : dpR[j]) if(i<=l) cnt[x] = 0; 
        int re = 0; 
        rrep(k,j-i+1) {
            re += cnt[k]; 
        }
        return re; 
    };
    rrep(i,n+1) rrep(j,n+1) dp[i][j] = 0; 
    rrep(i,n+1) dpp[i] = 0; 
    dp[n+1][0] = 1; 
    dpp[n+1] = 1; 
    for(int i=n;i>0;i--){
        for(int j=n;j>=i;j--){
            get(i,j); 
            for(int k=1;k<=j-i+1;k++){
                if(k!=1){
                    dp[i][k] += dpp[j+1]*cnt[k]; 
                }
                else {
                    dp[i][k] += (dpp[j+1]-dp[j+1][j-i+2])*cnt[k]; 
                }
            }
        }
        for(int j=1;j<=n;j++) dpp[i] += dp[i][j]; 
    }
    cout << (dpp[1].val()) << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}