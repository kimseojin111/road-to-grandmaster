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
ll l[N],r[N]; 
ll dp[N]; 
vector<int> adj[N]; 
ll df[N]; 

void dfs(int v, int p){
    int c = 0; 
    for(auto ne : adj[v]) if(ne!=p){
        dfs(ne,v); 
        dp[v] += dp[ne]; 
        c++; 
    }
    if(c==0){
        dp[v] = 0; df[v] = l[v]; return; 
    }
    df[v] = l[v]; 
    for(auto ne : adj[v]) if(ne!=p) {
        if(df[ne]>r[v]) df[v] = r[v]; 
        else df[v] = max(df[v],df[ne]); 
    }
    for(auto ne : adj[v]) if(ne!=p){
        dp[v] += max(0LL,df[ne]-df[v]); 
    }
}

void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>l[i] >> r[i]; 
    rrep(i,n) adj[i].clear(); 
    rrep(i,n) dp[i]=0; 
    rep(i,n-1){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    dfs(1,1); 
    cout << (dp[1]+df[1]) << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}