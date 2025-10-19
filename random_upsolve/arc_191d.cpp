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
int vis[N],par[N],dis1[N],dis2[N]; 
int cnt[N]; 
int deg[N]; 
int s,t; int n; 
void bfs(int S, int par[], int vis[], int d[], bool fuck = false){
    queue<int> q; q.push(S); 
    rrep(i,n) d[i] = 1e9; 
    d[S] = 0; 
    vis[S] = 1; 
    while(!q.empty()){
        int f = q.front(); q.pop(); 
        dbg(f,d[f])
        for(auto ne : adj[f]) if(!vis[ne]){
            if(fuck&&f==s&&ne==t) continue; 
            d[ne] = d[f]+1; 
            par[ne] = f; 
            vis[ne] = 1; q.push(ne); 
        }
    }
}

void solve(){
    int m; cin>>n>>m>>s>>t; 
    rep(i,m){
        int a,b; cin>>a>>b; adj[a].pb(b); adj[b].pb(a); deg[a]++; deg[b]++; 
    }
    bfs(t,par,vis,dis2); 
    memset(vis,0,sizeof(vis)); 
    bfs(s,par,vis,dis1); 
    int l = dis1[t]; 
    vector<int> path; 
    int now = par[t]; 
    while(now!=s){
        path.pb(now); 
        now = par[now]; 
    }
    vector<int> f; 
    rrep(i,n) f.pb(i); 
    sort(all(f),[&](int i, int j){
        return dis1[i]<dis1[j]; 
    }); 
    cnt[s] = 1; 
    for(int i=1;i<n;i++){
        int x = f[i]; 
        for(auto ne : adj[x]) if(dis1[ne]<dis1[x]){
            cnt[x] += cnt[ne]; 
        }
        cnt[x] = min(cnt[x],2); 
    }
    if(cnt[t]>=2){
        cout << (l*2); return; 
    }
    bool shit = false; 
    for(auto x : path) if(deg[x]>2) shit=true; 
    if(shit){
        // l+1이 있는지 
        set<int> shit; for(auto x : path) shit.insert(x); 
        shit.insert(s); shit.insert(t); 
        bool gogo = false; 
        rrep(i,n) if(shit.find(i)==shit.end()){
            if(dis1[i]+dis2[i]==l+1) gogo=true; 
        }
        if(gogo) cout << (2*l+1); 
        else cout << (2*l+2); return; 
    }
    // path 지우고 다른 최소 경로. 
    // or deg3 으로 이동 
    dbg(l)
    memset(vis,0,sizeof(vis)); 
    int ans = 1e9; 
    for(auto x : path) vis[x] = 1; 
    bfs(s,par,vis,dis1,true); 
    dbg(dis1[t])
    if(dis1[t]!=1e9) ans = min(ans,l+dis1[t]); 
    dbg(ans)
    memset(vis,0,sizeof(vis));
    bfs(s,par,vis,dis1); 
    rrep(i,n) if(deg[i]>=3){
        dbg(i,dis1[i],dis2[i])
        ans = min(ans,dis1[i]*4+2*l+4); 
        ans = min(ans,dis2[i]*4+2*l+4); 
    }
    if(ans==1e9) cout << -1; 
    else cout << ans; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}