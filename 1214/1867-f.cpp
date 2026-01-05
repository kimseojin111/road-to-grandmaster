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
typedef uint64_t ll;
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

uint64_t mix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

ll st; 

ll hsh(vector<ll> v){
    ll re = st; 
    sort(all(v)); 
    for(auto x : v){
        re = mix64(re^mix64(x)); 
    }
    return re; 
}

const int N = 1000100; 
vector<int> adj[N]; 
ll pv[N]; 

void dfs(int v, int p){
    vector<ll> dd; 
    for(auto ne : adj[v]) if(ne!=p){
        dfs(ne,v); dd.pb(pv[ne]); 
    }
    sort(all(dd)); 
    pv[v] = hsh(dd); 
    dbg(v,pv[v])
    return; 
}

int nn; 
unordered_set<ll> s; 
unordered_map<ll,vector<ll>> dp[16]; 

vector<int> adjj[N]; 
int shit; 
void build(int v, vector<ll>h){
    if(h.empty()) return; 
    for(auto ne : h){
        for(int i=1;i<=15;i++) if(dp[i].find(ne)!=dp[i].end()) {
            int vv = ++shit; 
            adjj[v].pb(vv); 
            build(vv,dp[i][ne]); 
            break; 
        }
    }
}

void walk(int n, int remain, int maxv, vector<ll> h, vector<int> sz){
    if(remain==0){
        ll k = hsh(h); 
        if(s.find(k)==s.end()){
            shit = nn-n+1; 
            build(shit,h); 
            shit = nn-n+1; 
            for(int i=1;i<shit;i++) {
                adjj[i].pb(i+1); 
            }
            rrep(i,nn) for(auto x : adjj[i]) cout << i << " " << x << "\n"; 
            exit(0); 
        } else {
            auto hh = h; 
            sort(all(hh)); 
            dp[n][k] = h; 
        }
    }
    for (int x = min(remain, maxv); x >= 1; x--) {
        for (auto sub : dp[x]) {
            h.pb(sub.first);
            sz.pb(x);
            walk(n, remain - x, x, h, sz);
            h.pop_back();
            sz.pop_back(); 
        }
    }
}

void solve(){
    int n; cin>>n; nn=n; 
    rep(i,n-1) {
        int a,b; cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    dfs(1,1); 
    rrep(i,n) s.insert(pv[i]); 
    for(int i=1;i<=min(15,n);i++){
        walk(i,i-1,i-1,vector<ll>(),vector<int>()); 
    }
    for(int i=1;i<n;i++) cout << i << " " << i+1 << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    st = randint(0,2e18); 
    while(t--) solve(); 
    return 0;
}