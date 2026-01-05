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

const int N = 110; 
vector<int> p[N]; 
int dp[N*N]; 

void init(int n){
    rrep(i,n*n+2) dp[i] = 0;
    rrep(i,n+1) p[i].clear(); 
}

void solve(){
    int n; cin>>n; 
    int N = n*n+1; 
    init(n);
    rrep(i,N) dp[i] = n+1; 
    auto qry = [&](vector<int>& t){
        cout << "? "; 
        cout << t.size() << " "; 
        for(auto x : t) cout << x << " "; 
        cout << endl; 
        int c; cin>>c; 
        vector<int> re; 
        rep(_,c) {
            int x; cin>>x; re.pb(x); 
        }
        dbg(re)
        return re; 
    }; 
    auto fuck = [&](vector<int> t){
        sort(all(t)); 
        cout << "! "; 
        rep(i,n+1) cout << t[i] << " "; 
        cout << endl; 
    }; 
    rrep(i,n){
        vector<int> tmp; 
        rrep(j,N) if(dp[j]==n+1) tmp.pb(j); 
        auto v = qry(tmp); 
        p[i] = v; 
        if(v.size()>n){
            fuck(v); return; 
        } else {
            for(auto x : v) dp[x] = i; 
        }
    }
    dbg(n)
    vector<int> u; 
    rrep(i,N) if(dp[i]==n+1) {
        dbg(i,dp[i],dp[i]==n+1)
        u.pb(i); break; 
    }
    dbg(u)
    for(int j=n;j>=1;j--){
        auto it = lower_bound(all(p[j]),u.back()); 
        u.pb(*prev(it)); 
    }
    fuck(u); 
    return; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}