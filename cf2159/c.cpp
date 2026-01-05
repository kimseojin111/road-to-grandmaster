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
#include <atcoder/modint> 
using namespace atcoder; 
using mint = modint1000000007; 

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
void __print(mint x) {cerr << (x.val());}

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

const int N = 400010; 
mint dp[N],dp1[N]; 

void solve(){
    int n; cin>>n; 
    vector<int> a(n+1); 
    rep(i,n+1) cin>>a[i];
    rrep(i,n) if(a[i]>n){
        cout << 0 << "\n"; return; 
    } 
    rrep(i,n){
        if(a[i]>0){
            int ne = a[i]; 
            if(a[ne]==-1) a[ne] = i; 
            if(a[ne]==i) continue; 
            if(a[ne]!=i){
                cout << 0 << "\n"; return; 
            }
        }
    }
    rrep(i,n) if(a[i]>0) {
        int ne = a[i]; 
        if(a[ne]!=i) {
            cout << 0 << "\n"; return; 
        }
    }
    vector<int> d; 
    rrep(i,n) if(a[i]==-1) d.pb(i); 
    if(a[n]!=-1) {
        cout << dp[d.size()].val() << "\n"; 
    } else {
        cout << dp1[d.size()].val() << "\n";
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
    // dp -> 그냥 dp1 -> 무조건 마지막은 자기 자신 
    dp[0] = 1; 
    dp[1] = 2; 
    for(int i=2;i<N;i++){
        dp[i] = dp[i-1]*2 + (i-1)*dp[i-2];  
    }
    dp1[1] = 1; 
    for(int i=2;i<N;i++){
        dp1[i] = dp[i-1] + (i-1)*dp[i-2]; 
    }

   while(t--) solve(); 
   return 0;
}