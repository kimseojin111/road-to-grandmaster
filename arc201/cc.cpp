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

const int N = 500010; 
int l[N],r[N]; 
#include <atcoder/modint>
using namespace atcoder; 
using mint = modint998244353; 

mint dp[N]; 
int cnt[N]; 
int sz[N]; 
int pv; 
void dfs(string s){
    int now = 0; 
    vector<int> v; 
    for(auto c : s){
        int f = c=='A'; 
        v.pb(now);
        sz[now]++;  
        if(f){
            if(l[now]==-1) l[now] = ++pv; 
            now = l[now]; 
        }
        else {
            if(r[now]==-1) r[now] = ++pv; 
            now = r[now]; 
        }
    }
    v.pb(now); 
    cnt[now]++; 
    sz[now]++; 
    reverse(all(v)); 
    for(auto x : v){
        dp[x] = 0; 
        if(cnt[x]){
            mint two = 2; dp[x] += two.pow(sz[x]-1); 
        }
        if(l[x]!=-1&&r[x]!=-1) dp[x] += dp[l[x]]*dp[r[x]]; 
    }
}

void solve(){
    int n; cin>>n; 
    memset(l,-1,sizeof(l)); 
    memset(r,-1,sizeof(r)); 
    rep(i,n){
        string s; cin>>s; 
        dfs(s); 
        cout << dp[0].val() << "\n";
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}