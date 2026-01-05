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

const int N = 200100;
int a[N]; 
int p[N]; 

void solve(){
    int n,q; cin>>n>>q; 
    rrep(i,n) cin>>a[i]; 
    vector<pair<int,int>> s; 
    for(int i=1,j=1;i<=n;){
        j = i+1; 
        while(j<=n&&a[j]<=a[j-1]) j++; 
        if((j-i)>2){
            s.pb({i,j-1}); 
        }
        i=j;
    }
    int t = s.size(); 
    dbg(s)
    if(t==0){
        while(q--){
            int l,r; cin>>l>>r; cout << (r-l+1) << "\n"; 
        }
        return;
    }
    vector<int> L,R; 
    for(auto [l,r]:s) L.pb(l),R.pb(r); 
    rep(i,t){
        auto [l,r] = s[i]; 
        p[i] = (r-l+1)-2; 
        if(i>0) p[i] += p[i-1]; 
    }
    //dbg(s)
    while(q--){
        int l,r; cin>>l>>r; 
        int f = lower_bound(all(L),l) - L.begin(); 
        int d = upper_bound(all(R),r) - R.begin(); 
        d--; 
        //dbg(f,d)
        int ans =0; 
        //if(d>=0) ans = p[d] - (f==0 ? 0 : p[f-1]); 
        if(f<t && R[f]<=r){
            ans = p[d] - (f==0 ? 0 : p[f-1]); 
        }
        if(f>0){
            auto [p,q] = s[f-1]; 
            int pp = max(p,l), qq = min(q,r); 
            if(qq>=pp+2) ans += (qq-pp-1); 
        }
        if(d<t-1 && d+1!=f-1){
            auto [p,q] = s[d+1]; 
            int pp = max(p,l), qq = min(q,r); 
            if(qq>=pp+2) ans += (qq-pp-1); 
        }
        cout << (r-l+1-ans) << "\n";
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}