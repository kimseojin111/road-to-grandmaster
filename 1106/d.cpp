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


void solve(){
    int n,k; cin>>n>>k; 
    string s; cin>>s; 
    string t; cin>>t; 
    int l=0,r=k; 
    int ans = -1; 
    bool gg = false; 
    while(l<=r){
        int m = l+r>>1; 
        bool dd = true; 
        for(int i=0,j=0;j<t.size();j++){
            while((j-i)>m) i++; 
            while(i<j && s[i]!=t[j]) i++; 
            if(i>=n || s[i]!=t[j]) {
                dd = false; break; 
            }
        }
        if(dd){
            gg = true; 
            ans = m; r = m-1; 
        } else {
            l = m+1; 
        }
    }
    if(!gg){
        cout << -1 << "\n"; return; 
    }
    cout << ans << "\n";
    if(ans==0){
        return; 
    }
    vector<string> shit; 
    vector<int> orig; 
    int m = ans; 
    for(int i=0,j=0;j<t.size();j++){
        while((j-i)>m) i++; 
        while(i<j && s[i]!=t[j]) i++; 
        orig.pb(i);
    }
    dbg(ans)
    shit.pb(t); 
    for(int step=ans-1;step>=0;step--){
        dbg(step)
        auto b = shit.back(); 
        vector<char> dd(n);  
        vector<int> norig(n,-1); 
        dbg(orig,b)
        for(int i=0;i<b.size();i++){
            if(orig[i]==i){
                norig[i] = i; dd[i] = b[i]; 
            } else {
                dd[i-1] = b[i]; 
                norig[i-1] = orig[i]; 
            }
        }
        for(int i=0;i<n;i++) if(norig[i]==-1){
            norig[i] = max(norig[i-1],max(i-step,0)); 
            dd[i] = s[norig[i]]; 
        }
        string u; for(auto c: dd) u.pb(c); 
        if(step!=0) shit.pb(u); 
        orig = norig; 
    }
    reverse(all(shit)); 
    for(auto c : shit) cout <<c<< "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}