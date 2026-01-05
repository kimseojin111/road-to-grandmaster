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

struct union_find {
    int n; vector<int> par; 
    vector<int> val; 
    vector<vector<int>> gp; 
    union_find(int n) : n(n) {
        par.resize(n+1); gp.resize(n+1); val.resize(n+1); 
        rrep(i,n) par[i] = i; 
        rep(i,n) gp[i].pb(i); 
    }
    int find(int x){
        return x==par[x] ? x : par[x]=find(par[x]); 
    }
    bool merge(int a, int b, int c){ // a - b = c
        a = find(a), b = find(b); 
        if(a==b) return false; 
        if(gp[a].size()>gp[b].size()){
            swap(a,b); c = -c; 
        }
        par[a] = b; 
        for(auto x : gp[a]) {
            val[x] += c; gp[b].pb(x); 
        }
        return true; 
    }
}; 

const int N = 20*20; 
int a[N], b[N], c[N]; 
int dif[20][20]; 

const int F = (1<<16)+3; 
bool dp[F][F]; 
vector<int> chk[N]; 
int mola[F]; 

void solve(){
    int n,m; cin>>n>>m; 
    union_find uf(n); 
    rep(i,m){
        cin>>a[i]>>b[i]>>c[i]; a[i]--; b[i]--; 
        dif[a[i]][b[i]] = c[i]; 
        uf.merge(a[i],b[i],c[i]); 
    }
    vector<int> par; 
    rep(i,n){
        int x = uf.find(i); par.pb(x); 
    }
    sort(all(par)); par.erase(unique(all(par)),par.end()); 
    map<int,int> par_to_idx; 
    vector<int> val; 
    for(auto x : par){
        par_to_idx[x] = val.size(); 
        vector<int> tmp; 
        for(auto t : uf.gp[x]){
            tmp.pb(uf.val[t]); 
        }
        int mi = *min_element(all(tmp)); 
        int shit = 0; 
        for(auto t : tmp){
            shit |= (1<<(t-mi)); 
        }
        val.pb(shit); 
        dbg(x,shit)
    }
    // val 끼리 
    int sz = val.size(); 
    dbg(val)
    chk[0].pb(0); 
    for(int b=1;b<(1<<sz);b++){
        int j = __builtin_ctz(b); 
        mola[b] = mola[b-(1<<j)] + val[j]; 
        chk[mola[b]].pb(b); 
        dbg(b,mola[b])
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