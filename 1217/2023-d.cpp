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

const int N = 400010; 
vector<int> w[101]; 
double dp[N]; 
double ndp[N]; 

void solve(){
    int n; cin>>n; 
    rep(i,n){
        int p,x; cin>>p>>x; 
        w[p].pb(x); 
    }
    for(int i=1;i<=100;i++){
        sort(all(w[i]),[](int a, int b){
            return a>b; 
        }); 
    }
    ll init = 0; 
    for(auto x : w[100]) init += x; 
    if(init>200000){
        cout << init; return; 
    }
    dp[init] = 1; 
    for(int i=1;i<100;i++) {
        double p = (double)i/100; 
        int j = 0; 
        while(1){
            // p^j * j  > p^(j+1) * (j+1) 
            // j > p * (j+1) 
            if(j<=p*(j+1)) j++; 
            else break; 
        }
        //dbg(i,j)
        while(w[i].size()>j) w[i].pop_back(); 
        for(auto x : w[i]){
            rep(i,N) ndp[i] = dp[i]; 
            rep(i,N) {
                int ne = i+x; 
                if(ne<N){
                    ndp[ne] = max(ndp[ne],dp[i]*p); 
                }
            }
            rep(i,N) dp[i] = ndp[i]; 
        }
    }
    double ans = 0; 
    rep(i,N) ans = max(ans,dp[i]*i); 
    cout << fixed; 
    cout.precision(10); 
    cout << ans; 
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) solve(); 
    return 0;
}