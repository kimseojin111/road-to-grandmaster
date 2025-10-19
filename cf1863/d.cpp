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

const int N = 510; 
char a[N][N]; 
char ans[N][N]; 

void solve(){
    int n,m; cin>>n>>m; 
    rep(i,n) rep(j,m) cin>>a[i][j]; 
    rep(i,n) rep(j,m) ans[i][j] = '.'; 
    for(int j=0;j<m;j++) {
        vector<int> v; 
        for(int i=0;i<n;i++) if(a[i][j]=='L') v.pb(i); 
        if(v.size()&1){
            cout << -1 << "\n"; return; 
        }
        for(int k=0;k<v.size();k+=2){
            int p = v[k],q=v[k+1]; 
            ans[p][j] = 'W'; ans[q][j] = 'B'; 
            ans[p][j+1] = 'B'; ans[q][j+1] = 'W'; 
        }
    }
    for(int i=0;i<n;i++){
        vector<int> v; 
        for(int j=0;j<m;j++) if(a[i][j]=='U') v.pb(j); 
        if(v.size()&1) {
            cout << -1 << "\n"; return; 
        }
        for(int k=0;k<v.size();k+=2){
            int p = v[k],q=v[k+1]; 
            ans[i][p] = 'W'; ans[i][q] = 'B'; 
            ans[i+1][p] = 'B'; ans[i+1][q] = 'W'; 
        }
    }
    rep(i,n) rep(j,m){
        cout << ans[i][j]; 
        if(j==m-1) cout << "\n";
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