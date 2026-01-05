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
#include <atcoder/modint> 
using namespace atcoder; 
using mint = modint1000000007; 

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
void __print(mint x) {cerr << (x.val());}

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

const int N = 5001; 

mint po4[(N+2)*(N+2)]; 
mint dp[N][N][2][2]; 
mint inv3,inv4; 

void solve(){
    rrep(i,N-1) rrep(j,N-1) rep(p,2) rep(q,2) {
        mint tmp = (p==1 ? 1 : 3) *(q==1 ? 1 : 3) * inv4; 
        rep(l,4){
            //dbg(i,j)
            bool down = (q==1 || l==0); 
            bool right = (p==1 || l==1); 
            if(down&&right){
                mint dd = po4[(i+1)*(j+1)-2] * tmp; 
                dp[i][j][p][q] += dd; 
            } else if(down) {
                mint u = 0; 
                rep(_,2) u += dp[i][j-1][_][l==2]; 
                dp[i][j][p][q] += u * (l==2 ? mint(1) : inv3) * po4[i] * tmp; 
            } else {
                mint u = 0;
                rep(_,2) u += dp[i-1][j][l==3][_]; 
                dp[i][j][p][q] += u * tmp * po4[j] * (l==3 ? mint(1) :inv3); 
            }
        }
    }
}


signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    po4[0] = 1; 
    for(int i=1;i<(N+2)*(N+2);i++){
        po4[i] = po4[i-1]*4; 
    }
    inv3 = mint(3).inv(); 
    inv4 = mint(4).inv(); 
    dbg(1)
    solve(); 
    cin >> t; 
    while(t--){
        int n,m; cin>>n>>m; 
        mint ans = 0; 
        rep(i,2) rep(j,2)  ans += dp[n][m][i][j]; 
        cout << ans.val() << "\n"; 
    }
    return 0;
}