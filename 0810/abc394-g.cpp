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


vector<pair<int,int>> build[1000100]; 
int y[200010], z[200010]; 
int ans[200010]; 
int L[200010],R[200010]; 
int fuck[200010]; 
vector<int> chk[1000010]; 
int a[200010],b[200010],c[200010],d[200010]; 
int height[510][510]; 
int dx[4] = {1,-1,0,0}; 
int dy[4] = {0,0,1,-1}; 

struct uf{
    int n; vector<int> par; 
    uf(int n):n(n) {
        par.resize(n+1); rrep(i,n) par[i]=i;
    }
    int find(int x){
        return par[x]==x ? x : par[x]=find(par[x]); 
    }
    bool merge(int a, int b){
        a = find(a), b=find(b); 
        if(a==b) return false; 
        par[a] = b; return true; 
    }
}; 


void solve(){
    int h,w; cin>>h>>w; 
    auto get = [&](int i, int j){
        return i*w+j; 
    }; 
    rrep(i,h) rrep(j,w){
        int aij; cin>>aij; build[aij].pb({i,j}); 
        height[i][j] = aij; 
    }
    int q; cin>>q; 
    rrep(i,q){
        cin>>a[i]>>b[i]>>y[i]>>c[i]>>d[i]>>z[i]; 
        L[i]=1, R[i]=1000000; 
    }
    dbg(1)
    // a,b merge c,d 가 되는 최대 높이 
    // L[i],R[i] -> ans fuck[i] 
    int sz = get(h,w); 
    while(1){
        bool flag = true; 
        rrep(i,q){
            if(L[i]<=R[i]){
                dbg(i)
                flag = false; 
                int m = L[i]+R[i]>>1; 
                chk[m].pb(i); 
            }
        }   
        if(flag) break; 
        uf U(sz); 
        for(int h=1000000;h>0;h--){
            for(auto [p,q]:build[h]) {
                rep(k,4){
                    int pp=p+dx[k],qq=q+dy[k]; 
                    if(height[pp][qq]>=h) U.merge(get(p,q),get(pp,qq)); 
                }
            } 
            if(!chk[h].empty()){
                dbg(chk[h],h)
            }
            for(auto x : chk[h]){
                int p = U.find(get(a[x],b[x])), q = U.find(get(c[x],d[x])); 
                if(p==q){
                    fuck[x] = h; L[x] = h+1; 
                } else {
                    R[x] = h-1; 
                }
            }
            chk[h].clear(); 
        }
    }
    rrep(i,q){
        if(fuck[i]>=min(y[i],z[i])) cout << (abs(y[i]-z[i])) << "\n";
        else cout << (y[i]+z[i]-fuck[i]*2) << "\n"; 
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