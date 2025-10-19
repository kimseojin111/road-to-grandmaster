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

#include <atcoder/modint> 
using namespace atcoder; 

using mint = modint998244353; 

const int N = 510; 
mint cnt[N],cnt1[N]; 
mint dcnt[N],dcnt1[N]; 

mint dp[N][2]; 
mint ndp[N][2]; 
int a[N],b[N]; 

void solve(){
    int n,k; cin>>n>>k; 
    for(int i=0;i<=k;i++) for(int j=0;j<2;j++) dp[i][j] = 0; 
    for(int i=0;i<=k;i++) dcnt[i]=dcnt1[i] = 0; 
    rrep(i,k) rrep(j,k) {
        if(i>=j) dcnt[i-j]++; 
        else dcnt1[j-i]++; 
    }
    rrep(i,n) cin>>a[i]; 
    rrep(i,n) cin>>b[i]; 
    dp[0][1] = 1; 
    for(int i=2;i<=n;i++){
        int p = a[i],q=b[i-1];
        dbg(i,p,q) 
        for(int i=0;i<=k;i++) cnt[i]=cnt1[i]=0; 
        if(p==-1&&q==-1){
            for(int i=0;i<=k;i++) cnt[i]=dcnt[i],cnt1[i]=dcnt1[i]; 
        }
        else if(p==-1){
            rrep(j,k){
                int dif = j-q; if(dif>=0) cnt[dif]++; 
                else cnt1[-dif]++; 
            }
        }
        else if(q==-1){
            rrep(j,k){
                int dif = p-j; if(dif>=0) cnt[dif]++; 
                else cnt1[-dif]++; 
            }
        }
        else {
            int dif = p-q; if(dif>=0) cnt[dif]++; 
            else cnt1[-dif]++; 
        }
        for(int dif=-k;dif<=k;dif++) for(int t=0;t<=k;t++) for(int flag=0;flag<2;flag++){
            if(flag){
                if(t) continue; 
                if(dif<0){
                    dbg(-dif,cnt1[-dif].val(),dp[0][1].val())
                }
                if(dif>=0) ndp[0][1] += cnt[dif]*dp[0][1]; 
                else ndp[-dif][0] += cnt1[-dif]*dp[0][1]; 
            }
            else {
                if(dif>=0){
                    if(t>=dif){
                        ndp[t-dif][0] += cnt[dif]*dp[t][0]; 
                    }
                }
                else {
                    ndp[-dif][0] += cnt1[-dif]*dp[t][0]; 
                }
            }
        }
        for(int i=0;i<=k;i++) rep(j,2) {
            dbg(i,j,ndp[i][j].val())
            dp[i][j] = ndp[i][j]; ndp[i][j]=0; 
        }
    }
    mint ans = 0; 
    for(int i=0;i<=k;i++) rep(j,2) {
        ans += dp[i][j]; 
    }
    if(a[1]==-1) ans *= k; 
    if(b[n]==-1) ans *= k; 
    cout << ans.val() << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}