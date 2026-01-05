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

vector<ll> shit[70]; 

ll dp(int i, ll w){
    dbg(i,w)
    if(w==0) return 0; 
    sort(all(shit[i]),[](ll p, ll q){
        return p>q; 
    }); 
    if(shit[i].empty()) return dp(i+1,w>>1); 
    if((w&1)){
        ll ans = shit[i][0]; 
        dbg(i,ans)
        w -= 1; 
        for(int j=1;j<shit[i].size();j+=2){
            ll now = shit[i][j] + (j==shit[i].size()-1 ? 0 : shit[i][j+1]); 
            shit[i+1].pb(now); 
        }
        return ans + dp(i+1,w>>1); 
    } 
    for(int j=0;j<shit[i].size();j+=2){
        ll now = shit[i][j] + (j==shit[i].size()-1 ? 0 : shit[i][j+1]); 
        shit[i+1].pb(now); 
    }
    return dp(i+1,w>>1); 
}

void solve(){
    rep(i,70) shit[i].clear(); 
    int n; cin>>n; ll w; cin>>w; 
    rep(i,n){
        int x,w; cin>>x>>w; shit[x].pb(w); 
    }
    cout << dp(0,w) << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}