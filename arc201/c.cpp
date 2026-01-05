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

const int N = 500010;
int l[N*5], r[N*5]; 
int pv; 
int cnt[N*5]; 
int sum[N*5]; 
int p[N*5]; 

#include <atcoder/modint>
using namespace atcoder; 
using mint = modint998244353; 

mint fac[N], rfac[N]; 

mint ncr(int n, int r){
    if(r<0||r>n) return (mint)0; 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

void dfss(int node){
    sum[node] = cnt[node]; 
    if(l[node]!=-1){
        dfss(l[node]); sum[node] += sum[l[node]]; 
    }
    if(r[node]!=-1){
        dfss(r[node]); sum[node] += sum[r[node]]; 
    }
}

vector<mint> dfs(int node){
    dbg(node,sum[node],cnt[node])
    mint ans = 0; 
    vector<mint> re(sum[node]+1,0); 
    if(cnt[node]>0){
        for(int i=1;i<=sum[node];i++) re[i] = ncr(sum[node],i) - ncr(sum[node]-cnt[node],i); 
    }
    if(l[node]==-1 || r[node]==-1) return re; 
    auto p = dfs(l[node]); 
    auto q = dfs(r[node]); 
    for(int i=1;i<p.size();i++) for(int j=1;j<q.size();j++) re[i+j] += p[i]*q[j]; 
    for(int i=1;i<=sum[node];i++) {
        dbg(node,i,re[i].val())
    }
    return re; 
}

mint dp[N*10]; 
void insert(string s){
    int now = 0; 
    for(char c : s){
        sum[now]++; 
        int x = (c=='B'); 
        if(x==0){
            if(l[now]<0){
                l[now] = ++pv; p[l[now]] = now; 
            }
            now = l[now]; 
        }
        else {
            if(r[now]<0) {
                r[now] = ++pv; p[r[now]] = now; 
            } 
            now = r[now]; 
        }
    }
    sum[now]++;
    mint two = 2;  
    mint shit = two.pow(sum[now]-1) - dp[now]; 
    dp[now] = 0; 
    bool flag = s=="AB"; 
    if(l[now]!=-1&&r[now]!=-1){
        dp[now] = dp[l[now]]*dp[r[now]];  
    }
    if(flag){
        dbg(now,p[now],p[p[now]])
    }
    dp[now] += two.pow(sum[now]-1); 
    while(p[now]!=-1){
        int px = p[now]; 
        if(now==l[px]){
            if(r[px]==-1) shit = 0; 
            else shit *= dp[r[px]]; 
        }
        else{
            if(l[px]==-1) shit = 0; 
            else shit *= dp[l[px]]; 
        }
        dp[px] = dp[px]*2 + shit; 
        if(flag){
            dbg(px,dp[px].val())
        }
        now = p[now]; 
    }
}

void solve(){
    fac[0] = 1; rfac[0] = 1; 
    p[0] = -1; 
    for(int i=1;i<N;i++){
        fac[i] = fac[i-1]*i; 
        rfac[i] = 1/fac[i]; 
    }
    int n; cin>>n; 
    vector<string> s; 
    rep(i,n){
        string t; cin>>t; s.pb(t); 
    }
    memset(l,-1,sizeof(l)); memset(r,-1,sizeof(r)); 
    for(auto t : s) {
        insert(t);
        cout << dp[0].val() << "\n";
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