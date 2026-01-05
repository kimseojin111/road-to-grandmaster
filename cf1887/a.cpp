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

void solve(){
    int n,m; cin>>n>>m; 
    vector<int> a(n-1); 
    rep(i,n-1) cin>>a[i];
    vector<int> b(n);
    rep(i,n) cin>>b[i];
    auto get = [&](int x){
        auto aa = a; 
        aa.pb(x); 
        sort(all(b)); sort(all(aa));
        int re = 0; 
        int l = 1, r = n; 
        dbg(x,aa,b)
        while(l<=r){
            int m = l+r>>1; 
            bool flag = true; 
            rep(i,m) if(aa[i]>=b[n-m+i]) flag = false; 
            dbg(m,flag)
            if(flag) {
                re = m; l=m+1; 
            }
            else r=m-1; 
        }
        return n-re; 
    }; 
    int k = get(1); 
    dbg(k)
    // get(i) == k 인 최대의 i 
    int lim = 1; 
    int l = 2, r = m; 
    while(l<=r){
        int mm = l+r>>1; 
        dbg(mm,get(mm))
        if(get(mm)==k){
            lim = mm; l=mm+1; 
        }
        else r=mm-1; 
    }
    ll ans = (ll)k*lim + (ll)(k+1)*(m-lim); 
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