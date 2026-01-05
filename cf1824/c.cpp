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

const int N = 100010;
int a[N];
vector<int> adj[N]; 

struct xor_set{
    set<int> s; 
    int key; 
}; 

int dp[N]; 
xor_set dpv[N]; 

void merge(xor_set &a, xor_set& b, map<int,int>&M){
    if(a.s.size()<b.s.size()) {
        swap(a,b); 
    }   
    // a 가 par 이다. 
    for(auto x:b.s){
        int xx = x^b.key^a.key; 
        if(a.s.find(xx)!=a.s.end()){
            M[x^b.key]++; 
        }
        else {
            a.s.insert(xx); 
        }
    }
}

void dfs(int v, int p){
    dbg(v)
    map<int,int> M; 
    int c = 0; 
    for(auto ne : adj[v]) if(ne!=p){
        dfs(ne,v); 
        c++; 
        merge(dpv[v],dpv[ne],M); 
        dp[v] += dp[ne]; 
    }
    if(c==0){
        dpv[v].key = a[v]; 
        dpv[v].s.insert(0); 
        return; 
    }
    if(M.empty()){
        dp[v] += max(c-1,0); 
        dpv[v].key ^= a[v]; return; 
    }
    else {
        vector<int> can; 
        int mx = 0; 
        for(auto [k,v]:M) {
            if(mx<v){
                can.clear(); can.pb(k); mx=v;
            }
            else if(mx==v){
                can.pb(k); 
            }
        }
        dp[v] = dp[v] + (c-mx-1); 
        dpv[v].key = a[v]; 
        dpv[v].s.clear(); 
        for(auto x : can) dpv[v].s.insert(x); 
    }
    dbg(v)
}

void solve(){
    int n; cin>>n;
    rrep(i,n) cin>>a[i];
    rep(i,n-1){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
    }
    rrep(i,n) dpv[i].key = 0; 
    dfs(1,1); 
    int ans = dp[1]+1; 
    if(dpv[1].s.find(dpv[1].key)!=dpv[1].s.end()) ans--;
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