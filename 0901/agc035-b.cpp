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

const int N = 100010; 
int f[N],deg[N]; 
set<int> adj[N]; 
struct union_find {
    int n; vector<int> par; 
    union_find(int n) : n(n) {
        par.resize(n+1); 
        rrep(i,n) par[i] = i; 
    }
    int find(int x){
        return x==par[x] ? x : par[x]=find(par[x]); 
    }
    bool merge(int a, int b){
        a = find(a), b = find(b); 
        if(a==b) return false; 
        par[a] = b; return true; 
    }
}; 

void solve(){
    int n,m; cin>>n>>m; 
    if(m&1){
        cout << -1; return; 
    }
    union_find u(n); 
    vector<pair<int,int>> ans; 
    rep(i,m){
        int a,b; cin>>a>>b; 
        if(u.merge(a,b)){
            adj[a].insert(b); adj[b].insert(a); 
            deg[a]++; deg[b]++; 
        } else {
            ans.pb({a,b});
            f[a] ^= 1; 
        }
    }
    queue<int>q; 
    rrep(i,n) if(deg[i]==1) q.push(i); 
    while(!q.empty()){
        int a = q.front(); q.pop(); 
        if(adj[a].empty()) break; 
        int ne = *adj[a].begin(); 
        if(f[a]) ans.pb({a,ne}); 
        else {
            ans.pb({ne,a}); f[ne] ^= 1; 
        }
        adj[ne].erase(a); 
        deg[ne]--; if(deg[ne]==1) q.push(ne); 
    }
    for(auto [a,b]:ans) cout <<a<<" " <<b<<"\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}