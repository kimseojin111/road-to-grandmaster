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

#include <atcoder/lazysegtree>
using namespace atcoder; 

const ll inf = 2e18; 
ll op(ll a, ll b){return min(a,b);} 
ll e() {return inf;} 
ll mapping(ll f, ll x) {return x-f;}
ll composition(ll f, ll g) {return f+g;}
ll id() {return 0LL;}


const int N = 400010;
ll dp[N], sum[N]; 
ll dp1[N]; 

void solve(){
    ll n,k,A; cin>>n>>k>>A; 
    lazy_segtree<ll,op,e,ll,mapping,composition,id> seg(2*k+2); 
    vector<array<ll,3>> v(n); 
    rep(i,n) rep(j,3) cin>>v[i][j]; //x y c
    sort(all(v),[](auto a, auto b){
        return a[1] - a[0] < b[1] - b[0]; 
    }); 
    rep(i,n) {
        auto [x,y,p] = v[i]; sum[y-x+k] += p; 
    }
    for(int i=1;i<N;i++) sum[i] += sum[i-1]; 
    sort(all(v),[](auto a, auto b){
        return a[0]>b[0]; 
    }); 
    dp[0] = 0; 
    seg.set(0,0LL);
    int pv = 0; 
    dbg(v)
    for(int i=2;i<=k*2;i+=2){
        //dbg(i,sum[i])
        while(pv<v.size()&&v[pv][0]==k-i/2){
            auto [x,y,p] = v[pv]; pv++; 
            seg.apply(0,2*y+1,p); 
        }
        dp[i] = seg.prod(0,i-1) + sum[i] + A*i/2; 
        dbg(i,sum[i])
        //dbg(seg.all_prod(),sum[i],A*i/2)
        for(int j=0;j<i;j+=2){
            dbg(j,seg.get(j))
        }
        dp1[i] = min(dp1[i-2]+sum[i]-sum[i-2],dp[i]); 
        seg.set(i,-A*i/2+dp1[i-2]+sum[i-1]-sum[i-2]-sum[i-1]);
        dbg(i,dp[i],dp1[i],sum[i]-sum[i-2])
    }
    cout << dp1[k*2];
}   

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}