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

const int N = 20; 
int adj[N]; 
bool dp[1<<N][N]; 
int a[N]; 

void solve(){
    int n,m; cin>>n>>m; 
    rep(i,m){
        int a,b; cin>>a>>b; 
        a--; b--; adj[a]|=(1<<b); adj[b]|=(1<<a); 
    }
    // dp[bit][s] -> 끝 s로 가능 
    rep(i,n){
        dp[1<<i][i] = 1; 
    }
    auto ans = [&](int cyc, int ed){
        int st = __builtin_ctz(cyc); 
        int bit = cyc; 
        vector<int> f; 
        while(1){
            f.pb(ed); 
            if(ed==st) break; 
            bit ^= (1<<ed); 
            rep(i,20){
                if(dp[bit][i]&&((adj[i]>>ed)&1)){
                    ed = i; break; 
                }
            }
        }
        for(int i=0;i<f.size();i++){
            int ne = f[(i+1)%f.size()]; 
            a[f[i]] = ne; 
        }
        int xx = 0; 
        for(auto x : f) xx |= (1<<x); 
        dbg(f)
        for(auto x : f){
            rep(i,n) if((adj[x]>>i)&1){
                if(((xx>>i)&1)==0) a[i] = x; 
                dbg(x,i,"wtf??")
            }
        }
        cout << "Yes\n"; 
        rep(i,n) cout << (a[i]+1) << " "; 
        return; 
    }; 
    rep(bit,(1<<n)) rep(i,n) if((bit>>i)&1) if(dp[bit][i]){
        dbg(bit,i)
        int lb = __builtin_ctz(bit); 
        if(__builtin_popcount(bit)>1){
            int d = 0; 
            if((adj[i]>>lb)&1){
                rep(j,n) if((bit>>j)&1) d|=adj[j]; 
            }
            if(d==(1<<n)-1){
                ans(bit,i); 
                return; 
            }
        }
        for(int j=lb+1;j<n;j++) if((adj[i]>>j)&1) if(((bit>>j)&1)==0) {
            dp[bit|(1<<j)][j] = 1; 
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