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

const int N = 1000100; 
int a[N], ind[N], dd[N]; 
bool vis[N]; 
#include <atcoder/modint>
using namespace atcoder; 
using mint = modint1000000007; 

void solve(){
    int n; cin>>n; 
    // cycle 만들고 ind 만들고 ok 
    rrep(i,n){
        cin>>a[i]; if(i!=a[i]) ind[a[i]]++, dd[a[i]]++; 
    }
    queue<int> q; 
    rrep(i,n) if(ind[i]==0) q.push(i); 
    mint ans = 1; 
    while(!q.empty()){
        int f= q.front(); q.pop(); 
        vis[f] = 1; 
        if(a[f]!=f){
            ind[a[f]]--; 
            if(ind[a[f]]==0) {
                q.push(a[f]); 
            }
        }
    }
    rrep(i,n) {
        if(vis[i]){
            if(a[i]!=i) ans = ans * (dd[i]+1); 
        }
    }
    rrep(i,n) if(!vis[i]){
        int now = i; 
            vector<int> cyc; 
            do {
                cyc.pb(now); now = a[now]; 
            } while(now!=i);
            dbg(cyc)
            for(auto x : cyc) vis[x] = 1; 
            mint koko = 1, ss = 0; 
            for(auto x : cyc) koko *= (dd[x]+1), ss += (dd[x]); 
            dbg(koko.val(),ss.val())
            koko -= ss; 
            ans *= koko; 
    }
    cout << ans.val(); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}