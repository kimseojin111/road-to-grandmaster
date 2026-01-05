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

#include <atcoder/segtree>
using namespace atcoder; 

int op(int a, int b) {
    return max(a,b); 
}

int e() {
    return -1e9; 
}

const int N = 200010; 
int l[N],r[N]; 
vector<int> ad[N], er[N]; 
int dp[N][12]; 

void solve(){
    int n,m,k; cin>>n>>m>>k;
    for(int i=0; i<=n+1; i++) {
        ad[i].clear(); er[i].clear(); 
    } 
    rrep(i,n) for(int j=0;j<=k;j++) dp[i][j] = -1e9; 
    rep(i,m) {
        cin>>l[i]>>r[i]; 
        ad[l[i]].pb(i); er[r[i]+1].pb(i); 
    }
    set<int> s;  
    vector<segtree<int,op,e>> seg;
    for(int i=0;i<=k;i++) seg.emplace_back(n+1); 
    for(int j=0;j<=k;j++) {
        seg[j].set(0,0);
        dp[0][j] = 0; 
    }
    int ans = 0; 
    rrep(i,n){
        for(auto x : ad[i]) s.insert(x); 
        for(auto x : er[i]) s.erase(x); 
        if(s.size()>k) continue; 
        vector<int> le; 
        for(auto x : s) le.pb(l[x]); 
        sort(all(le)); 
        vector<pair<int,int>> consider; 
        consider.pb({0,le.size()}); 
        for(int i=0;i<le.size();){
            int j = i; while(j<le.size()&&le[i]==le[j]) j++; 
            consider.pb({le[i],le.size()-j}); 
            i=j; 
        }
        dbg(i,consider)
        for(int j=0;j<consider.size();j++){
            auto [le,t] = consider[j]; 
            if(le>=i) break; 
            int r = (j==(int)consider.size()-1) ? i-1 : consider[j+1].first-1; 
            dbg(j,le,r+1,t)
            for(int tt=0;tt+t<=k;tt++){
                dp[i][tt+t] = max(dp[i][tt+t],1+seg[tt].prod(le,r+1)); 
            }
        }
        for(int j=0;j<=k;j++) {
            ans = max(ans,dp[i][j]); 
            seg[j].set(i,dp[i][j]); 
            dbg(i,j,dp[i][j])
        }
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