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

const int N = 200010; 
vector<array<ll,3>> adj[N]; 
ll ds[N],dt[N]; 
bool vis[N]; 
vector<int> g[N]; 
int ans[N]; 
int ps[N]; 

void bfs(int s, ll d[], int n) {
    rrep(i,n) d[i] = 2e18; 
    memset(vis,0,sizeof(vis)); 
    d[s] = 0; 
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq; 
    pq.push({0LL,s}); 
    while(!pq.empty()){
        auto [df,f] = pq.top(); pq.pop(); 
        //dbg(df,f)
        if(vis[f]) continue; 
        vis[f] = 1; 
        //dbg(adj[1])
        for(auto [ne,dd,vv] : adj[f]){
          //  dbg(ne,d[ne])
            if(d[ne]>df+dd) {
                d[ne] = df+dd; pq.push({d[ne],ne}); 
            }
        } 
    }
}; 

void solve(){
    int n,m; cin>>n>>m; 
    rrep(i,m){
        int a,b,c; 
        cin>>a>>b>>c; 
        adj[a].pb({b,(ll)c,i}); adj[b].pb({a,(ll)c,i}); 
    }
    bfs(1,ds,n); bfs(n,dt,n); 
    vector<int> in; 
    rrep(i,n) for(auto [x,ne,idx] : adj[i]) if(ds[n]==ds[i]+ne+dt[x]) {
        g[i].pb(x); g[x].pb(i); in.pb(i); in.pb(x); 
    }
    sort(all(in)); in.erase(unique(all(in)),in.end()); 
    sort(all(in),[](auto i, auto j){
        if(ds[i]!=ds[j]) return ds[i]<ds[j]; 
        return i<j; 
    }); 
    auto get = [&](int x){
        return lower_bound(all(in),x,[](auto i, auto j){
            if(ds[i]!=ds[j]) return ds[i]<ds[j]; 
            return i<j; 
        }) - in.begin(); 
    }; 
    dbg(in)
    for(auto x : in){
        for(auto ne : g[x]){
            if(ds[x]<ds[ne]) {
                int xx = get(x), nn = get(ne); 
                ps[xx]++; ps[nn]--; 
                dbg(xx,nn)
            }
        }
    }
    dbg(ans[1],ans[2],ans[3])
    for(int i=0;i<in.size()-1;i++){
        if(i>0) ps[i] += ps[i-1]; 
        dbg(i,in[i])
        if(ps[i]==1){
            int s = in[i], p = in[i+1]; 
            dbg(s,p)
            for(auto [d,fuck,idx] : adj[s]) if(p==d){
                ans[idx] = 1; 
                dbg(idx)
            }
        }
    }
    rrep(i,m) cout << (ans[i] ? "Yes" : "No") <<"\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}