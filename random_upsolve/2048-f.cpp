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

const int N = 200010; 
ll a[N],b[N],l[N],r[N]; 
ll dp[N][150]; 
const int K = 70; 
const ll inf = 2e18;
bool flag = false;  

ll mceil(ll a, ll x){
    return (a+x-1)/x; 
}
void dfs(int i){ 
    if(l[i]!=-1){
        dfs(l[i]); 
    }
    else l[i]=N-1; 
    if(r[i]!=-1){
        dfs(r[i]); 
    }
    else r[i]=N-1; 
    int f,s; 
    for(f=0,s=0;f<K&&s<K;){
        // le[i] >= re[j] 인 최대의 j 까지 
        if(dp[l[i]][f]>=dp[r[i]][s]){
            dp[i][f+s] = dp[l[i]][f]; f++; 
        }
        else {
            dp[i][f+s] = dp[r[i]][s]; s++; 
        }
    } 
    while(f<K){
        dp[i][f+K] = dp[l[i]][f]; f++; 
    }
    while(s<K){
        dp[i][s+K] = dp[r[i]][s]; s++; 
    }
    for(int j=0;j<150;j++) dp[i][j] = max(dp[i][j],a[i]); 
    for(int j=1;j<K;j++){
        dp[i][j] = min(mceil(dp[i][j-1],b[i]),dp[i][j]); 
    }
    return; 
}

void solve(){
    int n;cin>>n; 
    if(n==200000) flag =true; 
    fill(l,l+n,-1); fill(r,r+n,-1); 
    rep(i,n) cin>>a[i]; 
    rep(i,n) cin>>b[i]; 
    rep(i,n) rep(j,K) dp[i][j] = 0; 
    vector<int> st; 
    rep(i,n){
        int last = -1; 
        while(!st.empty()&&b[st.back()]>b[i]) {
            last = st.back(); st.pop_back(); 
        }
        if(!st.empty()) r[st.back()] = i; 
        l[i] = last; 
        st.pb(i); 
    }
    while(st.size()>1) st.pop_back(); 
    rep(i,n){
        dbg(i,l[i],r[i])
    }
    int rt = st[0]; 
    int ans = 0; 
    dfs(rt); 
    while(dp[rt][ans]>1)ans++; 
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