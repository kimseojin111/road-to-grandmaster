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

#include <atcoder/modint>
using namespace atcoder; 
using mint = modint1000000007; 
const int N = 2500100; 
mint fac[N],rfac[N]; 
mint ncr(int n, int r){
    if(r<0||r>n) return (mint)0; 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

mint a[N],b[N]; 

mint con(mint a[], int i, int j){
    int d = j-i; 
    mint re = 0; 
    for(int k=j;k>=i;k--){
        int ff = (k%2==j%2) ? 1 : -1; 
        dbg(d,j-k)
        mint cool = ncr(d,j-k)*a[k]*ff; 
        dbg(cool.val(),a[k].val(),k)
        re += cool; 
    }
    return re; 
}

void solve(){
    fac[0] = 1, rfac[0] = 1; 
    for(int i=1;i<N;i++){
        fac[i] = i*fac[i-1]; 
        rfac[i] = rfac[i-1]/i; 
    }
    int d; cin>>d; 
    for(int i=0;i<=d;i++) {
        int ai; cin>>ai; a[i] = ai; 
        //cin>>a[i]; 
    }
    for(int i=0;i<=d;i++) {
        int bi; cin>>bi; b[i]=bi; 
        //cin>>b[i]; 
    }
    mint aa = con(a,0,d-1), aaa = con(a,1,d); 
    mint bb = con(b,0,d-1), bbb = con(b,1,d); 
    dbg(aa.val(),aaa.val())
    mint p = aaa-aa; 
    mint s = (bb-aa)/p; 
    cout << s.val(); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}