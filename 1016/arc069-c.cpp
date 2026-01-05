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

const int N = 100010; 
ll a[N]; 
ll ans[N]; 
ll sfx[N]; 

void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>a[i]; 
    vector<ll> tmp; 
    rrep(i,n) tmp.pb(a[i]); 
    sort(all(tmp)); 
    for(int i=n-1;i>=0;i--) sfx[i] = sfx[i+1] + tmp[i]; 
    auto qry = [&](ll x){
        auto i = lower_bound(all(tmp),x) - tmp.begin(); 
        return sfx[i] - x*(n-i); 
    }; 
    map<ll,vector<int>> m; 
    rrep(i,n) {
        m[a[i]].pb(i); 
    }
    int lidx = 1e9, lval = 1e9;  
    ll g = accumulate(a+1,a+n+1,0LL); 
    for(auto it = m.rbegin(); it != m.rend(); it++){
        auto& [key,v] = *it; 
        //dbg(key,v)
        //dbg(lidx,lval)
        if(v[0]>lidx) continue; 
        ll xx = qry(key) - qry(lval); 
        if(lidx<=n) ans[lidx] = xx; 
        g -= xx; 
        lval = key; lidx = v[0]; 
    }
    ans[lidx] = g; 
    rrep(i,n) cout << ans[i] << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}