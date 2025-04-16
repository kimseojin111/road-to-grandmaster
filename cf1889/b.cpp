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


set<int> pos; 
const int N = 200010; 
int psum[N]; 
int l[N],r[N]; 
int cnt[N]; 
vector<int> add[N]; 
vector<int> er[N]; 

void solve(){
    int n,m,k;cin>>n>>m>>k; 
    for(int i=0;i<n+2;i++) {
        psum[i]=0; add[i].clear(); er[i].clear(); 
    }
    rep(i,m) cnt[i]=0; 
    map<pair<int,int>,int> fuck; 
    rep(i,m){
        cin>>l[i]>>r[i]; 
        add[l[i]].pb(i); 
        er[r[i]+1].pb(i); 
    }
    set<int> s; 
    int shit = 0; 
    rrep(i,n){
        for(auto x : add[i]) s.insert(x); 
        for(auto x : er[i]) s.erase(x); 
        if(s.size()==1){
            cnt[*s.begin()]++; 
        }
        if(s.size()==2){
            auto it = s.begin(); 
            int a = *it; it++; 
            int b = *it; 
            if(a>b) swap(a,b); 
            fuck[{a,b}]++; 
        }
        if(s.size()==0) shit++; 
    }
    int ans = 0; 
    for(auto [k,v]:fuck){
        auto [a,b] = k; ans = max(cnt[a]+cnt[b]+v,ans); 
    }
    sort(cnt,cnt+m); 
    ans = max(cnt[m-1]+cnt[m-2],ans);
    cout << (ans+shit)<<"\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}