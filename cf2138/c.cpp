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

const int N = 200010; 
int p[N]; 
int h[N]; 
vector<int> adj[N]; 
int cnt[N]; 

void init(int n){
    rrep(i,n){
        p[i]=h[i]=0;adj[i].clear();  cnt[i] = 0; 
    }
    cnt[0] = 0; 
}

void dfs(int v){
    if(adj[v].empty()) return; 
    for(auto ne : adj[v]){
        h[ne] = h[v]+1; 
        dfs(ne); 
    }
}

using u64 = unsigned long long;

static void or_shift(vector<u64>& b, int s){
    if (s <= 0) return;
    const int n = (int)b.size();
    vector<u64> orig = b;

    int whole = s >> 6;       
    int rem   = s & 63;       

    if (rem == 0) {
        for (int i = n - 1; i >= whole; --i)
            b[i] |= orig[i - whole];
    } else {
        for (int i = n - 1; i > whole; --i) {
            u64 hi = orig[i - whole] << rem;
            u64 lo = orig[i - whole - 1] >> (64 - rem);
            b[i] |= (hi | lo);
        }
        if (n - 1 >= whole) {
            b[whole] |= (orig[0] << rem);
        }
    }
}

static int find_prev_leq(const vector<u64>& b, int k){
    if (k < 0) return -1;
    int idx = k >> 6;
    int off = k & 63;

    if (idx >= (int)b.size()) idx = (int)b.size() - 1;

    if (idx >= 0){
        u64 mask = (off == 63) ? ~0ULL : ((1ULL << (off + 1)) - 1);
        u64 w = b[idx] & mask;
        if (w) return (idx << 6) + (63 - __builtin_clzll(w));
        for (int i = idx - 1; i >= 0; --i){
            if (b[i]) return (i << 6) + (63 - __builtin_clzll(b[i]));
        }
    }
    return -1;
}

void solve(){
    int n,k; cin>>n>>k;     
    init(n); 
    p[1] = 1; 
    for(int i=2;i<=n;i++) {
        cin>>p[i]; adj[p[i]].pb(i); 
    }
    dfs(1); 
    int D = n+100; 
    rrep(i,n){
        if(adj[i].empty())D = min(D,h[i]); 
        cnt[h[i]]++; 
    }
    int W = (k>>6)+3; 
    vector<u64> b(W, 0);
    int ans = 0;  
    b[0] |= 1ULL; 
    int al = 0; 
    for(int i=0;i<=D;i++){
        or_shift(b,cnt[i]); 
        al += cnt[i]; 
        int pos = find_prev_leq(b, k);
        if(al-pos<=n-k) ans = i+1; 
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