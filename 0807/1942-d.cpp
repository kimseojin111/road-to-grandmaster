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

const int N = 1010; 
vector<ll> dp[N]; 
ll a[N][N]; 

void solve(){
    int n,k; cin>>n>>k; 
    for(int i=0;i<=n;i++) dp[i].clear(); 
    rrep(i,n) for(int j=i;j<=n;j++) cin>>a[i][j]; 
    dp[0].pb(0LL); 
    dp[1].pb(0); dp[1].pb(a[1][1]); 
    sort(all(dp[1]),[](auto a, auto b){
        return a>b; 
    }); 
    while(dp[1].size()>k) dp[1].pop_back();
    for(int i=2;i<=n;i++){
        // 값, j, pivot 
        priority_queue<array<ll,3>> pq; 
        for(int j=1;j<=i;j++){
            ll tmp = a[j][i] + (j==1 ? 0LL : dp[j-2][0]); 
            pq.push({tmp,j,0}); 
        }
        while(dp[i].size()<=k&&!pq.empty()){
            auto [val,j,pv] = pq.top(); pq.pop(); 
            //shit.pb(val); 
            dbg(val,j,pv)
            dp[i].pb(val); 
            if(j==1||j==2) continue; 
            if(pv+1>=dp[j-2].size()) continue; 
            pv++; 
            ll tmp = a[j][i] + dp[j-2][pv]; 
            pq.push({tmp,j,pv});  
        }
        for(auto x : dp[i-1]) dp[i].pb(x); 
        sort(all(dp[i]),[](auto a, auto b){
            return a>b; 
        }); 
        while(dp[i].size()>k) dp[i].pop_back(); 
    }
    for(auto x:dp[n]) cout << x << " "; 
    cout << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}