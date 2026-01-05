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

const int N = 110; 
ll dp[N]; 
vector<pair<int,ll>> adj[N]; 
const ll inf = 2e18; 
bool vis[N]; 

void solve(){
    int n,m; cin>>n>>m; 
    rrep(i,n) dp[i] = inf; 
    rep(i,m){
        int a,b; ll w; cin>>a>>b>>w; 
        adj[a].pb({b,w}); adj[b].pb({a,w}); 
    }
    dp[n] = 0; 
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq; 
    pq.push({0,n}); 
    while(!pq.empty()){
        auto [di,i] = pq.top(); pq.pop(); 
        if(vis[i]) continue; 
        vis[i] = 1; 
        for(auto [ne,dn] : adj[i]) if(dp[ne]>dn+di){
            dp[ne] = dn+di; 
            pq.push({dp[ne],ne}); 
        }
    }
    if(dp[1]==inf){
        cout << "inf"; return; 
    }
    if(dp[1]==0){
        cout << "0 0"; return;
    }
    // dp[i] 받기 
    vector<int> x; 
    vector<pair<string,ll>> ans; 
    rrep(i,n){
        if(dp[i]!=0&&dp[i]!=inf) x.pb(i); 
        dbg(i,dp[i])
    }
    dbg(x)
    sort(all(x),[&](int i, int j){
        return dp[i]<dp[j]; 
    }); 
    dbg(x)
    for(int i=0;i<x.size();i++){
        string s; rep(t,n) s.pb('0'); 
        for(int j=i;j<x.size();j++) s[x[j]-1]='1'; 
        ll pl = (i==0) ? dp[x[0]] : dp[x[i]]-dp[x[i-1]]; 
        if(pl>0) ans.pb({s,pl}); 
        if(x[i]==1) break; 
    }
    cout << dp[1] << " " << ans.size() << "\n"; 
    for(auto [s,t] : ans) cout << s << " " << t << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}