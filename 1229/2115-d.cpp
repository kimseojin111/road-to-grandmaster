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
ll a[N], b[N]; 
ll sex[62]; 

void solve(){
    int n; cin>>n; 
    rep(i,n) cin>>a[i]; 
    rep(i,n) cin>>b[i]; 
    string c; cin>>c; 
    rep(i,n) {
        a[i] ^= b[i]; 
    }
    // start -> b[0] ^ ... b[n-1] 
    // operation -> a[i] ^ b[i] 
    for(int i=0;i<60;i++) sex[i] = 1LL<<i; 
    sex[60] = 0; 
    for(int i=n-1;i>=0;i--){
        ll shit = 0; // Aa[i] 
        for(int j=0;j<60;j++) if((a[i]>>j)&1) shit ^= sex[j]; 
        dbg(shit)
        if(shit==0LL) continue; 
        int lb = 63-__builtin_clzll(shit);
        vector<int> fuck; 
        rep(j,61) if((sex[j]>>lb)&1LL) fuck.pb(j); 
        dbg(fuck)
        if(c[i]=='0'){
            // minimize 
            // min(Ax+b,A(x+a[i])+b) -> Ax+b + A(a[i]) (:=shit) 짝수개 -> 모두 shit 넣기?
            for(auto x : fuck) sex[x] ^= shit; 
        } else {
            for(auto x : fuck) sex[x] ^= shit; 
            sex[60] ^= shit; 
        }
    }
    ll st = 0; 
    rep(i,n) st ^= b[i]; 
    ll shit = 0; 
    rep(j,60) if((st>>j)&1) shit ^= sex[j]; 
    shit ^= sex[60]; 
    cout << shit << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}