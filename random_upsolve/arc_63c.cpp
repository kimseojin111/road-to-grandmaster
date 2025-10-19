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

const int N = 100010; 
vector<int> adj[N]; 
int L[N],R[N],p[N]; 

int b[N]; 

void fs(int v, int p){
    b[v] = b[p]^1; 
    for(auto x : adj[v]) if(x!=p) fs(x,v);  
}

void ex(){
    cout << "No"; 
    exit(0); 
}

void dfs(int v, int pa){
    L[v] = -1e9; 
    R[v] = 1e9; 
    for(auto ne : adj[v]) if(ne!=pa){
        dfs(ne,v);
        L[v] = max(L[v],L[ne]-1); 
        R[v] = min(R[v],R[ne]+1);  
    }
    if(L[v]>R[v]) ex(); 
    if(p[v]!=-1){
        if(p[v]<L[v]||R[v]<p[v]) ex(); 
        L[v] = p[v], R[v] = p[v]; return; 
    }
    if(b[v]==0){
        // L,R 짝수 
        if(L[v]&1) L[v]++; 
        if(R[v]&1) R[v]--; 
    }
    else {
        if(!(L[v]&1)) L[v]++; 
        if(!(R[v]&1)) R[v]--; 
    }
    if(L[v]>R[v]) ex(); 
    return; 
}

void dfss(int v, int pa){
    if(pa==v){
        p[v] = L[v]; 
    }
    else {
        int pp = p[pa]; 
        int nt = pp-1; 
        if(p[v]!=-1){
            assert(pp==p[v]+1 || pp==p[v]-1); 
        }
        if(nt>=L[v]&&nt<=R[v]) p[v] = nt; 
        else {
            nt = pp+1; 
            assert(nt>=L[v]&&nt<=R[v]); 
            p[v] = nt; 
        }
    }
    for(auto ne : adj[v]) if(ne!=pa) dfss(ne,v); 
}

void solve(){
    int n; cin>>n; 
    rrep(i,n) p[i]=-1; 
    rep(i,n-1){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    int k; cin>>k; 
    rep(j,k){
        int v,pt; cin>>v>>pt; p[v] = pt; 
    }
    fs(1,1); 
    bool flag = true, flagg = true; 
    rrep(i,n) if(p[i]!=-1){
        int t = b[i]^p[i]; 
        if(t&1) flag = false; 
        else flagg = false; 
    }
    // flag ->  모두 같음 
    // flagg 모두 다름 
    if(flag==false&&flagg==false) {
        ex(); 
    }
    if(flagg) rrep(i,n) b[i]^=1; 
    dfs(1,1); 
    dfss(1,1);
    cout << "Yes\n"; 
    rrep(i,n) cout << p[i] << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}