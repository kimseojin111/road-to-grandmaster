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

const int N = 500010; 
int a[N]; 
int P[N]; 
int R[N]; 

void solve(){
    int n,Q; cin>>n>>Q; 
    rrep(i,n) P[i] = 0; 
    rrep(i,n) R[i] = 0; 
    rrep(i,n) cin>>a[i]; 
    vector<int> p; 
    for(int i=2;i<=n;i++) if(a[i]<a[i-1]) p.pb(i); 
    for(int i=1;i<p.size();i++) if(a[p[i]]<a[p[i-1]]) {
        P[p[i]] = 1; 
    }
    for(int i=4;i<=n;i++){
        
    }
    for(int i=1;i<=n;i++) P[i] += P[i-1]; 
    while(Q--){
        int l,r; cin>>l>>r; 
        if(r-l<=1){
            cout << "YES\n"; continue; 
        }
        // 만약 q를한개 포함 
        auto it = lower_bound(all(p),l+1); 
        if(it==p.end()||*it>=r) {
            cout << "YES\n"; continue; 
        }
        int L = *it; 
        it = upper_bound(all(p),r); 
        if(it==p.begin()) {
            cout << "YES\n"; continue; 
        }
        int R = *prev(it); 
        if(L>=R){
            cout << "YES\n"; continue; 
        }
        int dd = P[R]-P[L]; 
        if(dd){
            cout<< "NO\n"; 
        }
        else {
            cout << "YES\n";
        }

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