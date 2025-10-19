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


const int N = 1000100; 
vector<int> pos[30]; 
int a[N]; 

int dp[N]; 

void solve(){
    int n,k; cin>>n>>k; 
    string s; cin>>s; 
    rep(i,n){
        int x = s[i]-'a'; 
        a[i] = x; 
        pos[x].pb(i); 
    }
    map<int,int> g; 
    rep(i,k) g[i] = n; 
    dp[n] = 1; 
    for(int i=n-1;i>=0;i--){
        g[a[i]] = i; 
        int tp = -1; 
        for(auto [k,v]:g) tp = max(tp,v); 
        if(tp==n) dp[i] = 1; 
        else {
            dp[i] = dp[tp+1]+1; 
        }
    }
    int q; cin>>q; 
    auto ans = [&](string t){
        int now = 0; 
        for(int i=0;i<t.size();i++){
            int k = t[i] - 'a'; 
            auto it = lower_bound(all(pos[k]),now); 
            if(it==pos[k].end()){
                cout << 0 << "\n"; return; 
            }
            now = (*it)+1; 
        }
        dbg(now,dp[now])
        if(now==n) cout << 1 << "\n"; 
        else cout << dp[now] << "\n";
    }; 
    while(q--){
        string t; cin>>t; 
        ans(t); 
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