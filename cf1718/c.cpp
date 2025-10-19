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
ll a[N]; 
ll sum[30][N];
multiset<ll> m; 

void init(ll n){
    rep(i,30) rep(j,n) sum[i][j] = 0; 
    m.clear(); 
}

void solve(){
    ll n,q; cin>>n>>q; 
    init(n); 
    rrep(i,n) cin>>a[i]; 
    vector<int> p; 
    int nn = n; 
    for(int i=2;i<=n;i++){
        if(n%i==0){
            while(n%i==0) n/=i; 
            p.pb(i); 
        }
    }
    n = nn; 
    for(auto& i : p) i = n/i; 
    int P = p.size(); 
    vector<vector<multiset<long long>::iterator>> it(P);
    for (int j = 0; j < P; ++j) it[j].resize(p[j]);
    for(int j=0;j<p.size();j++){
        rrep(i,n){
            sum[j][i%p[j]] += a[i]; 
        }
        for(int i=0;i<p[j];i++) it[j][i] = m.insert(sum[j][i]*p[j]);
    }
    ll mx = -1; 
    mx=max(mx,*m.rbegin()); 
    cout << mx << "\n"; 
    dbg(p)
    while(q--){
        int i,x; cin>>i>>x; 
        for(int j=0;j<p.size();j++){
            int r = i%p[j]; 
            ll s = sum[j][r]; 
            m.erase(m.find(s*p[j]));
            s += (x-a[i]);  
            m.insert(s*p[j]); 
            sum[j][r] = s; 
        }
        a[i] = x; 
        ll mx = -1; 
        mx = *m.rbegin(); 
        cout << mx << "\n"; 
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}