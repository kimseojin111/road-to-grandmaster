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

ll f[110]; 
ll s[3110]; 
ll inf = 1e11; 
ll c[110]; 
ll cc[110]; 

void solve(){
    ll sum = 0; 
    int k; cin>>k; 
    dbg(k)
    rep(i,k) cin>>c[i]; 
    sum = 0; rep(i,k) {
        sum+=c[i]; dbg(i,c[i])
    }
    dbg(sum)
    if(sum==1){
        cout << "YES\n"; return; 
    }
    if(sum==2){
        if(k==1) cout << "NO\n"; 
        else cout << "YES\n"; 
        return; 
    }
    bool ff = false; 
    int la = -1; 
    for(int i=0;i<60;i++){
        dbg(i,s[i])
        if(s[i]==sum){
            ff=true; la = i; break;  
        }
    }
    if(!ff){
        cout << "NO\n"; return; 
    }
    auto chk = [&](int ppp){
        int pv = ppp; 
        for(int i=la-1;i>=0;i--){
            ll mx = -1, idx = -1; 
            for(int i=0;i<k;i++) if(c[i]>mx&&i!=pv){
                idx = i; mx= c[i]; 
            }
            if(idx==-1) {
                return 0; 
            }
            if(mx<f[i]){
                return 0; 
            }
            c[idx]-=f[i]; 
            pv = idx; 
        }
        return 1; 
    }; 
    rep(i,k) cc[i] = c[i]; 
    vector<int> tt; 
    rep(i,k) if(cc[i]>=f[la]) tt.pb(i); 
    int god = 0; 
    for(auto x : tt){
        dbg(x)
        rep(i,k) c[i]=cc[i]; 
        c[x] -= f[la]; 
        if(chk(x)) god=1;
    }
    cout << (god? "YES":"NO")<<"\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   f[0] = 1; f[1] = 1; 
    s[0] = 1, s[1] = 2; 
    for(int i=2;i<60;i++){
        f[i]=f[i-1]+f[i-2];
       // dbg(i,f[i]) 
        s[i]=s[i-1]+f[i]; 
        if(s[i]>inf) break;  
    }
   while(t--) solve(); 
   return 0;
}