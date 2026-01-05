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
    int n,q; cin>>n>>q; 
    auto fuck = [&](int from, int to, int other) {
        // vector<pair<int,int>> (other 위치, 비용) 
        vector<pair<int,int>> re; 
        // 무조건 cock wise 
        int ntt = to; if(ntt<from) ntt += n; 
        int cl = 0; int ot = other; 
        if(other>=from&&other<=ntt) cl += (ntt-other+1), ot = (ntt+1)%n; 
        else if(other+n>=from&&other+n<=ntt) cl += (ntt-n-other+1), ot = (ntt+1)%n; 
        cl += (ntt-from); 
        re.pb({ot,cl});
        ntt = to; if(ntt>from) ntt -= n;  
        int cr = 0; ot = other; 
        if(other<=from&&other>=ntt) cr += (other-ntt+1), ot = (ntt-1+n)%n;
        if(other-n<=from&&other-n>=ntt) cr += (other-n-ntt+1), ot = (ntt-1+n)%n; 
        cr += (from-ntt); 
        re.pb({ot,cr}); 
        return re; 
    }; // L, R 위치
    int pos[2] = {0,1}; 
    int hand = 0; // 0 이면 L 1이면 R 
    vector<ll> dp(n); 
    rep(i,n) dp[i] = 1e18; 
    dp[1] = 0; 
    int gigm = 0; 
    while(q--){
        vector<ll> ndp(n); 
        rep(i,n) ndp[i] = 1e18; 
        char h; int t; cin>>h>>t; t--; 
        int hand_now = h=='R'; 
        rep(i,n){
            if(dp[i]==1e18) continue; 
            // pos[hand] = gigm, pos[hand^1] = i, -> pos[hand_now] : t 
            pos[hand] = gigm, pos[hand^1] = i; 
            auto can = fuck(pos[hand_now],t,pos[hand_now^1]); 
            for(auto [ne,val] : can) ndp[ne] = min(ndp[ne],dp[i]+val); 
        }
        gigm = t; hand = hand_now; 
        rep(i,n) dp[i] = ndp[i];
    }
    cout << *min_element(all(dp)); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}