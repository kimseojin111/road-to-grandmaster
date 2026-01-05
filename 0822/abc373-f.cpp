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

const int N = 3010;
vector<ll> v[N]; 
ll dp[N]; 

void solve(){
    int n, w; cin>>n>>w; 
    rrep(i,n){
        ll w,vi; cin>>w>>vi; v[w].pb(vi); 
    }
    for(int i=1;i<=w;i++) if(!v[i].empty()) {
        // 무게 i 인 것 
        // 지금 k번 썼을 때 다음 이득 : v[i][x] - (k+1)*(k+1) + k*k  = v[i][x] - 2k -1 
        vector<ll> tmp; 
        priority_queue<array<ll,3>> pq; 
        dbg(v[i])
        for(int j=0;j<v[i].size();j++){
            dbg(v[i][j]-1)
            pq.push({v[i][j]-1,j,0}); 
        }
        dbg(i,tmp)
        rep(_,w/i){
            auto [ne,j,pv] = pq.top(); pq.pop(); 
            tmp.pb(ne); 
            pq.push({v[i][j]-2*pv-3,j,pv+1}); 
        }
        dbg(i,tmp)
        for(auto x : tmp) for(int j=w;j>=i;j--) dp[j] = max(dp[j],dp[j-i]+x); 
    }
    cout << *max_element(dp,dp+w+1); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}