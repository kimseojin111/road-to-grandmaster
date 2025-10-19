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
using mint = modint1000000007;  

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

const int N = 200010; 
int tt[N]; 
vector<int> adj[N]; 
void init(int n){
    rrep(i,n) adj[i].clear(); 
    rrep(i,n)tt[i] = 0; 
}
int d[N]; 
int par[N]; 
mint fac[N]; 

void solve(){
    int n,m; cin>>n>>m; init(n); 
    rep(i,m){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    if(m!=n-1){
        cout << "0\n"; return; 
    }
    auto bfs = [&](int i){
        rrep(i,n) d[i] = 1e9; 
        queue<int> q; q.push(i); 
        d[i] = 0; 
        par[i] = i; 
        while(!q.empty()){
            int f=q.front(); q.pop(); 
            
            for(auto ne : adj[f]) if(d[ne]>d[f]+1){
                par[ne] = f; 
                d[ne] = d[f]+1; q.push(ne); 
            }
        }
        return ;
    };
    bfs(1); 
    int s = max_element(d+1,d+n+1)-d; 
    bfs(s); 
    int e = max_element(d+1,d+n+1)-d; 
    vector<int> shit; 
    int t= par[e]; 
    dbg(s,e)
    while(t!=s){
        shit.pb(t); tt[t] = 1;t = par[t];  
    }
    dbg(shit)
    if(shit.empty()){
        cout << 2 << "\n"; return; 
    }
    rrep(i,n){
        if(tt[i]==0&&adj[i].size()>1){
            dbg(i)
            cout << 0 << "\n"; return; 
        }
    }
    if(shit.size()==1){
        int u = shit[0]; 
        mint ans = fac[adj[u].size()]*2; 
        cout << (ans.val()) << "\n"; return; 
    }
    mint ans = 4; 
    for(int i=0;i<shit.size();i++){
        if(i==0||i==shit.size()-1) ans = ans * fac[adj[shit[i]].size()-1]; 
        else ans = ans * fac[adj[shit[i]].size()-2]; 
    }
    cout << ans.val() << "\n";

}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   fac[0] = 1; 
   for(int i=1;i<N;i++) fac[i] = fac[i-1]*i; 
   cin >> t;
   while(t--) solve(); 
   return 0;
}