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

const int N = 5010; 
int mex[N][N]; 
int a[N]; 
bool dp[N][N*2]; 

vector<int> chk[N]; 
void init(int n){
    rrep(i,n) rrep(j,n) mex[i][j]=0; 
    rrep(i,n) rrep(j,n*2) dp[i][j] = 0;
    rrep(i,n) chk[i].clear(); 
}

void solve(){
    int n; cin>>n;
    init(n); 
    rrep(i,n) cin>>a[i]; 
    int cnt = 0; 
    rrep(i,n){
        int freq[n+2]={0,}; 
        int pv = 0; 
        for(int j=i;j<=n;j++){
            freq[a[j]]++; 
            while(freq[pv]) pv++; 
            mex[i][j] = pv; 
            if(mex[i][j]!=mex[i][j-1]){
                chk[j].pb(i); 
            }
        }
    }
    dp[0][0] = 1; 
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n*2;j++) dp[i][j] = dp[i-1][j]; 
        for(auto j : chk[i]){
            int l = mex[j][i]; 
            for(int k=0;k<=n*2;k++) if((k^l <= n*2) && dp[j-1][k^l]) dp[i][k]=1; 
        }
    }
    for(int k=n*2;k>=0;k--) if(dp[n][k]){
        cout << k << "\n"; return; 
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