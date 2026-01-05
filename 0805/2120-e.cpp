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
// #include <atcoder/modint> 
// using namespace atcoder; 
// using mint = modint998244353; 

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
//#define int ll 
const int N = 200010; 
ll a[N]; 
ll b[N]; 

using i128 = ll;

void solve(){
    int n,k; cin>>n>>k; 
    rep(i,n) cin>>a[i]; 
    sort(a,a+n); 
    // x 만큼 거시기 
    auto f = [&](ll x){
        i128 re = k*x; 
        rep(i,n) b[i] = a[i]; 
        ll xx = x; 
        i128 pl = 0; 
        for(int i=n-1;i>=0;){
            assert(a[i]==a[n-1]); 
            int j = i; while(j>=0&&a[n-1]==a[j]) j--; 
            int dif = b[i]-(j==-1 ? 0 : b[j]); 
            if(xx>=1LL*dif*(n-1-j)){
                ll shit = 1LL*dif*(2*a[i]-dif+1)/2; 
                pl -= shit*(n-1-j); xx -= 1LL*dif*(n-1-j); 
                a[n-1] -= dif; i=j; 
              //  dbg(j,a[n],dif)
                continue; 
            }
            else {
                ll dd = xx/(n-1-j); 
                ll shit = 1LL*dd*(2*a[i]-dd+1)/2;  
                pl -= shit*(n-1-j); xx -= 1LL*dd*(n-1-j); 
                a[n-1]-=dd; pl -= xx*a[n-1]; break; 
            }
        }
        re += pl; //dbg(x,pl)
        rep(i,n) a[i] = b[i]; 
        xx = x; 
        pl = 0; 
        for(int i=0;i<n;){
            assert(a[i]==a[0]); 
            int j = i; while(j<n&&a[j]==a[0]) j++; 
            int dif = (j==n ? (int)1e9 : b[j]) - b[i]; 
           // assert(j!=n);
            if(xx>=1LL*dif*(j)){
                ll shit = 1LL*dif*(2*a[i]+dif+1)/2; 
                pl += shit*(j); xx -= 1LL*dif*(j); 
                a[0] += dif; i=j; continue; 
            }
            else {
                ll dd = xx/(j); 
                ll shit = 1LL*dd*(2*a[i]+dd+1)/2; 
                pl += shit*(j); xx -= 1LL*dd*(j); 
                a[0] += dd; pl += xx*(a[0]+1); break; 
            }
        }
        re += pl; 
        rep(i,n) a[i] = b[i]; 
        return re; 
    }; 
    ll lo = 0, hi = 1LL*n*a[n-1] - accumulate(a,a+n,0LL); 
    while(hi-lo>=5){
       // cout << lo << " " << hi << endl;
        ll p = (lo*2+hi)/3, q = (lo+hi*2)/3; 
        dbg(p,q,f(p),f(q))
        if(f(p)<=f(q)) hi = q; 
        else lo = p; 
    }
    ll m = 1e18; 
    for(ll i=lo;i<=hi;i++) {m = min(m,(ll)f(i)); }

    rep(i,n) m += 1LL*a[i]*(a[i]+1)/2; 
    cout << m << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}