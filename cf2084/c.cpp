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

void solve(){
    int n; cin>>n; 
    vector<int> a(n+1),b(n+1),go(n+1),ib(n+1); 
    rrep(i,n) cin>>a[i]; 
    rrep(i,n) {
        cin>>b[i]; ib[b[i]] = i; 
    }
    int cnt = 0; 
    rrep(i,n){
        if(b[i]!=a[ib[a[i]]]) {
            cout << -1 << "\n"; return; 
        }
        if(a[i]==b[i]) cnt++; 
    }
    if(cnt!=n%2){
        cout << -1 << "\n"; return; 
    }
    int pv = 1; 
    rrep(i,n){
        int j = ib[a[i]]; 
        if(i==j) go[i] = (n+1)/2; 
        if(i<j){
            go[i] = pv; go[j] = n+1-pv; pv++; 
        }
    }
    vector<pair<int,int>> ans; 
    vector<int> p(n+1),rp(n+1); 
    rrep(i,n) p[i]=rp[i]=i; 
    auto swp = [&](int i, int j){
        ans.pb({i,j}); 
        rp[p[i]] = j; rp[p[j]] = i; 
        swap(p[i],p[j]); 
    }; 
    rrep(i,n){
        if(rp[i]!=go[i]) swp(rp[i],go[i]); 
    }
    cout << ans.size() << "\n"; 
    for(auto [a,b]:ans) cout<<a<<" "<<b<<"\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}