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

void chmax(int &x, int y){
    x = max(x,y); 
}

void solve(){
    int n; cin>>n; 
    dbg(n)
    vector<int> a; 
    vector<vector<int>> pos(2*n+4,vector<int>()); 
    rep(i,n){
        int x; cin>>x; a.pb(x); 
        pos[x].pb(i); 
    }
    vector<int> dpM(2*n+1); 
    vector<vector<int>> dp(2*n+1,vector<int>()); 
    vector<vector<int>> pfx(2*n+1,vector<int>()); 
    vector<vector<int>> sfx(2*n+1,vector<int>()); 
    rrep(i,n*2){
        dp[i].resize(pos[i].size()); 
        pfx[i].resize(pos[i].size());
        sfx[i].resize(pos[i].size());  
    }
    auto lb = [&](vector<int>& v, int k){
        // v 에서 k 이하의 개수 
        return int(upper_bound(all(v),k)-v.begin()); 
    }; 
    rrep(i,n*2){
        if(i==1||i==2){
            for(int j=0;j<pos[i].size();j++){
                int cur = pos[i][j]; 
                dp[i][j] = j+1 - lb(pos[i-1],cur) - lb(pos[i+1],cur); 
            }
        }
        else {
            for(int j=0;j<pos[i].size();j++){
                int cur = pos[i][j]; 
                dp[i][j] = j+1 - lb(pos[i-1],cur) - lb(pos[i+1],cur) + dpM[i-2]; 
            }
            // pfx, sfx 
            for(int j=0;j<pos[i-2].size();j++){
                pfx[i-2][j] = dp[i-2][j] + lb(pos[i-1],pos[i-2][j]); 
                if(j>0) chmax(pfx[i-2][j],pfx[i-2][j-1]); 
            }
            for(int j=int(pos[i-2].size())-1;j>=0;j--){
                sfx[i-2][j] = dp[i-2][j];
                if(j!=pos[i-2].size()-1) chmax(sfx[i-2][j],sfx[i-2][j+1]); 
            }
            for(int j=0,k=-1;j<pos[i].size();j++){
                while(k<int(pos[i-2].size())-1&&pos[i-2][k+1]<pos[i][j]) k++; 
                int cur = pos[i][j]; 
                int po = j+1 - lb(pos[i-1],cur) - lb(pos[i+1],cur);  
                if(k>=0) chmax(dp[i][j],po+pfx[i-2][k]); 
                if(k+1<int(pos[i-2].size())) chmax(dp[i][j],po+sfx[i-2][k+1]+lb(pos[i-1],pos[i][j])); 
            }
        }
        if(i>2) chmax(dpM[i],dpM[i-2]); 
        for(int j=0;j<pos[i].size();j++) chmax(dpM[i],dp[i][j]); 
    }
    int ans = dpM[2*n]+dpM[2*n-1]; 
    cout << ans << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}