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

const int N = 110; 
int b[N][N]; 
int c[N][N]; 
int d[N][N]; 
int e[N][N]; 
int f[N][N]; 
int g[N][N]; 


void solve(){
    int n; cin>>n; 
    int x=-1,y=-1;
    rep(i,n){
        string s; cin>>s; 
        rep(j,n) {
            b[i][j] = s[j]=='#'; 
            if(x==-1&&b[i][j]){
                x=i,y=j; 
            } 
        }
    }
    if(x==-1){
        cout << "YES\n"; 
    } else {
        rep(i,n) rep(j,n) {
            c[i][j] = d[i][j] = e[i][j] = f[i][j] = g[i][j] = 0; 
        }
        auto chk = [&](int i, int j){
            return (i>=0)&&(i<n)&&(j>=0)&&(j<n); 
        };
        for(int u=x,v=y;u<n;u++,v++ ){
            if(chk(u,v)) c[u][v] = 1; 
            if(chk(u,v+1)) c[u][v+1] = 1;
        }
        for(int u=x,v=y;u<n;u++,v--){
            if(chk(u,v)) d[u][v] = 1; 
            if(chk(u,v-1)) d[u][v-1] = 1; 
        }
        for(int u=x,v=y-1;u<n;u++,v++){
            if(chk(u,v)) e[u][v] = 1; 
            if(chk(u,v+1)) e[u][v+1] = 1;
        }
        for(int u=x,v=y+1;u<n;u++,v--){
            if(chk(u,v)) f[u][v] = 1; 
            if(chk(u,v-1)) f[u][v-1] = 1; 
        }

        auto gg = [&](int a[N][N], int b[N][N]) {
            rep(i,n) rep(j,n) {
                if(a[i][j]==1&&b[i][j]==0) return false; 
            }
            return true; 
        }; 

        for(auto i : {x,x+1}) for(auto j : {y,y+1}) if(chk(i,j)) g[i][j]=1; 
        if(gg(b,c)||gg(b,d)||gg(b,e)||gg(b,f)||gg(b,g)) {
            cout << "YES\n"; 
        } else {
            cout << "NO\n";
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