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

const int N = 5000*2; 
mint fac[N],rfac[N]; 
void init(){
    fac[0] = rfac[0] = 1; 
    for(int i=1;i<N;i++){
        fac[i] = i*fac[i-1]; 
        rfac[i] = rfac[i-1]/i; 
    }
}
mint ncr(int n, int r){
    if(r<0||r>n) return mint(0); 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

mint nhr(int n, int r){
    return ncr(n+r-1,n-1); 
}

void solve(){
    int n; cin>>n; 
    vector<int> p(n); 
    rep(i,n) cin>>p[i]; 
    p.pb(0); 
    sort(all(p)); 
    vector<int> tmp; 
    tmp = p; 
    tmp.erase(unique(all(tmp)),tmp.end()); 
    dbg(tmp)
    if(tmp[0]>0||tmp.back()<0){
        cout << 0 << "\n"; return; 
    }
    for(int i=0;i+1<tmp.size();i++) if(tmp[i]+1!=tmp[i+1]){
        cout << 0 << "\n"; return; 
    }
    unordered_map<int,int> org; 
    for(auto x : p) org[x]+=1; 
    int mx = tmp.back(); 
    reverse(all(tmp)); 
    mint ans = 0; 
    for(auto t : tmp){
        unordered_map<int,int> cnt; 
        for(int i=0;i<=mx;i++) cnt[i]+=1; 
        for(int i=mx-1;i>=t;i--) cnt[i]+=1; 
        mint fuck = 1; 
        for(auto cur : tmp){
            //dbg(cur,cnt[cur],org[cur])
            if(cnt[cur]>org[cur]) {
                fuck = 0; break; 
            } 
            if(cur==tmp.back()&&cnt[cur]!=org[cur]) {
                fuck = 0; break; 
            }
            int toadd = org[cur]-cnt[cur]; 
            fuck *= nhr(cnt[cur],toadd); 
            //dbg(cur,fuck)
            cnt[cur-1] += toadd; 
        }
        ans += fuck; 
    }
    cout << ans.val() << "\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    init(); 
    while(t--) solve(); 
    return 0;
}