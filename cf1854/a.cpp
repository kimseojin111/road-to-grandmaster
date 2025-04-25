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


const int N = 30;
ll a[N]; 

void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>a[i]; 
    int p=0,q=0; 
    // p -> 모두 양수로, 먼저 음수 개수  q-> 모두 음수로 , 먼저 양수 개수 
    auto print = [&](auto v){
        cout << v.size() << "\n"; 
        for(auto [a,b]:v) cout << a << " " << b << "\n"; 
        return; 
    }; 
    rrep(i,n) if(a[i]>0) q++; else if(a[i]<0) p++; 
    if(p==0){
        // 모두 양수 
        vector<pair<int,int>> ans; 
        for(int i=2;i<=n;i++) ans.pb({i,i-1}); 
        print(ans); 
        return; 
    }
    if(q==0){
        // 모두 음수 
        vector<pair<int,int>> ans; 
        for(int i=n-1;i>0;i--) ans.pb({i,i+1}); 
        print(ans); 
        return; 
    }
    int pm = *max_element(a+1,a+n+1), mm = *min_element(a+1,a+n+1); 
    mm = -mm; 
    dbg(pm,mm)
    int k = 0; 
    while((1<<k)*pm < mm) k++; 
    p+=k; 
    k = 0; 
    while((1<<k)*mm < pm) k++; 
    q += k; 
    if(p<=12){
        vector<pair<int,int>> ans; 
        int pi = max_element(a+1,a+n+1)-a; 
        int k = 0; 
        while(pm < mm){
            ans.pb({pi,pi}); 
            pm += pm; 
        }
        dbg(pm)
        rrep(i,n) if(a[i]<0) {
            ans.pb({i,pi}); pm+=pm; 
        }
        for(int i=2;i<=n;i++) ans.pb({i,i-1}); 
        print(ans); 
        return; 
    }
    if(q<=12){
        vector<pair<int,int>> ans; 
        int qi = min_element(a+1,a+n+1)-a; 
        int k = 0; 
        while(mm < pm){
            ans.pb({qi,qi}); 
            mm += mm; 
        }
        rrep(i,n) if(a[i]>0) {
            ans.pb({i,qi});  
        }
        for(int i=n-1;i>0;i--) ans.pb({i,i+1}); 
        print(ans); 
        return; 
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