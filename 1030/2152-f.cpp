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
    int n,z,q; cin>>n>>z; 
    vector<int> x(n+1); 
    rep(i,n) cin>>x[i]; 
    int logn = 20; 
    vector<vector<int>> g(logn, vector<int>(n+1,0)); 
    g[0][n] = n; 
    for(int i=0,j=0;i<n;i++){
        while(j<n&&x[j]<=x[i]+z) j++; 
        g[0][i] = j; 
    }
    for(int k=1;k<logn;k++) rep(i,n+1) g[k][i] = g[k-1][g[k-1][i]]; 
    auto lca = [&](int i, int j)->pair<int,int>{
        // g^k[i] == g^k[j] 인 최소의 k 와 g^k[i] 를 반환 
        if(i==j){
            return {0,i}; 
        }
        int k = 0; 
        for(int b=logn-1;b>=0;b--) {
            if(g[b][i]!=g[b][j]){
                i = g[b][i]; j = g[b][j]; 
                k |= 1<<b; // ??????? 
            }
        }
        return {k+1,g[0][i]}; 
    }; 
    vector<vector<int>> ne(logn,vector<int>(n+1,0)); 
    vector<vector<int>> cost(logn, vector<int>(n+1,0)); 
    // i, i+1   -> ne[i] 
    rep(i,n+1){
        if(i==n) ne[0][i] = n; 
        else {
            int mn,mlen; 
            int j = i+1; 
            auto d = lca(i,j);
            mn = d.second, mlen = d.first*2; 
            int ii = g[0][i]; 
            auto dd = lca(ii,j); 
            if(dd.second<mn){
                mn = dd.second; mlen = dd.first*2+1; 
            }
            ne[0][i] = mn; 
            cost[0][i] = mlen; 
        }
        dbg(i,ne[0][i],cost[0][i])
    }
    for(int b=1;b<logn;b++) rep(i,n+1){
        ne[b][i] = ne[b-1][ne[b-1][i]]; 
        cost[b][i] = cost[b-1][i] + cost[b-1][ne[b-1][i]]; 
    }
    cin>>q; 
    while(q--){
        int l,r; cin>>l>>r; l--; r--; 
        if(l==r){
            cout << 1 << "\n"; continue; 
        }
        int st = l; 
        int ans = 0; 
        for(int b=logn-1;b>=0;b--) if(ne[b][st]<=r) {
            ans += cost[b][st]; st = ne[b][st]; 
        }
        // l,l+1 로 시작해서 r 이하까지 가기. 
        dbg(st)
        auto calc = [&](int s, int e){
            int re = 0; 
            if(s>e) return 0; 
            for(int b=logn-1;b>=0;b--) if(g[b][s]<=e) {
                s = g[b][s]; re |= 1<<b; 
            }
            return re+1; 
        }; 
        ans += calc(st,r) + calc(st+1,r); 
        cout << ans << "\n";
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