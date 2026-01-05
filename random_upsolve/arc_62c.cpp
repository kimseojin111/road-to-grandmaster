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

int cyc(array<int,4>& v){
    bool flag = true; 
    rep(i,4) if(v[i]!=v[0]) flag = false; 
    if(flag) return 1; 
    if((v[0]==v[2])&&(v[1]==v[3])) return 2; 
    return 4; 
}

int ncyc(array<int,4> v){
    int p = cyc(v); 
    if(p==1) return 4; 
    if(p==2) return 2; 
    return 1; 
}

array<int,4> rot(array<int,4>v, int k){
    while(k--){
        int f = v[0]; for(int i=0;i<3;i++) v[i] = v[i+1]; v[3] = f; 
    }
    return v; 
}

bool same(array<int,4>v, array<int,4>w){
    rep(k,4) if(rot(v,k)==w) return true; 
    return false; 
}

array<int,4> c[410]; 

using ds = array<int,4>; 

ll npr(int n, int r){
    //dbg(n,r)
    if(r<0||r>n) return 0LL; 
    ll re = 1; 
    for(int i=n;i>n-r;i--){
        re = re*i; 
    }
    return re; 
}

ll po(int n, int k){
    ll re = 1; 
    //dbg(n,k)
    while(k--) re*=n; 
    return re; 
}

void solve(){
    map<array<int,4>,int> M; 
    int n; cin>>n; 
    rep(i,n) {
        rep(j,4) cin>>c[i][j]; 
        int rt = cyc(c[i]); 
        rep(j,rt){
            M[rot(c[i],j)]++; 
        }
    }   
    ll ans = 0; 
    bool goat = false; 
    rep(i,n) rep(j,n) rep(k,4) if(i!=j){
        if(i==2&&j==5&&k==0) goat = true; 
        auto a = c[i], b = rot(c[j],k); 
        array<int,4> e = {a[1],b[0],b[3],a[2]}; 
        array<int,4> f = {b[1],a[0],a[3],b[2]}; 
        ds d = {a[3],a[2],b[3],b[2]}; 
        ds c = {b[1],b[0],a[1],a[0]}; 
        vector<ds> v; 
        v.pb(a); v.pb(b); v.pb(e); v.pb(f); v.pb(d); v.pb(c); 
        bool vis[6] = {0,}; 
        int cnt[6] = {0,0,1,1,1,1}; 
        ll tmp = 1; 
        for(int i=0;i<6;i++) if(!vis[i]){
            int ff = cnt[i]; 
            int gg = 1-cnt[i]; 
            for(int j=i+1;j<6;j++) if(!vis[j]) {
                if(same(v[i],v[j])){
                    vis[j] = 1;
                    ff += cnt[j];
                    gg += 1-cnt[j];   
                }
            }
            int no = M[v[i]]; 
            if(no-ff<gg) {
                tmp = 0; break; 
            }
            tmp = tmp*npr(no-gg,ff)*po(ncyc(v[i]),ff); 
        }
        ans += tmp; 
        goat = false; 
    }
    cout << ans/6; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}