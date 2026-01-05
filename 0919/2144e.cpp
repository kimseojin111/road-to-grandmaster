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
    int n; cin>>n; string s; cin>>s; 
    int d = 0; 
    for(auto c : s) if(c=='(') d++; else d--; 
    d%=4; if(d<0) d=(d+4)%4; 
    dbg(d)
    if(d){
        cout << -1 << "\n"; return; 
    }
    bool all1 = true; 
    for(int i=0;i+1<n;i++) if(s[i]==s[i+1]) all1 = false; 
    if(all1){
        if(s[0]=='(') cout << s << "\n"; 
        else cout << -1 << "\n"; 
        return; 
    }
    auto swp = [&](int i){
        if(s[i]=='(') s[i] = ')'; 
        else s[i] = '('; 
    }; 
    if(s[0]==')'){
        int i = 0; 
        while(s[i]!=s[i+1]) i++; 
        for(int j=i;j>=0;j--) {
            swp(j); swp(j+1); 
        }
    }
    if(s[n-1]=='('){
        int i = n-1; 
        while(s[i]!=s[i-1]) i--; 
        for(int j=i;j<n;j++) {
            assert(s[j]==s[j-1]); 
            swp(j); swp(j-1); 
        }
    }
    for(int i=0;i+1<n-1;i++){
        if(s[i]==')'&&s[i+1]==')'){
            swp(i); swp(i+1); 
        }
    }
    dbg(s)
    vector<pair<int,int>> v; 
    // ( 0 ) 1 
    for(int i=0;i<n;){
        int j = i; while(j<n&&s[j]==s[i]) j++; 
        int t = s[i]==')'; 
        if(i==0||t==1){
            v.pb({t,j-i}); 
        } else {
            int cnt = j-i; 
            v[0].ss += (cnt/2)*2; 
            v.pb({t,cnt&1}); 
        }
        i=j; 
    }
    dbg(v)
    int sum = 0; 
    for(auto [t,cnt]:v) if(t==0) sum+=cnt; else sum-=cnt; 
    auto [dd,cnt] = v[0]; 
    rep(i,cnt-sum/2) cout << '('; 
    rep(i,sum/2) cout << ')'; 
    for(int i=1;i<v.size();i++) {
        auto [t,cnt] = v[i]; if(t==0) rep(j,cnt) cout << '('; 
        else rep(j,cnt) cout<<')'; 
    }
    cout << "\n"; return; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}