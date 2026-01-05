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

const int N = 300010; 
int a[N],p[N],sz[N]; 
int ra[N]; 
vector<int> child[N]; 
set<int> fuck[N]; 
int gp[N]; 

void init(int n){
    rrep(i,n){
        sz[i] = 0; child[i].clear(); fuck[i].clear(); gp[i] = 0; 
    }
}

void solve(){
    int n,q; cin>>n>>q; 
    // x 에서 par[x] 의 같은 형제중 a[y] = a[x] + sz[x] 인 (x,y) 개수 -> 각 child - 1 개 
    // a[p[x]] + 1 = a[x] 인 x 개수 : 전체 부모 개수 
    init(n); 
    for(int i=2;i<=n;i++) {
        cin>>p[i]; child[p[i]].pb(i); 
    }
    p[1] = 1; 
    ra[0] = 0, ra[n+1] = n+1; 
    rrep(i,n) {
        cin>>a[i]; ra[a[i]] = i; 
    } 
    int gogo = 0; 
    for(int i=n;i>0;i--){
        sz[i] = 1; 
        for(auto x : child[i]) {
            sz[i] += sz[x]; 
        }
        sort(all(child[i])); 
        gogo += child[i].size(); 
    }
    int cnt = 0; 
    for(int i=1;i<=n;i++){
        if(a[p[i]]+1==a[i]) {
            cnt++; gp[p[i]] = 1; 
        }
        if(p[i]!=i){
            int ne = a[i]+sz[i]; 
            if(ne<=n){
                int f = ra[ne]; 
                if(p[f]==p[i]) cnt++; 
            }
        }
    }
    auto er = [&](int x) {
        int px = ra[a[x]+1]; 
        if(lower_bound(all(child[x]),px)!=upper_bound(all(child[x]),px)) cnt--; 
        px = ra[a[x]-1]; 
        if(p[x]==px) cnt--; 
        if(x!=1){
            int ne = a[x]+sz[x]; 
            if(ne<=n){
                int f = ra[ne]; 
                if(p[f]==p[x]) cnt--; 
            }
        }
    }; 
    auto ad = [&](int x){
        int px = ra[a[x]+1]; 
        if(lower_bound(all(child[x]),px)!=upper_bound(all(child[x]),px)) cnt++; 
        px = ra[a[x]-1]; 
        if(p[x]==px) cnt++; 
        if(x!=1){
            int ne = a[x]+sz[x]; 
            if(ne<=n){
                int f = ra[ne]; 
                if(p[f]==p[x]) cnt++; 
            }
        }
    }; 

    while(q--){
        int x,y; cin>>x>>y; 
        int px = ra[p[x]+1]; 
        er(x); er(y); 
        if(p[x]==y && a[x]==a[y]+1) cnt++; 
        if(p[y]==x && a[y]==a[x]+1) cnt++; 
        ra[a[y]] = x; ra[a[x]] = y; 
        swap(a[x],a[y]); 
        dbg(x,y,cnt)
        ad(x); ad(y); 
        if(p[x]==y && a[x]==a[y]+1) cnt--; 
        if(p[y]==x && a[y]==a[x]+1) cnt--;
        if(cnt==gogo){
            cout << "YES\n";
        } 
        else cout<<"NO\n";
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