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

const int N = 52; 
unordered_set<int> a[N];
int b[N]; 
int dp[N][N]; 

void solve(){
    int n; cin>>n; 
    rrep(i,n) {
        int x; cin>>x; a[i].insert(x); 
    }
    rrep(i,n) cin>>b[i]; 
    memset(dp,-1,sizeof(dp));
    dp[0][0] = 0; 
    for(int i=1;i<=50;i++){
        dp[i][i] = 0; 
        for(int k=1;k<=i;k++){
            int ne = i%k; 
            for(int j=0;j<i;j++) if(dp[ne][j]!=-1) {
                if(dp[i][j]==-1) dp[i][j] = max(dp[ne][j],k); 
                else dp[i][j] = min(dp[i][j],max(dp[ne][j],k)); 
            }
        }
    }
    ll ans = 0; 
    rrep(i,n) {
        if(dp[*a[i].begin()][b[i]]==-1){
            cout << -1; return; 
        }        
    }
    rep(_,52){
        int mx = 0; 
        rrep(i,n){
            vector<int> er; 
            int kk = 1000; 
            for(auto d : a[i]){
                if(dp[d][b[i]]==-1) er.pb(d); 
                else kk = min(kk,dp[d][b[i]]); 
            }
            for(auto x : er) a[i].erase(x); 
            mx = max(mx,kk); 
        }
        if(mx==0) break; 
        ans |= 1LL<<mx; 
        rrep(i,n){
            vector<int> in; 
            for(auto d : a[i]) in.pb(d%mx); 
            for(auto d : in) a[i].insert(d); 
        }
    }
    cout << ans;
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}