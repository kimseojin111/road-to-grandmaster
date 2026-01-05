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
using mint = modint998244353; 

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
vector<pair<int,int>> adj[N]; 
int deg[N]; 
int tmp[N]; 

void solve(){
    int n,m; cin>>n>>m; 
    rep(i,m){
        int a,b,c; cin>>a>>b>>c; 
        adj[c].pb({a,b}); 
        deg[a]++; deg[b]++;
    }
    mint ans = 1; 
    int remain = n; 
    int blank = 0; 
    rrep(i,n) if(deg[i]==0) blank++; 
    for(int i=n;i>=1;i--){
        dbg(i,blank)
        if(!adj[i].empty()){
            dbg(i,adj[i].size(),adj[i])
            vector<int> chk; 
            for(auto [a,b] : adj[i]){
                tmp[a]++; tmp[b]++; chk.pb(a); chk.pb(b); 
                deg[a]--; deg[b]--; 
            }
            vector<int> d2; 
            sort(all(chk)); chk.erase(unique(all(chk)),chk.end()); 
            for(auto x : chk) if(tmp[x]>=2) d2.pb(x); 
            if(d2.size()>=2){
                cout<<0; return; 
            }
            if(d2.size()){
                int u = d2[0]; if(deg[u]) {
                    cout<<0; return; 
                } 
                for(auto x : chk) if(x!=u&&deg[x]==0) blank++; 
            }  
            else {
                if(adj[i].size()>=2){
                    cout<<0; return; 
                }
                auto [p,q] = adj[i][0]; 
                if(deg[p]&&deg[q]){
                    cout<<0; return; 
                }
                if(!deg[p]&&!deg[q]){
                    ans *= 2; blank++; 
                } 
            }
            for(auto x : chk) tmp[x] = 0; 
        }
        else {
            if(blank==0) {
                cout << 0; return; 
            }
            ans *= blank; blank--; 
        }
    }
    cout << ans.val();
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}