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

const int N = 500010; 
ll dp[N][8]; 
bool vis[N][8]; 

void solve(){
    int a,b,c,m,k; cin>>a>>b>>c>>m>>k; 
    dbg(a,b,c)
    // a, b, c, k, 
    rep(i,m) rep(j,8) {
        dp[i][j] = 2e18; vis[i][j] = false; 
    }
    dp[0][0] = 0; 
    priority_queue<array<ll,3>,vector<array<ll,3>>,greater<>> pq; 
    pq.push({0,0,0}); 
    while(!pq.empty()){
        auto [dpij,i,msk] = pq.top(); pq.pop(); 
        if(vis[i][msk]) continue; 
        dp[i][msk] = dpij; 
        vis[i][msk] = 1; 
       //dbg(i,msk,dpij)
        vis[i][msk] = 1; 
        {
            int ne = (i*2)%m; 
            ll ndp = dpij + 1LL * __builtin_popcount(msk) * k; 
            pq.push({ndp,ne,msk}); 
        }
        {
            int nmsk = msk | 1; 
            ll ndp = dpij + a; 
            int ne = (i+a)%m; 
            pq.push({ndp,ne,nmsk}); 
        }
        {
            int nmsk = msk | 2; 
            ll ndp = dpij + b; 
            int ne = (i+b)%m; 
            pq.push({ndp,ne,nmsk}); 
        }
        {
            int nmsk = msk | 4; 
            ll ndp = dpij + c; 
            int ne = (i+c)%m; 
            pq.push({ndp,ne,nmsk}); 
        }
    }
    dbg(dp[0][7])
    cout << (dp[0][7]-a-b-c) << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}