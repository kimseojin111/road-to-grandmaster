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

void solve(){
    int n,m; cin>>n>>m; 
    vector<vector<int>> G(n,vector<int>(m,0)); 
    rep(i,n){
        string s; cin>>s; 
        rep(j,m) G[i][j] = s[j]=='1';  
    } 
    bool swp = n>m; 
    if(swp){
        vector<vector<int>> T(m,vector<int>(n,0)); 
        rep(i,n) rep(j,m) T[j][i] = G[i][j]; 
        swap(n,m); 
        swap(G,T); 
    }
    const int inf = 99999999; 
    vector<vector<int>> ans(n,vector<int>(m,inf));
    for(int i=0;i<n-1;i++){
        vector<int> tmp(m,inf); 
        for(int j=n-1;j>i;j--){
            vector<int> u; 
            rep(k,m) if(G[i][k]&&G[j][k]) u.pb(k); 
            for(int t=0;t+1<u.size();t++){
                int l = u[t], r = u[t+1]; 
                for(int d=l;d<=r;d++) tmp[d] = min(tmp[d],(j-i+1)*(r-l+1)); 
            }
            rep(k,m) ans[j][k] = min(ans[j][k],tmp[k]); 
        }
        rep(k,m) ans[i][k] = min(ans[i][k],tmp[k]); 
    } 
    if(!swp){
        rep(i,n) rep(j,m) {
            cout << (ans[i][j]==inf ? 0 : ans[i][j]) << " \n"[j==m-1]; 
        }
    }
    else {
        vector<vector<int>> T(m,vector<int>(n,0)); 
        rep(i,n) rep(j,m) T[j][i] = ans[i][j]; 
        swap(n,m); 
        rep(i,n) rep(j,m) cout << (T[i][j]==inf ? 0 : T[i][j]) << " \n"[j==m-1]; 
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}