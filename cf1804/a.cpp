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

const int N = 22; 
int adj[N][N]; 

int dp[1<<N][N]; 
int fuck[N]; 
int shit[1<<N]; 

void solve(){
    int n; cin>>n; 
    int m; cin>>m; 
    while(m--){
        int a,b; cin>>a>>b;
        a--; b--; 
        adj[a][b] = 1, adj[b][a] = 1; 
        fuck[a] |= (1<<b); 
        fuck[b] |= (1<<a); 
    }
    for(int i=1;i<(1<<n);i++){
        int k = i&(i-1); 
        int t = i-k; 
        if(k==0){
            int j =0; 
            while((1<<j)!=i)j++; 
            shit[i] = fuck[j];   
        }
        else {
            shit[i] = shit[k] | shit[t]; 
        }
    }
    memset(dp,-1,sizeof(dp));
    for(int k=0;k<n;k++) dp[1<<k][k] = k; 
    auto ans = [&](int msk, int ed) {
        vector<int> cyc; 
        while(1){
            cyc.pb(ed); 
            int u = dp[msk][ed]; 
            if(u==ed) break; 
            msk -= (1<<ed); 
            ed = u; 
        }
        dbg(cyc)
        int a[N] = {0,}; 
        for(auto x : cyc) rep(i,n) {
            if(adj[i][x]) a[i] = x; 
        }
        for(int i=0;i<cyc.size();i++){
            int j = i+1; 
            if(j==cyc.size()) j =0; 
            a[cyc[i]] = cyc[j]; 
        }
        cout << "Yes\n"; 
        rep(i,n) cout << (a[i]+1) << " ";
    }; 

    for(int msk=1;msk<(1<<n);msk++){
        int st = 0; 
        while(((msk>>st)&1)==0)st++; 
        if(msk==(1<<st)) continue; 
        dbg(msk,st)
        for(int j=st+1;j<n;j++){
            if((msk>>j)&1){
                //for(auto ne : adj[j]) 
                rep(ne,n) if(adj[j][ne]){
                    int go = (msk>>ne)&1; 
                    if(go&&dp[msk-(1<<j)][ne]!=-1) {
                        dp[msk][j] = ne; 
                        dbg(msk,j)
                        if(adj[st][j]&&shit[msk]==((1<<n)-1)){
                            // msk 가 ans 
                            ans(msk,j); return; 
                        }
                    }
                    
                }
            }
        }
    }
    cout << "No\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}