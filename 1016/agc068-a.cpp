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
using mint = modint998244353; 

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

const int N = 1000100; 
mint fac[N],rfac[N]; 

void init(){
    fac[0]=rfac[0]=1; 
    for(int i=1;i<N;i++){
        fac[i]=i*fac[i-1]; 
        rfac[i]=rfac[i-1]/i; 
    }
}

mint ncr(int n, int r){
    if(n<0||r<0||r>n) return mint(0); 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

mint nhr(int n, int r){
    return ncr(n+r-1,r-1); 
}

mint cnt[N]; 
mint dp[N]; 

void solve(){
    int l,n; cin>>l>>n; 
    // 반포함 x 
    mint ans = 0; 
    for(int k=1;k<=l/2;k++){
        mint t = ncr(k-1,n-2); 
        if(n==2&&k*2==l) t/=2; 
        ans += t*l*k; 
        dbg(t,k,n)
    }
    if(n==2){
        cout << ans.val(); return; 
    }
    dbg(ans)
    // a_i > k 인 것이 t 개 일때 연속에 t개가 없는 가짓수 -> dp[t] 
    // x_0 + x_1 ... x_t = n-t    x_0 >=0, x_t >=0 -> n-t-(t-1) H t+1 
    // 맨 앞 맨 뒤 
    // t-2 개 사이에  -> t-1 개 합이 n-t   
    for(int t =0;t<=n/2; t++){
        dp[t] = nhr(n-t-(t-1),t+1); 
        //dbg(t,dp[t])
        if(t>=2){
            if(n==2) dp[t] = 0; 
            else {
                dp[t] -= ncr(n-t-1-1,t-1); 
            }
        }
        dbg(t,dp[t])
    }

    // 반포함 o 
    // a_1 + ... a_n = L 
    // a_i <= (L-1)/2 
    // min(a_i,a_i+1) <= k 인 가짓수 : cnt[k] 
    for(int k=1;k<=(l-1)/2;k++){
        // >k 의 개수가 t 개 이상 
        vector<mint> u(l/k+10); 
        for(int t=0;t*(k+1)<=l;t++){
            // 전체 - (l-1)/2 보다 큰거 하나 + (l-1)/2 보다 큰거 두개 (x)
            mint tmp = nhr(l-(k+1)*t-(n-t),n) - (n-t)*nhr(l-(k+1)*t-(n-t-1)-(l-1)/2-1,n) - t*nhr(l-(k+1)*(t-1)-(n-t)-(l-1)/2-1,n); 
            u[t] = tmp; 
        }
        for(int t=0;t<u.size();t++){
            mint gg = u[t]-u[t+1]; // >k 인 것이 t 개 
            cnt[k] += gg*dp[t]; 
        }
        dbg(k,cnt[k])
    }
    for(int k=1;k<=(l-1)/2;k++){
        // min(a_i,a_i+1) ==k 
        mint gg = cnt[k]-cnt[k-1]; 
        ans += gg*k*l/n; 
    }
    cout << ans.val(); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   init(); 
   //cin >> t;
   while(t--) solve(); 
   return 0;
}