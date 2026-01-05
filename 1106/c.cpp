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

void solve(){
    int n,m; cin>>n>>m; 
    vector<int> a(n); rep(i,n) cin>>a[i]; 
    vector<pair<int,int>> v(m); 
    rep(i,m) cin>>v[i].ff; 
    rep(i,m) cin>>v[i].ss; 
    // j 
    vector<int> b; 
    vector<pair<int,int>> sup; 
    rep(i,m) if(v[i].ss==0) b.pb(v[i].ff); 
    else sup.pb(v[i]); 
    sort(all(a)); 
    sort(all(b)); 
    sort(all(sup)); 
    // base 
    int ans = 0; 
    int x = a.back(); 
    int cnt = 0; 
    for(auto [bi,ci] : sup) if(x>=bi) {
        cnt++; x = max(x,ci); 
    }
    ans = cnt; 
    int l=1,r=min(a.size(),b.size()); 
    int shit = 0; 
    while(l<=r){
        int m = l+r>>1; 
        multiset<int> s; 
        for(int i=a.size()-m;i<a.size();i++) s.insert(a[i]); 
        int ddd = 0; 
        for(auto [bi,ci] : sup) {
            auto it = s.lower_bound(bi); 
            if(it==s.end()) break; 
            ddd++;
            int ne =  max(ci,*it); 
            s.erase(it); 
            s.insert(ne); 
        }
        assert(ddd==cnt); 
        int idx = 0; 
        bool f = true; 
        for(auto x : s) {
            if(x>=b[idx++]) continue; 
            else {
                f = false; break; 
            }
        }
        if(f) {
            shit = m; l=m+1;
        } else r=m-1; 
    }
    ans = max(ans,cnt+shit); 
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