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

#include <atcoder/modint>
using namespace atcoder; 
using mint = modint998244353; 

const int N = 410; 
mint fac[N]; 

bool adj[N][N]; 
int deg[N]; 

int par[N]; 
int get(int x){
    if(x==par[x]) return x; 
    return par[x] = get(par[x]); 
}
void merge(int a, int b){
    a=get(a), b=get(b); 
    if(a!=b) par[a]=b; 
}

mint f(vector<int>& v, bool st){
    for(auto x : v) deg[x] = 0; 
    for(auto x : v) for(auto y:v) if(adj[x][y]) deg[x]++; 
    vector<int> rt; 
    for(auto x : v) if(deg[x]==v.size()) rt.pb(x); 
    sort(all(rt)); 
    if(rt.size()==0) return 0; 
    if(st){
        if(rt[0]!=0) return (mint)0; 
    }
    mint ans = fac[rt.size()]; 
    if(st) ans /= ((int)rt.size()); 
    vector<int> shit; 
    for(auto x : v) if(lower_bound(all(rt),x)==upper_bound(all(rt),x)) shit.pb(x); 
    if(shit.size()==0) return ans; 
    for(auto x : shit) par[x] = x; 
    for(auto x : shit) for(auto y:shit) if(adj[x][y]) merge(x,y); 
    map<int,vector<int>> M; 
    for(auto x : shit) M[get(x)].pb(x); 
    for(auto [k,v]:M){
        ans *= f(v,false); 
    }
    return ans; 
}

void solve(){
    int n; cin>>n; 
    rep(i,n) rep(j,n) {
        cin>>adj[i][j]; 
    }
    vector<int> t; 
    rep(i,n) t.pb(i); 
    cout << f(t,true).val() << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   fac[0] = 1; 
   for(int i=1;i<N;i++) fac[i] = fac[i-1]*i; 
   while(t--) solve(); 
   return 0;
}