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
#include <atcoder/modint> 
using namespace atcoder; 
using mint = modint998244353; 

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

vector<pair<int,int>> comp(int x){
    if(x==1) return {}; 
    vector<pair<int,int>> re; 
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            int u = 0; 
            while(x%i==0){
                u++; x/=i; 
            }
            re.pb({i,u}); 
        }
    }
    if(x>1) re.pb({x,1}); 
    return re; 
}

vector<pair<int,int>> merge(vector<pair<int,int>> a, vector<pair<int,int>> b){
    vector<pair<int,int>> res;
    size_t i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || (i < a.size() && a[i].first < b[j].first)) {
            res.pb(a[i++]);
        } else if (i == a.size() || b[j].first < a[i].first) {
            res.pb(b[j++]);
        } else { // same prime
            int p = a[i].first;
            int e = a[i].second + b[j].second;
            res.pb({p, e});
            ++i; ++j;
        }
    }
    return res;
}

void solve(){
    ll x,y,z; cin>>x>>y>>z; 
    auto v1 = comp(x); 
    auto v2 = comp(y); 
    auto v3 = comp(z); 
    ll m = x*y*z; 
    auto w = merge(v1,v2); 
    auto v = merge(w,v3); 

    vector<pair<int,int>> s; 
    set<int> in; 
    for(auto [p,d]:v) in.insert(p); 

    unordered_map<int,ll> e;

    for(auto [p,d]:v){
        if(p==2) continue;
        auto g = comp(p-1); 
        for(auto [u,dd]:g){
            if(in.find(u)==in.end()){
                e[u]+=dd; 
            }
        } 
    }

    mint ans = mint(1)/m; 
    for(auto [q,dd]:e)
        {
            mint invq = mint(1)/q;
            mint q_pow = mint(q).pow(dd); 
            mint term = 1 + (mint(q).pow(dd)-1)*invq; 
            ans *= term;

        }
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}