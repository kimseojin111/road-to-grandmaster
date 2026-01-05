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

const ll mod = (1LL<<57)+1557; 
const int N = 100010; 



void solve(){
    auto hsh =[&](auto v){
        return v; 
    }; 
    int n,k; cin>>n>>k; 
    if(n==1){
        if(k==1){
            cout << "YES\n"; cout << "1\n"; return; 
        }
        else {
            cout << "NO\n"; return; 
        }
    }
    set<vector<int>> has; 
    if(n%2==0 && (k%2)){
        cout << "NO\n"; return; 
    }
    vector<vector<int>> ans; 
    ll fac = 1; 
    for(ll i=1;i<=n;i++){
        if(fac>1e9) break; 
        fac = fac*i; 
    }
    if(k==fac-1||k==1||k>fac){
        cout << "NO\n"; return; 
    }
    vector<int> v(n); 
    iota(all(v),1); 
    int j = n/2; 
    vector<int> w(n); 
    rep(i,n) {
        w[i] = (v[i]+j); while(w[i]>n) w[i]-=n; 
    }
    vector<int> vv(n); 
    int s = 3*(n/2)+3; 
    bool f = true; 
    rep(i,n){
        vv[i] = s-w[i]-v[i]; if(vv[i]<=0) f = false; 
    }
    if(k&1){
        ans.pb(v); ans.pb(w); ans.pb(vv); k-=3; 
        has.insert(hsh(v)); has.insert(hsh(w)); has.insert(hsh(vv)); 
    }
    do {
        if(k==0) break; 
        auto w = v;
        for(auto&x : w) x = n+1-x; 
        auto hv = hsh(v), hw = hsh(w); 
        if(has.count(hv)||has.count(hw)) continue; 
        k -= 2; 
        ans.pb(v); ans.pb(w); has.insert(hv); has.insert(hw); 
    }while(next_permutation(all(v))); 
    cout<<"YES\n";
    for(auto x : ans) {
        for(auto b : x) cout << b << " "; 
        cout << "\n"; 
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