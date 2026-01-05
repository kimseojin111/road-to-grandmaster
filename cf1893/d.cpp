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
int a[N]; 
vector<vector<int>> can[N]; 
int s[N],d[N]; 
int cnt[N];

void solve(){
    int n,m; cin>>n>>m;
    rrep(i,n) cnt[i]=0; 
    rrep(i,m) can[i].clear(); 
    rrep(i,n) cin>>a[i]; 
    rrep(i,n) cnt[a[i]]++; 
    rrep(i,m) cin>>s[i]; 
    rrep(i,m) cin>>d[i]; 
    set<pair<int,int>> fuck; // 개수, 종류 
    rrep(i,n){
        if(cnt[i]) fuck.insert({cnt[i],i}); 
    }
    rrep(i,m){
        while(s[i]){
            int re = min(s[i],d[i]); 
            s[i] -= re; 
            if(fuck.size()<re){
                cout << -1 << "\n"; return; 
            }
            vector<pair<int,int>> tmp; 
            rep(j,re) {
                tmp.pb(*fuck.rbegin()); 
                fuck.erase(*fuck.rbegin()); 
            }
            dbg(tmp)
            vector<int> god; 
            for(auto [cn,j]:tmp){
                god.pb(j); if(cn>1) fuck.insert({cn-1,j}); 
            }
            can[i].pb(god); 
        }
    }
    auto print = [&](int i){
        auto& v = can[i]; 
        reverse(all(v)); 
        int sz = v[0].size(); 
        map<int,int> pos; 
        vector<vector<int>> ans;
        vector<int> pp;  
        for(int j=0;j<sz;j++){
            //cout << v[0][j] << " "; 
            pp.pb(v[0][j]); 
            pos[v[0][j]] = j; 
        }
        ans.pb(pp); 
        for(int u=1;u<v.size();u++){
            vector<int>pp; 
            vector<int> toans(v[u].size()); 
            for(auto x : v[u]) if(pos.find(x)!=pos.end()){
                if(pos[x]<toans.size()) toans[pos[x]] = x; 
            }
            int p=0; 
            for(auto x : v[u]) if(pos.find(x)==pos.end()){
                while(p<toans.size()&&toans[p]!=0)p++; 
                assert(p<toans.size());
                toans[p] = x; p++; 
            }
            //for(auto x : toans) cout << x << " "; 
            ans.pb(toans); 
            pos.clear(); 
            for(int i=0;i<toans.size();i++) pos[toans[i]]=i; 
        }
        reverse(all(ans)); for(auto &v:ans) for(auto x  : v) cout << x << " "; 
    };
    rrep(i,m){
        print(i); cout << "\n";
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}