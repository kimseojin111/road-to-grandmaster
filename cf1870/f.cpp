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

using i128 = __int128; 

vector<ll> par(ll n, ll k){
    vector<ll> re; 
    while(n){
        re.pb(n%k); n/=k; 
    }
    reverse(all(re)); 
    return re; 
}

ll po[100]; 
ll poo[100]; 
ll remain[100]; 

void solve(){
    ll n,k; cin>>n>>k; 
    ll ans = 0; 
    //dbg(par(35,2))
    vector<ll> n_par = par(n,k); 
    int L = n_par.size(); 
    i128 l=1,r=k-1;
    po[0] = 1; poo[0] = 1; 
    remain[0] = n%k; 
    for(int i=1;i<L;i++) {
        po[i] = po[i-1]*k; 
        poo[i] = po[i] + poo[i-1]; 
    }
    i128 nn = n; 
    dbg(L)
    for(int i=1;i<L-1;i++){
        remain[i] = n%po[i+1]; 
    }
    dbg(L)
    auto f = [&](ll x){
        // x보다 작은 것의 개수 - x 
        // x 이하의 개수 i
        auto v = par(x,k); 
        ll re = 0; 
        ll xx = x; 
        for(int i=0;i<v.size();i++){
            re += xx - po[v.size()-1-i]+1; 
            xx /= k;
        }
        xx=x; 
        ll nk = n/k; 
        for(int i=v.size();i<L;i++){
            if(xx>nk){
                xx = n+1; 
            }
            else {
                xx *=k; xx = min(xx,n+1); 
            }
            re += xx - po[i]; 
        }
        return re-x; 
    };
    while(1){
        r = min((i128)n,r); 
        ll le = l, ri = r; 
        assert(le<=n&&ri<=n); 
        if(f(le)<=0 && f(ri)>=0){
            ll min_x = -1; 
            while(le<=ri){
                ll m = (le+ri)>>1; 
                if(f(m)>=0)  {
                    min_x = m; ri=m-1; 
                }
                else {
                    le = m+1; 
                }
            }
            if(f(min_x)==0){
                le = min_x, ri = r; 
                ll max_x = -1; 
                while(le<=ri){
                    ll m = (le+ri)>>1; 
                    if(f(m)<=0){
                        max_x = m; le = m+1; 
                    }
                    else {
                        ri = m-1; 
                    }
                }
                ans += (max_x-min_x+1); 
            }
        }
        if(r==n) break; 
        l*=k; r=l*k-1; 
    }
    cout << ans << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}