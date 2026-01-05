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
int a[N]; 
vector<int> cyc[N]; 
int pv; 
bool vis[N]; 
int cnt[N]; 

void init(int n){
    rrep(i,n) {
        cyc[i].clear(); vis[i]=cnt[i]=0; 
    }
    pv = 0; 
}

void solve(){
    int n,k; cin>>n>>k; 
    init(n);
    rrep(i,n) cin>>a[i]; 
    if(k==1){
        bool f = true; 
        rrep(i,n) if(a[i]!=i) f=false; 
        cout << (f ? "YES":"NO") << "\n"; return; 
    }
    auto dfs = [&](int v) {
        if(vis[v]) return; 
        int s = v; 
        while(!vis[s]){
            vis[s] = 1; 
            s = a[s]; 
        }
        if(cnt[s]!=0){
            int dd = cnt[s]; 
            while(cnt[v]==0){
                cnt[v] = dd; 
                v = a[v]; 
            }
            return; 
        }
        int dd = ++pv; 
        while(cnt[s]==0){
            cyc[dd].pb(s); 
            cnt[s] = pv; 
            s = a[s]; 
        }
        while(cnt[v]==0){
            cnt[v] = dd; 
            v = a[v]; 
        }
    }; 
    rrep(i,n) dfs(i); 
    for(int i=1;i<=pv;i++) if(cyc[i].size()!=k) {
        cout << "NO\n"; return; 
    }
    cout << "YES\n"; 
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}