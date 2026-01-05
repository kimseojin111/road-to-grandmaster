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
    int n,m; cin>>n>>m; 
    vector<pair<int,int>> a(n); 
    rep(i,n){
        cin>>a[i].ff; 
        a[i].ss = i+1; 
    }
    if(2*m>n){
        cout << -1 << "\n"; return; 
    } 
    if(m==0){
        ll sum = 0; 
        sort(all(a)); 
        rep(i,n-1) sum += a[i].ff; 
        if(sum<a[n-1].ff) {
            cout << -1 << "\n"; return; 
        }
        vector<pair<int,int>> ans; 
        sum = 0; 
        int idx = n-2; 
        while(sum<a[n-1].ff){
            sum += a[idx].ff; 
            idx--; 
        }
        idx++; 
        // idx ~ n-2 -> n-1  
        //  1 
        for(int i=0;i<=idx-1;i++){
            ans.pb({a[i].ss,a[i+1].ss}); 
        }
        for(int i=idx;i<=n-2;i++){
            ans.pb({a[i].ss,a[n-1].ss}); 
        }
        cout << ans.size() << "\n"; 
        for(auto [p,q] : ans) cout << p << " " << q << "\n"; 
        return; 
    }
    sort(all(a)); 
    vector<pair<int,int>> ans; 
    deque<pair<int,int>> p; 
    vector<pair<int,int>> q; 
    for(int i=0;i<n-m;i++) p.pb(a[i]); 
    for(int i=n-m;i<n;i++) q.pb(a[i]); 
    dbg(p,q)
    while(p.size()>q.size()){
        auto d = p.front(); p.pop_front(); 
        ans.pb({d.second,p.front().second}); 
    }
    for(int i=0;i<q.size();i++){
        ans.pb({q[i].second,p[i].second}); 
    }
    cout << ans.size() << "\n"; 
    for(auto [p,q] : ans) cout << p << " " << q << "\n"; 
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}