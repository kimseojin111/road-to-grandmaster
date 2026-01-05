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
 
int l[1<<20],r[1<<20]; 
multiset<int> shit[1<<20]; 
ll dp[1<<20];   

void merge(multiset<int>& lv, multiset<int>& rv){
    if(lv.size()<rv.size()) swap(lv,rv); 
    for(auto x : rv) lv.insert(x); 
}

void dfs(int node, int s, int e){
    if(e-s==1){
        //dbg(node,l[node<<1],l[(node<<1)+1])
        dp[node] = 0; 
        shit[node].insert(l[node<<1]); 
        shit[node].insert(l[(node<<1)+1]); 
        int lx = max(l[node<<1],l[(node<<1)|1]); 
        for(int rv : {r[node<<1],r[(node<<1)|1]}) {
            if(rv<lx) {
                shit[node].erase(prev(shit[node].end())); 
                shit[node].insert(rv); 
                dp[node] += (lx-rv); 
            }
        }
        r[node] = max(r[node<<1],r[(node<<1)|1]); 
    } else {
        int m = s+e>>1; 
        dfs(node<<1,s,m); dfs((node<<1)|1,m+1,e); 
        int ln = node<<1, rn = (node<<1)|1; 
        r[node] = max(r[ln],r[rn]); 
        dp[node] = dp[ln]+dp[rn]; 
        shit[node] = shit[ln]; 
        merge(shit[node],shit[rn]); 
        int lx = *shit[node].rbegin(); 
        for(int rv : {r[node<<1],r[(node<<1)|1]}) {
            //dbg(rv,lx,"????")
            if(rv<lx) {
                shit[node].erase(prev(shit[node].end())); 
                shit[node].insert(rv); 
                dp[node] += (lx-rv); 
            }
        }
    }
    //dbg(node,s,e,dp[node],shit[node])
}

void solve(){
    int n; cin>>n; 
    int N = 1<<n; 
    rep(i,N) {
        cin>>l[N+i]>>r[N+i]; 
        //dbg(N+i)
    }
    dfs(1,1,N); 
    cout << dp[1]; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}