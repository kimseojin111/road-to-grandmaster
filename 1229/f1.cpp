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
void __print(mint x) {cerr << (x.val());}

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

const int N = 600010; 
mint fac[N],rfac[N],pw[N]; 
mint ncr(int n, int r){
    if(r<0||r>n) return mint(0); 
    return fac[n] * rfac[r] * rfac[n-r]; 
}

int cnt[62];
int tmp[62];  
mint pww[62]; 

void solve(){
    int n,m; cin>>n>>m; 
    auto add = [&](int a, int x){
        cnt[a] += x; 
        for(int i=0;i<62;i++){
            pww[i] = (i==0 ? mint(1) : pww[i-1]) * pw[cnt[i]]; 
        }
    };
    rep(i,n){
        int x; cin>>x; add(x,1); 
    }
    rep(i,m){
        ll op,x; cin>>op>>x; 
        if(op==1) add(x,1); 
        else if(op==2) add(x,-1); 
        else {
            memset(tmp,0,sizeof(tmp)); 
            int shift = 60; 
            for(int p=60,t=0;p>=0;p--){
                if((x >> p) & 1LL){
                    int e = p + t;      
                    tmp[e]++;             
                    t++;
                }
            }
            mint ans = 0; 
            mint kk = 1; 
            for(int i=60;i>=0;i--){
                dbg(i,tmp[i])
                mint fuck = pw[cnt[i]]; 
                for(int k=0;k<=tmp[i];k++) fuck -= ncr(cnt[i],k); 
                ans += fuck * (i==0 ? mint(1) : pww[i-1]) * kk; 
                kk *= ncr(cnt[i],tmp[i]); 
            }
            ans += kk; 
            cout << ans.val() << "\n"; 
        }
    }
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    fac[0] = rfac[0] = 1;
    pw[0] = 1; 
    for(int i=1;i<N;i++){
        fac[i] = fac[i-1] * i; 
        rfac[i] = rfac[i-1] / i; 
        pw[i] = pw[i-1] * 2; 
    }
    while(t--) solve(); 
    return 0;
}