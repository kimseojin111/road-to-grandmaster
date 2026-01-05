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

int adj[3010][3010]; 
bool vis[3010]; 
int chk[3010];

void solve(){
    int n,m; cin>>n>>m; 
    if(n>3000){
        rep(i,m){
            int a,b; cin>>a>>b; 
        }
        cout << "No\n"; return; 
    }
    rrep(i,n) rrep(j,n) if(i!=j) adj[i][j] = 1; 
    rrep(i,n) vis[i]=0; 
    rep(i,m){
        int a,b; cin>>a>>b; adj[a][b] = adj[b][a] = 0; 
    }
    // chk bipartite
    rrep(i,n) if(!vis[i]){
        queue<int> q; q.push(i); 
        while(!q.empty()) {
            int f = q.front(); q.pop(); 
            if(vis[f]) continue; 
            vis[f] = 1; 
            rrep(i,n) if(adj[f][i]&&!vis[i]){
                q.push(i); chk[i] = chk[f]^1; 
            }
        }
    }
    bool flag = true; 
    rrep(i,n) rrep(j,n) if(adj[i][j]&&chk[i]==chk[j]) flag = false; 
    if(flag) cout << "Yes\n"; 
    else cout << "No\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}