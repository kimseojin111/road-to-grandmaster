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

const int N = 100010; 
int p[N]; 
int a[N]; 

void solve(){
    int n,m; cin>>n>>m; 
    rrep(i,m) p[i] = 0,a[i]=0; 
    int L=0,R=0; 
    vector<int>v; 
    rep(i,n){
        int x; cin>>x; if(x==-1)L++; if(x==-2)R++; 
        if(x>0) {
            a[x]=1; v.pb(x); 
        }
    }
    rrep(i,m) p[i] = p[i-1]+a[i]; 
    sort(all(v)); v.erase(unique(all(v)),v.end()); 
    int ans = 0; 
    //dbg(v,L,R)
    for(int i=0;i<v.size();i++){
        int xi = v[i]; 
        int le = min(L+p[xi-1],xi-1); 
        int rr = min(R+p[m]-p[xi],m-xi); 
        //dbg(le,rr)
        ans = max(le+rr+1,ans); 
    }
    if(L){
        int k = min(m-1,p[m-1]+L-1) + 1; 
        ans = max(ans,k); 
    }
    if(R){
        int k = min(m-1,p[m]-p[1]+R-1)+1; 
        ans = max(ans,k); 
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