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

mint dp[12][2][12][2][12][2]; 
mint ndp[12][2][12][2][12][2]; 

void solve(){
    ll n,a,b,c; cin>>n>>a>>b>>c; 
    dp[0][0][0][0][0][0] = 1; 

    auto chk = [&](int& nb, int ob, int cur, bool& flag){
        // nb : 현재 미만인지 같인지  ob : 새로 추가하려는 값, cur : 현재 비트, flag : 가능 불가능 
        if(nb==1) return; 
        // 현재 같은 값이고 
        if(ob>cur) {
            flag = false; return; 
        } else if(ob==cur){
            return; 
        } else {
            nb = 1; return; 
        }
    }; 

    for(int f = 61;f>=0;f--){
        ll nf = (n>>f)&1; 
        rep(am,a) rep(af,2) rep(bm,b) rep(bf,2) rep(cm,c) rep(cf, 2){
            ndp[am][af][bm][bf][cm][cf] = 0; 
        }
        rep(am,a) rep(af,2) rep(bm,b) rep(bf,2) rep(cm,c) rep(cf, 2){
            {
                // 0 0 0 
                int aff=af,bff=bf,cff=cf; 
                if(nf==1) aff=1,bff=1,cff=1; 
                ndp[am][aff][bm][bff][cm][cff] += dp[am][af][bm][bf][cm][cf]; 
            }
            {
                // 1 1 0 
                int aff=af,bff=bf,cff=cf; 
                bool add = true; 
                chk(aff,1,nf,add); 
                chk(bff,1,nf,add); 
                chk(cff,0,nf,add); 
                ll amm = (1LL<<f)%a + am, bmm = (1LL<<f)%b + bm, cmm = cm; 
                if(amm>=a) amm-=a; 
                if(bmm>=b) bmm-=b; 
                if(cmm>=c) cmm-=c; 
                if(add) ndp[amm][aff][bmm][bff][cmm][cff] += dp[am][af][bm][bf][cm][cf]; 
            }
            {
                // 0 1 1 
                int aff=af,bff=bf,cff=cf; 
                bool add = true; 
                chk(aff,0,nf,add); 
                chk(bff,1,nf,add); 
                chk(cff,1,nf,add); 
                ll amm = am, bmm = (1LL<<f)%b + bm, cmm = (1LL<<f)%c + cm; 
                if(amm>=a) amm-=a; 
                if(bmm>=b) bmm-=b; 
                if(cmm>=c) cmm-=c; 
                if(add) ndp[amm][aff][bmm][bff][cmm][cff] += dp[am][af][bm][bf][cm][cf]; 
            }
            {
                // 1 0 1 
                int aff=af,bff=bf,cff=cf; 
                bool add = true; 
                chk(aff,1,nf,add); 
                chk(bff,0,nf,add); 
                chk(cff,1,nf,add); 
                ll amm = (1LL<<f)%a + am, bmm = bm, cmm = (1LL<<f)%c + cm; 
                if(amm>=a) amm-=a; 
                if(bmm>=b) bmm-=b; 
                if(cmm>=c) cmm-=c; 
                if(add) ndp[amm][aff][bmm][bff][cmm][cff] += dp[am][af][bm][bf][cm][cf]; 
            }
        }
        rep(am,a) rep(af,2) rep(bm,b) rep(bf,2) rep(cm,c) rep(cf, 2){
            dp[am][af][bm][bf][cm][cf] = ndp[am][af][bm][bf][cm][cf];
        }
    }
    mint ans = 0; 
    rep(i,2) rep(j,2) rep(k,2) ans += dp[0][i][0][j][0][k]; 
    // a = 0 
    dbg(ans)
    auto lcm = [](ll a, ll b){
        return a*b/(gcd(a,b)); 
    }; 
    ll na = n/a + 1, nb = n/b + 1, nc = n/c + 1; 
    ans = ans - ((n/lcm(a,b))+1) - (n/lcm(b,c)+1) - (n/lcm(c,a)+1); 
    ans += 3; 
    ans -= 1; 
    cout << ans.val();
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}