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
int L[N], R[N]; 

void solve(){
    int n ; cin>>n; 
    rrep(i,n) cin>>a[i];
    vector<pair<int,int>> st1,st2;  
    for(int i=n;i>=1;i--){
        if(i==n){
            st1.pb({a[i],i}); st2.pb({a[i],i}); R[i] = n; continue; 
        }
        int j = n+1; 
        while(!st1.empty()&&st1.back().ff>a[i]){
            auto [f,idx] = st1.back(); st1.pop_back(); 
            if(idx!=i+1) j = min(j,idx); 
        }
        while(!st2.empty()&&st2.back().ff<a[i]){
            auto [f,idx] = st2.back(); st2.pop_back(); 
            if(idx!=i+1) j = min(j,idx); 
        }
        R[i] = min(R[i+1],j-1); 
        st1.pb({a[i],i}); st2.pb({a[i],i});
        dbg(i,R[i])
    }
    st1.clear(); st2.clear(); 
    for(int i=1;i<=n;i++){
        if(i==1){
            st1.pb({a[i],i}); st2.pb({a[i],i}); L[i] = 1; continue; 
        }
        int j = 0; 
        while(!st1.empty()&&st1.back().ff>a[i]){
            auto [f,idx] = st1.back(); st1.pop_back(); 
            if(idx!=i-1) j = max(j,idx); 
        }
        while(!st2.empty()&&st2.back().ff<a[i]){
            auto [f,idx] = st2.back(); st2.pop_back(); 
            if(idx!=i-1) j = max(j,idx); 
        }
        L[i] = max(L[i-1],j+1); 
        st1.pb({a[i],i}); st2.pb({a[i],i});
        dbg(i,L[i])
    }
    vector<pair<int,int>> v; 
    rrep(i,n) v.pb({L[i],R[i]}); sort(all(v)); 
    ll ans = 0; 
    int pv=0; int mx = 0;  
    rrep(i,n){
        while(pv<v.size()&&v[pv].ff<=i){
            mx =max(mx,v[pv].ss); pv++; 
        }
        ans+=(mx-i+1); 
    }
    cout << ans << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}