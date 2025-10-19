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

int a[N]; 
set<int> fuck[N]; 
set<pair<int,int>> use[N]; 
int par[N]; 
int has[N]; // 0을 포함 
vector<int> adj[N]; 
int vis[N]; 

void init(int n){
    rrep(i,n){
        adj[i].clear(); fuck[i].clear(); use[i].clear(); 
        par[i] = i; has[i] = 0; vis[i] = 0; 
    }
}

int find(int i){
    if(i==par[i]) return i; 
    return par[i] = find(par[i]); 
}

void merge(int i, int j){
    i = find(i), j = find(j); 
    if(i==j) return; 
    if((fuck[i].size()+use[i].size())>(fuck[j].size()+use[j].size())) swap(i,j); 
    par[i] = j; 
    for(auto x : fuck[i]) fuck[j].insert(x);
    for(auto x : use[i]) use[j].insert(x);   
}

void solve(){
    int n,m; cin>>n>>m; 
    init(n); 
    rrep(i,n) {
        cin>>a[i]; if(a[i]==0) has[i] = 1; 
    }
    rep(i,m){
        int p,q; cin>>p>>q; adj[p].pb(q); adj[q].pb(p); 
    }   
    rrep(i,n) if(a[i]==0&&!vis[i]) {
        int p = find(i); 
        use[p].insert({a[p],p}); 
        while(!use[p].empty()){
            auto [at,t] = *use[p].begin(); 
            if(at>fuck[p].size()) break; 
            use[p].erase(use[p].begin()); 
            if(fuck[p].find(t)!=fuck[p].end()) continue; 
            if(fuck[p].size()>=at){
                if(vis[t]){
                    merge(p,t); 
                    p = find(p); 
                }
                else {
                    par[t] = p; 
                    fuck[p].insert(t); 
                    for(auto x : adj[t]) {
                        use[p].insert({a[x],x}); 
                    }
                    vis[t] = 1; 
                }
            }
        }
    }
    rrep(i,n) {
        int x = find(i); if(fuck[x].size()==n) {
            cout << "YES\n"; return; 
        }
    }
    cout << "NO\n"; return; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}