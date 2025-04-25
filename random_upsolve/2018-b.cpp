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

#include <atcoder/segtree>
using namespace atcoder; 

const int inf = 1e7; 

struct node{
    // 01 왼끝 01 오른끝 01 내가 max를 포함? 
    int dp[2][2][2]; 
    node() {
        rep(i,2) rep(j,2) rep(k,2) dp[i][j][k] = -inf; 
        dp[0][0][0] = 0; 
    }
    node(int p){
        // p 1 max else 0 
        rep(i,2) rep(j,2) rep(k,2) dp[i][j][k] = -inf; 
        dp[0][0][0] = 0; 
        if(p) dp[1][1][1] = 1; 
        else dp[1][1][0] = 1; 
    }
};

node e() {
    node re; return re; 
}

node op(node a, node b){
    node re; 
    rep(i,2) rep(j,2) rep(k,2) rep(p,2) rep(q,2) rep(r,2){
        if(j==1&&p==1) continue; 
        re.dp[i][q][k|r] = max(re.dp[i][q][k|r],a.dp[i][j][k]+b.dp[p][q][r]); 
    }
    return re; 
}

void solve(){
    int n; cin>>n; 
    vector<pair<int,int>> v; 
    int mx = -1; 
    vector<int> a(n); rep(i,n) {
        cin >> a[i]; v.pb({a[i],i}); mx = max(mx,a[i]); 
    }
    sort(all(v),[](auto a, auto b){
        return a.first > b.first; 
    }); 
    segtree<node,op,e> seg(n); 
    ll ans = 0; 
    for(int i=0;i<v.size();i++){
        auto [aj,j] = v[i]; 
        if(aj==mx){
            seg.set(j,node(1)); 
        }
        else seg.set(j,node(0)); 
        auto f = seg.all_prod(); 
        ll shit = 0; 
        rep(p,2) rep(q,2) shit = max(shit,(ll)f.dp[p][q][1]); 
        ans = max(ans,shit+mx+aj); 
    }
    cout << ans << "\n";

}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}