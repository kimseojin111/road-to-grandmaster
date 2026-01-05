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
#include <atcoder/modint>
using namespace atcoder; 
using mint = modint998244353; 
const int N = 2010; 
ll a[N],b[N]; 
char s[N]; 
ll p[N]; 
mint dp[N][4]; 
// P : 0 S : 1 
// PP 0     PS   2     SP 1     SS 3 

void solve(){
    ll n,m; cin>>n>>m; 
    rrep(i,n) cin>>s[i]; 
    s[0] = 'P', s[n+1]='S'; 
    rrep(i,n) cin>>b[i]; 
    set<ll> v; 
    v.insert(b[1]); v.insert(b[n]); 
    for(int i=1;i+1<=n;i++) v.insert(b[i]+b[i+1]); 
    mint ans = 0; 
    auto get_shit = [&](int i, int bi, ll sum){
        // b==0 P 
        // b==1 S 
        if(bi==0){
            return make_pair(i,b[i]); 
        }
        else {
            return make_pair(i-1,sum-b[i]); 
        }
    };
    for(auto sum : v){
        b[n+1] = 0; b[0] = 0; 
        for(int i=0;i<=n;i++){
            rep(j,4){
                // alphabet check 
                dp[i][j] = 0; 
                int ii = j&1, iii = (j&2); 
                if(s[i]=='P'&&ii) continue; 
                if(s[i]=='S'&&(!ii)) continue; 
                if(s[i+1]=='P'&&iii) continue; 
                if(s[i+1]=='S'&&(!iii)) continue; 
                if(j==2){
                    if(b[i]+b[i+1]!=sum) continue; 
                }
                if(i==0){
                    dp[i][j] = 1; continue; 
                }
                rep(k,4){
                    int dd = (k&2)>>1; 
                    if(dp[i-1][k]==0) continue; 
                    if(ii!=dd) continue; 
                    vector<pair<int,ll>> lol; 
                    lol.pb(get_shit(i-1,(k&1),sum)); 
                    lol.pb(get_shit(i,dd,sum)); 
                    lol.pb(get_shit(i+1,iii,sum)); 
                    sort(all(lol)); 
                    bool fuck = false; 
                    for(int i=0;i<2;i++){
                        auto [p,pi] = lol[i]; 
                        auto [q,qi] = lol[i+1]; 
                        if(abs(pi-qi)>m*(q-p)) fuck = true; 
                    }
                    if(fuck) continue; 
                    dp[i][j] += dp[i-1][k]; 
                }
            }
        }
        ans += dp[n][2] + dp[n][3]; 
    }
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}