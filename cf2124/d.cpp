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
    int n,k; cin>>n>>k; 
    k--;
    vector<int> v(n); vector<int> t;
    rep(i,n){
        cin>>v[i]; t.pb(v[i]); 
    }
    if(k==0){
        cout << "YES\n"; return; 
    }
    sort(all(t)); 
    int m = t[k-1]; 
    vector<pair<int,int>> ans; 
    rep(i,n) if(v[i]<m) ans.pb({v[i],i}); 
    if(ans.empty()){
        cout << "YES\n"; return; 
    }
    for(int j=0;j<ans.size();j++) if(ans[j].ff!=ans[ans.size()-1-j].ff){
        cout << "NO\n"; return; 
    }
    int lb = k - ans.size(); 
    int shit = 0; 
    vector<int> uu; 
    for(int j=0;j<ans.size();j++){
        int l = (j==0) ? 0 : ans[j-1].ss; 
        int r = ans[j].ss; 
        int bl = 0; 
        for(int k=l;k<=r;k++) if(v[k]==m) bl++; 
        uu.pb(bl); 
    }
    dbg(ans)
    int l = ans.back().ss, r = n-1; 
    int bl = 0; 
    for(int k=l;k<=r;k++) if(v[k]==m) bl++; 
    uu.pb(bl);
    dbg(uu)
    for(int i=0;i<uu.size()/2;i++){
        shit += min(uu[i],uu[uu.size()-1-i])*2; 
    }
    if(uu.size()%2){
        shit += uu[uu.size()/2]; 
    }

    if(shit>=lb) cout << "YES\n"; 
    else cout << "NO\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}