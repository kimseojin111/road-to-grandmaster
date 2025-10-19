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
    int n; cin>>n; 
    string s; cin>>s; 
    // 1 0 1 
    vector<int> v; 
    vector<int> ans(n+1); 
    rep(i,n) if(s[i]=='1') v.pb(i+1); 
    if(v.empty()){
        cout << "YES\n"; 
        rrep(i,n) cout << (n+1-i) << " \n"[i==n]; 
        return; 
    }
    for(int i=0;i<v.size();i++){
        if(i==0&&v[i]==2){
            cout << "NO\n"; return; 
        }
        if(i==v.size()-1&&v[i]==n-1){
            cout << "NO\n"; return; 
        }
        if(i+1<v.size()&&v[i+1]-v[i]==2){
            cout << "NO\n"; return; 
        }
        ans[v[i]] = v[i]; 
        if(i==0){
            for(int j=1;j<v[i];j++) ans[j] = (v[i]-j); 
        }
        if(i>0){
            // v[i-1]+1 ~ v[i]-1
            for(int k=v[i-1]+1;k<v[i];k++){
                ans[k] = v[i]+v[i-1]-k; 
            }
        }
        if(i==v.size()-1){
            // v[i]+1 ~ n 
            for(int k=v[i]+1;k<=n;k++){
                ans[k] = n+v[i]+1-k; 
            }
        }
    }
    cout << "YES\n"; 
    rrep(i,n) cout << ans[i] << " \n"[i==n]; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}