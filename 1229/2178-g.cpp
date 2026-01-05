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

struct fen_xor{
    vector<ll> a; int n; 
    fen_xor(int n) : n(n) {
        a.resize(n+1); 
    }
    void upd(int p, ll v){
        while(p<n){
            a[p]^=v; p+=p&-p; 
        }
    }
    ll qry(int p){
        ll re = 0; 
        while(p){
            //dbg(p,a[p])
            re ^= a[p]; p-=p&-p; 
        }
        return re; 
    }
    ll qry(int l, int r){
        return qry(r) ^ qry(l-1); 
    }
}; 

void solve(){
    int n; cin>>n; 
    fen_xor f(n*2+3); 
    fen_xor fx(n*2+3); 
    ll sum = 0; 
    rep(i,n){
        int a,b; cin>>a>>b; 
        int shit = f.qry(a+1,b-1)^1LL;
        f.upd(a,shit); f.upd(b,shit);
        dbg(shit)
        ll fuck = 0; 
        fuck = fx.qry(a+1,b-1);  
        if(shit){
            ll rd = randint(1LL,(1LL<<62)-1); 
            fuck ^= rd; 
        }
        sum ^= fuck; 
        dbg(i,sum)
        fx.upd(a,fuck); fx.upd(b,fuck); 
        if(sum==0){
            cout << '1'; 
        } else cout << '0'; 
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}