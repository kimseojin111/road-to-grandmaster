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

int op(int a, int b) {return min(a,b);}
int e() {return 1e9;}
int mapping(int f, int x){
    return x+f; 
}
int composition(int f, int g){return f+g;}
int id() {return 0;}

void solve(){
    int n,m; cin>>n>>m; int shit = 0; 
    vector<pair<int,int>> v; 
    int nn = n; 
    rep(i,n){
        int l,r; cin>>l>>r; 
        if(l==0&&r==m+1){
            shit++; nn--; 
        }
        else v.pb({l,r}); 
    }
    int ans = 0;
    ans = min(ans,m-nn); 
    vector<int> p(m+2); rep(i,m+2) p[i] = -i; 
    lazy_segtree<int,op,e,int,mapping,composition,id> seg(p); 
    sort(all(v)); int pv = 0; 
    dbg(v)
    for(int i=0;i<=m;i++){
        while(pv<v.size()&&v[pv].first==i){
            int d = v[pv++].second; 
            seg.apply(0,d+1,-1); 
        }
        int shit = seg.all_prod(); 
        dbg(i,shit,i+m+1+shit)
        ans = min(i+m+1+shit,ans);
    }
    cout << (-ans+shit);
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}