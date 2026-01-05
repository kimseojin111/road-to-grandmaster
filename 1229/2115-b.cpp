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

const int N = 300010; 
int b[N]; 
int a[N]; 
int c[N]; 

void chmax(int&x, int y){
    x = max(x,y); 
}

void solve(){
    int n,q; cin>>n>>q; 
    vector<array<int,3>> qry(q); 
    rrep(i,n) cin>>b[i]; 
    rrep(i,n) a[i] = b[i]; 
    rep(i,q) rep(j,3) cin>>qry[i][j]; 
    for(int i=q-1;i>=0;i--){
        auto [x,y,z] = qry[i]; 
        // min(ax,ay) = az 
        if(z==x&&z==y) continue; 
        if(x==y){
            chmax(a[x],a[z]); 
            a[z] = 0; continue; 
        }
        if(z==x){
            chmax(a[y],a[x]); continue; 
        }
        if(z==y){
            chmax(a[x],a[y]); continue; 
        }
        chmax(a[x],a[z]); chmax(a[y],a[z]); 
        a[z] = 0; 
    }
    rrep(i,n) c[i] = a[i]; 
    rep(i,q) {
        auto [x,y,z] = qry[i]; 
        c[z] = min(c[x],c[y]); 
    }
    rrep(i,n) if(b[i]!=c[i]) {
        cout << -1 << "\n"; return; 
    }
    rrep(i,n) cout << a[i] << " \n"[i==n]; 
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}