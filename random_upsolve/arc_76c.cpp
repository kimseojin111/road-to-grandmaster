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

void solve(){
    int r,c; int n; 
    vector<pair<int,int>> v; 
    // [0,r] [0,c] x=0 -> y (c)   x>0, y=c -> y+x,  ,     x=r, y -> r+c+c-y ->   y=0 -> r+2c+r-x 
    cin>>r>>c>>n; 
    auto cc = [&](int x, int y){
        return ((x==0)||(x==r)||(y==0)||(y==c)); 
    }; 
    auto f = [&](int x, int y){
        if(x==0) return y; 
        if(x>0&&y==c) return c+x; 
        if(x==r) return r+2*c-y; 
        if(y==0) return r+2*c+r-x; 
    };
    int N = 2*r+2*c; 
    rep(i,n){
        int x,y,xx,yy; cin>>x>>y>>xx>>yy; 
        if(!cc(x,y)) continue; 
        if(!cc(xx,yy)) continue; 
        v.pb({f(x,y),f(xx,yy)}); 
    }
    for(auto&[a,b]:v) {
        if(a>b) swap(a,b); 
    }
    sort(all(v)); 
    dbg(v)
    priority_queue<int,vector<int>,greater<>> pq; 
    for(auto [a,b]:v) {
        if(pq.empty()) pq.push(b); 
        else {
            while(!pq.empty()&&pq.top()<a) pq.pop(); 
            if(!pq.empty()&&pq.top()<b) {
                cout << "NO\n"; return; 
            }
            pq.push(b); 
        }
    }
    cout << "YES\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}