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
int par[N]; 
int pp[N]; 
vector<int> gp[N]; 
vector<int> adj[N]; 
int sz[N]; 
int find(int x){
   // dbg(x,pp[x])
    return x==pp[x] ? x : pp[x]=find(pp[x]);
}

void dfs(int v, int p){
    //dbg(v,p)
    par[v] = p; 
    for(auto ne : adj[v]) if(ne!=p){
        dfs(ne,v); 
    }
}

void merge(int a, int b){
    int pa = find(a), pb = find(b); 
    if(sz[pa]>sz[pb]) {
        swap(pa,pb); swap(a,b); 
    }
    pp[pa] = pb; 
    sz[pb] += sz[pa]; 
    dfs(a,b);
}

void solve(){
    int x = 0; 
    int n,q; cin>>n>>q; 
    rrep(i,n) {
        par[i]=i; gp[i].pb(i); pp[i] = i; sz[i] = 1; 
    }
    while(q--){
        int op,a,b; 
        cin>>op>>a>>b; 
        op = 1 + ((1LL*op*(x+1))%998244353)%2;
        b = 1 + (1LL*b*(x+1))%998244353%n;
        a = 1 + (1LL*a*(x+1))%998244353%n;
        dbg(op,a,b)
        if(op==1){
            adj[a].pb(b); adj[b].pb(a); merge(a,b); 
        }
        else {
            if(find(a)!=find(b)) {
                x = 0; cout << x << "\n"; 
            } else {
                x = 0; 
                dbg(a,b,par[a],par[b])
                int p = par[a]; if(p==par[b] && p!=b && p!=a ) x = p; 
                if(par[b]!=a&&par[par[b]]==a) x = par[b]; 
                if(par[a]!=b&&par[par[a]]==b) x = par[a]; 
                cout << x << "\n";
            }
        }
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}