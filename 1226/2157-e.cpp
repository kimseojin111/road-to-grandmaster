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
    int n,k; cin>>n>>k; 
    vector<int> cnt(5*n); 
    set<int> unused; 
    set<int> chk; 
    for(int i=1;i<5*n;i++) unused.insert(i); 
    rep(i,n){
        int x; cin>>x; 
        cnt[x]++; 
        if(unused.count(x)) unused.erase(x); 
        if(cnt[x]>=2) chk.insert(x); 
    }
    int ans = 0; 
    for(int i=n*2;i>=1;i--){
        if(cnt[i]>k){
            int sz = cnt[i] - 1; 
            dbg(i,sz)
            int mk = i; 
            chk.erase(i); 
            cnt[i] = 1; 
            while(sz>k-1){
                auto i1 = unused.lower_bound(i); 
                auto i2 = chk.upper_bound(i); 
                int t = *i1; 
                if(i2!=chk.end()) t = min(t,*i2); 
                dbg(sz,t,cnt[t])
                if(cnt[t]==0){
                    sz--; mk = t; 
                    cnt[t] = 1; 
                    unused.erase(t); continue; 
                } else {
                    sz += cnt[t] - 1; 
                    cnt[t] = 1; mk = t; 
                    chk.erase(t); continue; 
                }
            }
            if(k>1){
                chk.insert(mk); 
            }
            dbg(i,mk)
            cnt[mk] = k; 
            ans = max(ans,mk-i); 
        }
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