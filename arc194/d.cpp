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

const int N = 10000;
mint fac[N]; 
mint rfac[N]; 

int pv = 0; 
vector<int> child[N]; 
int par[N]; 

pair<mint,string> dfs(int v, int p){
    if(child[v].empty()) {
        return make_pair((mint)1,"()"); 
    }
    vector<string> t; 
    mint ans = 1; 
    for(auto ne : child[v]) {
        auto [m,s] = dfs(ne,v); 
        ans *= m; t.pb(s); 
    }
    sort(all(t)); 
    vector<int> tmp; 
    for(int i=0;i<t.size();){
        int j = i; while(j<t.size()&&t[j]==t[i])j++; 
        tmp.pb(j-i); i=j; 
    }
    ans *= fac[t.size()]; 
    for(auto x : tmp) ans *= rfac[x]; 
    string re; 
    re.pb('('); for(auto &s : t) re += s; re.pb(')'); 
    return {ans,re}; 
}

void solve(){
    int n,x,y; cin>>n>>x>>y; 
    string s,t; cin>>s>>t; 
    vector<pair<int,int>> S; 
    int s0 = 0, s1 = 0, t0=0,t1=0; 
    for(auto c:s) if(c=='0') s0++; else s1++; 
    for(auto c:t) if(c=='0') t0++; else t1++; 
    dbg(s0,s1,t0,t1)
    if(s0!=t0||s1!=t1){
        cout << "No"; return; 
    }
    for(int i=0;i<s.size();){
        int j =i; while(j<s.size()&&s[j]==s[i])j++; 
        int l = j-i; 
        if(s[i]=='0'){
            l %= x; if(l>0) S.pb({l,0}); 
        }
        else {
            l %= y; if(l>0) S.pb({l,1}); 
        }
        i=j; 
    }
    vector<pair<int,int>> T; 
    for(int i=0;i<t.size();){
        int j =i; while(j<t.size()&&t[j]==t[i])j++; 
        int l = j-i; 
        if(t[i]=='0'){
            l %= x; if(l>0) T.pb({l,0}); 
        }
        else {
            l %= y; if(l>0) T.pb({l,1}); 
        }
        i=j; 
    }
    auto merge = [&](auto& v) {
        vector<pair<int,int>> re; 
        for(auto [l,c]:v){
            if(!re.empty()&&re.back().second==c){
                int t = re.back().second+c; 
                if(l==0) t%=x; else t%=y; 
                if(t==0){
                    re.pop_back(); continue; 
                }
                else {
                    re.back().second=t; 
                }
            }
            else re.pb({l,c}); 
        }
        return re; 
    }; 
    cout << (merge(S)==merge(T) ? "Yes":"No"); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}