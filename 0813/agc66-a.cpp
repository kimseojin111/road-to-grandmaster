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

const int N = 510; 
int a[N][N]; 
int b[N][N]; 
int c[N][N]; 

void solve(){
    int n,d; cin>>n>>d; 
    rrep(i,n) rrep(j,n) cin>>a[i][j]; 

    auto lb = [](int x, int mod, int k){
        // x- (k(mod m)) 중 차이가 최소인 것. 
        int dd = (x/mod); 
        int re = -1, dif = 1e9; 
        for(int s=dd-2;s<=dd+2;s++){
            int shit = mod*s + k;
            if(abs(shit-x)<dif){
                dif = abs(shit-x); re = shit; 
            }
        }
        return re; 
    }; 
    ll p = 0, q = 0; 
    rrep(i,n) rrep(j,n){
        if((i+j)&1){
            b[i][j] = lb(a[i][j],d*2,d); 
            c[i][j] = lb(a[i][j],d*2,0); 
            p = p + abs(a[i][j]-b[i][j]); 
            q = q + abs(a[i][j]-c[i][j]); 
        }
        else{
            b[i][j] = lb(a[i][j],d*2,0); 
            c[i][j] = lb(a[i][j],d*2,d); 
            p = p + abs(a[i][j]-b[i][j]); 
            q = q + abs(a[i][j]-c[i][j]); 
        }
    }
    dbg(p,q,b[1][1],c[1][1])
    if(p>q) swap(b,c); 
    rrep(i,n) rrep(j,n) cout << b[i][j] << " \n"[j==n];
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}