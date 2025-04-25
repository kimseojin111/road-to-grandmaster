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

const int N = 200010; 
vector<int> adj[N]; 
int n; 

int deg[N]; 

int dp[2][N]; 
int cnt[N]; 
int par[N]; 

int dd[N]; 
int ddd[N]; 

int m,s,t;
bool vis[N]; 

void get_par(int s, int dd[]){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq; 
    rrep(i,n) dd[i] = 1e9; 
    pq.push({0,s}); 
    par[s] = s; 
    dd[s] = 0; 
    memset(vis,0,sizeof(vis)); 
    while(!pq.empty()){
        auto [di,i] = pq.top(); pq.pop(); 
        if(vis[i]) continue; 
        vis[i] = 1; 
        for(auto ne : adj[i]) {
            if(dd[ne]>di+1){
                par[ne] = i; 
                dd[ne] = di+1; 
                pq.push({di+1,ne}); 
            }
        }
    }
}

void solve(){
    cin>>n>>m>>s>>t; 
    rep(i,m){
        int a,b; cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
        deg[a]++; deg[b]++; 
    }
    rep(j,2) rrep(i,n) dp[j][i] = 1e9; 
    dp[0][s] = 0; 

    get_par(s,dd); 
    int x = par[t]; 
    vector<int> pp; 
    while(x!=s) {
        pp.pb(x); x = par[x]; 
    }
    pp.pb(s); pp.pb(t); 
    bool wwww = false; 
    for(auto x : pp) if(deg[x]>=3) wwww=true; 
    if(wwww==false){
        if(deg[s]==1&&deg[t]==1) {
            cout << -1; return; 
        }
        get_par(t,ddd); 
        int ans = 1e9; 
        rrep(i,n){
            if(deg[i]>=3){
                ans = min(ans,dd[i]+ddd[i]+2); 
            }
        }
        if(ans==1e9){
            cout << -1; 
        }
        else cout << ans; 
        return;
    }

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq; 
    pq.push({0,s}); 
    while(!pq.empty()){
        auto [di,i] = pq.top(); pq.pop(); 
        if(cnt[i]==2) continue;  
        dp[cnt[i]][i] = di; 
        cnt[i]++; 
        for(auto ne : adj[i]) {
            if(cnt[ne]<2){
                pq.push({di+1,ne}); 
            }
        }
    }
    int a = dp[0][t], b = dp[1][t]; 
    dbg(a,b)
    int ans = min(a+b,a*2+2); 
    get_par(t,ddd);  
    rrep(i,n){
        if(deg[i]>=3){
            ans = min(ans,dd[i]+ddd[i]+2); 
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