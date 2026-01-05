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

const int N = 3010; 
int l[N],r[N]; 
vector<int> v[N]; 
int lv[N]; 
int pv; 
map<pair<int,int>,int> cache; 

int ans[N][N]; 

int a[N]; 

int qry(int i, int j){
    if(i>j) swap(i,j); 
    assert(min(i,j)>=0&&max(i,j)<=100); 
    pair<int,int> v = {i,j}; 
    if(cache.find(v)!=cache.end()) {
        return cache[v]; 
    }
    cout << "? " << i+1 << " " << j << endl; 
    int x; cin>>x;
    // {
    //     int k = a[i] ^ a[j]; 
    //     x = k==0 ? -1 : 31 - __builtin_clz(k); 
    // } 
    cache[v] = x; 
    return x; 
}

void dfs(int node){
    // dbg(node)
    auto& vi = v[node]; 
    dbg(node,v[node],lv[node])
    sort(all(vi)); 
    if(lv[node]==-1){
        for(auto x : vi) for(auto y : vi) ans[x][y] = -1; 
    }
    if(vi.size()==1||lv[node]==-1) return; 
    map<int,int> col; 
    int s = vi[0]; 
    col[s] = 0; 
    int e = vi.back(); 
    int hb = lv[node]; 
    if(qry(s,e)==hb) col[e] = 1; 
    else col[e] = 0; 
    for(int i=1;i+1<vi.size();i++){
        int now = vi[i]; 
        int u = abs(now-s) < abs(now-e) ? e : s; 
        col[now] = col[u] ^ (qry(u,now)==hb); 
    }
    vector<int> la,ra; 
    for(auto x : vi) if(col[x]) ra.pb(x); else la.pb(x); 
    for(auto x : la) for(auto y : ra) ans[x][y] = ans[y][x] = lv[node]; 
    if(!la.empty()){
        l[node] = ++pv; 
        lv[pv] = lv[node] - 1; 
        v[pv] = la; 
        dfs(pv); 
    }
    if(!ra.empty()){
        r[node] = ++pv; 
        lv[pv] = lv[node] -1; 
        v[pv] = ra; 
        dfs(pv); 
    }
}

void solve(){
    //dbg(31-__builtin_clz(1)); 
    int n; cin>>n; 
    rrep(i,n){
        a[i] = randint(0,(1<<30)-1); 
    }
    for(int i=0;i<N;i++){
        l[i] = r[i] = lv[i] = -1; 
        v[i].clear(); 
    }
    lv[0] = 29; 
    cache.clear();
    pv = 0; 
    for(int i=0;i<=n;i++) v[0].pb(i); 
    dfs(0); 
    cout << "!\n";
    rrep(i,n) for(int j=i;j<=n;j++) {
        cout << ans[i-1][j] << " \n"[j==n]; 
        // {
        //     int k = a[i-1] ^ a[j]; 
        //     int x = k==0 ? -1 : 31 - __builtin_clz(k); 
        //     if(ans[i-1][j]!=x){
        //         dbg(i,j,"wtf????",a[i-1],a[j],ans[i-1][j],x)
        //     }
        //     assert(ans[i-1][j]==x); 
        // } 
    }
    cout << endl;
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}