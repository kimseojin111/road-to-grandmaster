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

void solve(){
    int n; cin>>n;vector<int>a(n); rep(i,n) cin>>a[i]; 
    vector<int> ev; 
    vector<int> od; 
    rep(i,n) {
        if(a[i]%2==0) ev.pb(a[i]); 
        else od.pb(a[i]); 
    }

    // x , y    x<y   y(mod x)
    if(ev.size()>=2){
        cout << ev[0] << " " << ev[1] << "\n"; return; 
    }
    if(ev.size()==1){
        int e = ev[0]; 
        for(auto x : od) if(x>e && (x%e)%2==0) {
            cout << e << " " << x << "\n"; return; 
        }
        for(auto x : od) if(x<e && (e%x)%2==0) {
            cout << x << " " << e << "\n"; return; 
        }
    }
    if(ev.size()<=40){
        for(auto x : od) for(auto y : od) if(x<y) {
            int t = y%x; 
            if(t%2==0){
                cout << x << " " << y << "\n";return; 
            }
        }
        cout << -1 << "\n"; return; 
    } else {
        for(int i=0;i+1<od.size();i++) {
            int a = od[i], b = od[i+1]; 
            if(b<a*2) {
                cout << a << " " << b << "\n"; return; 
            }
        }
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}