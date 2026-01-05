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


#define int ll 
// crt? 
bool is_prime(ll x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0) return false; 
    } return true; 
}

using i128 = __int128_t;

long long inv(long long a, long long b){
    return 1 < a ? b - inv(b%a, a) * b/a : 1;
}

static inline ll norm_mod(ll x, ll m){
    x %= m;
    if(x < 0) x += m;
    return x;
}

// pairwise coprime CRT: x ≡ re[i] (mod a[i])
// returns {M, x} with 0 <= x < M
pair<ll,ll> crt(const vector<ll>& a, vector<ll> re){
    int n = (int)a.size();
    for(int i=0;i<n;i++) re[i] = norm_mod(re[i], a[i]);

    ll s = re[0];
    ll mod = a[0];

    for(int i=1;i<n;i++){
        ll m = a[i];
        ll r = re[i];

        // k = (r - s) / mod  (mod m)
        ll diff = norm_mod(r - s, m);
        ll inv_mod = inv(norm_mod(mod, m), m);          // inverse of mod (mod m)
        ll k = (ll)((i128)diff * inv_mod % m);

        s = (ll)((i128)s + (i128)mod * k);              // use i128 to avoid overflow in multiply
        mod = (ll)((i128)mod * m);

        s = norm_mod(s, mod);
    }
    return {mod, s};
}


void solve(){
    ll hidden = 10; 
    auto f = [&](ll x, ll b){
        if(x<b) return -1LL; 
        ll re = 0; 
        while(x) {
            re += x%b; 
            x /= b; 
        }
        return re; 
    }; 
    auto qry = [&](int b){
        cout << "? " << b << endl; 
        int x; 
        cin>>x;
        // x= f(hidden,b);  
        return x; 
    }; 

    auto fuck = [&](int l, int r, vector<int> p, vector<int> gett = {}){
        vector<int> t; 
        for(auto x : gett) t.pb(x); 
        //for(auto x : p) t.pb(qry(x)); 
        for(int i=gett.size();i<p.size();i++) t.pb(qry(p[i])); 

        if(l>=70){
            for(auto &x : p) x--; 
            auto ddd = crt(p,t); 
            cout << "! " << ddd.second << endl; 
            //dbg(l,r,p,t,hidden,ddd.second)
            return; 
        }
        map<vector<int>,int> m;
        for(int i=l;i<=r;i++){
            vector<int>t; 
            for(auto x : p) t.pb(f(i,x)); 
            m[t] = i; 
        } 
        int ans = m[t]; 
        cout << "! " << ans << endl; return; 
    }; 

    auto under_9 = [&](){
        return fuck(1,8,{2,3}); 
    }; 

    int m = 45000; 
    vector<ll> p; 
    while(p.size()<4){
        if(is_prime(m)) p.pb(m); 
        m--; 
    }
    vector<ll> re; 
    re.pb(qry(p[0]+1)); 
    if(re[0]==-1){
        ll a9 = qry(9); 
        if(a9==-1) return under_9(); 
        int a78 = qry(78); 
        if(a78==-1) return fuck(9,77,{9,10},{a9}); 
        return fuck(78,45000,{9,78,76},{a9,a78}); 
    }
    for(int i=1;i<4;i++) re.pb(qry(p[i]+1)); 
    auto fff = crt(p,re); 
    cout << "! " << fff.second << endl; 
    return; 
}

signed main() {
    //cin.tie(0)->ios::sync_with_stdio(0);
    //cout.tie(nullptr);
    ll t,k,c; 
    cin>>t>>k>>c; 
    rrep(i,t){
        solve(); 
        int r; cin>>r; 
        assert(r==1); 
    }
    dbg(1)
    return 0;
}