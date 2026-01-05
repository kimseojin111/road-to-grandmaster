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

int p[27]; 
// 개수 26개 1~26
vector<int> child[30]; 
int ne[30]; 
bool vis[30]; 

void solve(){
    int n; cin>>n; 
    string s,t; cin>>s>>t; 
    rep(i,n){
        int x = s[i]-'a'+1, y = t[i]-'a'+1; 
        if(p[x]!=0&&p[x]!=y){
            cout << -1 << "\n"; return; 
        } 
        if(p[x]==0) child[y].pb(x); 
        p[x] = y; 
    }
    int ans = 0;
    int tt = 0;  
    for(int i=1;i<=26;i++) {
        if(!child[i].empty()){
            if(p[i]==i) ans += (child[i].size()-1); 
            else ans += (child[i].size()); 
            tt++;  
            if(child[i].size()==1&&p[i]!=i){
                int j = p[i]; if(child[j].size()==1) ne[i] = j; 
            }
        }
    }
    if(tt==26){
        if(ans==0) cout << 0; 
        else cout << -1; 
        return; 
    }
    rrep(i,26) if(!vis[i]&&ne[i]) {
        set<int> c; vector<int> tmp; 
        int j = i; 
        while(1){
            if(j==0) break; 
            tmp.pb(j); 
            if(c.find(j)!=c.end()){
                ans++; break; 
            }
            if(vis[j]) break; 
            c.insert(j); j = ne[j]; 
        }
        for(auto x : tmp) vis[x] = 1; 
    }
    cout << ans; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}