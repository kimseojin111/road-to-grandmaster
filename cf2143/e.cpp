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

// ( -> 0,   ) -> 1

void solve(){
    int n; cin>>n; 
    deque<pair<int,int>> v; 
    string s; cin>>s; 
    if(n==1){
        cout << -1 << "\n";return; 
    }
    int d = 0; 
    for(auto c : s) if(c=='(') d+=1; else d-=1; 
    d%=4; if(d<0) d=(d+4)%4; 
    dbg(d,s)
    if(d!=0){
        cout << -1 << "\n"; return; 
    } 
    for(int i=0;i<s.size();){
        int j=i; while(j<n&&s[i]==s[j]) j++; 
        if(s[i]=='(') {
            v.pb({0,j-i}); 
        }
        else {
            v.pb({1,j-i});
        }
        i = j; 
    }
    dbg(v)
    bool all1 = true; 
    for(auto [a,b]:v) if(b>1) all1=false; 
    if(all1){
        if(s[0]=='(') cout << s << "\n"; 
        else {
            cout << -1 << "\n"; return; 
        }
        return; 
    }
    if(s[0]==')'){
        int i = 0; 
        while(s[i]!=s[i+1]) i++; 
        for(int j=i;j>=0;j--){
            if(s[j]==')') s[j] = s[j+1] = '('; 
            else s[j] = s[j+1] = ')'; 
        }
    }
    if(s[n-1]=='('){
        int i = n-1; 
        while(s[i-1]!=s[i]) i--; 
        for(int j=i;j<n;j++){
            if(s[j]==')') s[j] = s[j+1] = '('; 
            else s[j] = s[j+1] = ')'; 
        }
    }


    dbg(s)
    v.clear(); 
    for(int i=0;i<s.size();){
        int j=i; while(j<n&&s[i]==s[j]) j++; 
        if(s[i]=='(') {
            v.pb({0,j-i}); 
        }
        else {
            v.pb({1,j-i});
        }
        i = j; 
    }
    dbg(v)
    // ( -> 0,   ) -> 1
    vector<pair<int,int>> shit; 
    for(int i=0;i<v.size();i++){
        if(v[i].ff==0) {
            shit.pb(v[i]); 
        } else {
            if(v[i].ss%2){
                auto [op,cnt] = shit.back(); shit.pop_back(); 
                cnt += (v[i].ss/2)*2; 
                shit.pb({op,cnt}); 
                shit.pb({1,1}); 
            }
            else {
                auto [op,cnt] = shit.back(); shit.pop_back(); 
                cnt += (v[i].ss/2)*2; 
                shit.pb({op,cnt}); 
            }
        }
    }
    dbg(shit)
    vector<pair<int,int>> fuck; 
    for(int i=0;i<shit.size();i++){
        dbg(i,fuck)
        auto [op,cnt] = shit[i]; 
        if(i==0){
            fuck.pb(shit[i]); continue; 
        }
        if(op==0){
            fuck[0].ss += (cnt/2)*2; 
            fuck.pb({op,cnt%2}); 
        }
        else fuck.pb(shit[i]); 
    }
    int sum = 0; 
    for(auto [op,cnt]:fuck) if(op==0) sum+=cnt; else sum-=cnt; 
    dbg(sum)
    auto [op,cnt] = fuck[0]; 
    rep(i,cnt-(sum/2)) cout << '('; 
    rep(i,sum/2) cout << ')'; 
    dbg(fuck)
    for(int i=1;i<fuck.size();i++) {
        auto [op,cnt] = fuck[i]; 
        if(op==0) rep(i,cnt) cout << '('; 
        else rep(i,cnt) cout << ')'; 
    }
    cout << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}