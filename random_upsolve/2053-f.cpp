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

struct ds{
    int n; ll S,chM,M; 
    vector<ll> v; 
    ds(int n):n(n){
        v.resize(n+1); 
        S=chM=M=0; 
    }
    ll get(int i){
        ll t = v[i]; 
        if(t<chM) {
            v[i] = chM; t=chM; 
        }
        return t+S; 
    }
    void set(int i, ll x){
        v[i] = x-S; 
        M = max(M,x-S); 
    }
    ll getM(){
        return M+S; 
    }
    void allAdd(ll x){
        S+=x; 
    }
    void allChm(ll x){
        chM = max(chM,x-S); 
        M = max(M,chM); 
    }
}; 

const int N = 200010; 
ll u[N]; 
set<int> col[N]; 
map<int,ll> cnt[N]; 

void solve(){
    int n,m,k; cin>>n>>m>>k; 
    ds D(k); 
    rrep(i,n){
        u[i]=0; col[i].clear(); cnt[i].clear(); 
    }
    rrep(i,n){
        rep(j,m){
            int x; cin>>x; if(x==-1) u[i]++; 
            else {
                col[i].insert(x); cnt[i][x]++; 
            }
        }
    }
    for(int i=2;i<=n;i++){
        ll kk = 0; 
        for(auto j : col[i]){
            if(col[i-1].find(j)!=col[i-1].end()){
                kk += cnt[i][j]*cnt[i-1][j]; 
            }
        }
        D.allAdd(kk); 
        ll M = D.getM(); 
        for(auto j : col[i]){
            ll tmp = D.get(j)+u[i-1]*cnt[i][j]; 
            M = max(M,tmp); 
        }
        D.allAdd(u[i]*u[i-1]); 
        for(auto j : col[i]){
            ll s = D.get(j); 
            s += u[i-1]*cnt[i][j]; 
            D.set(j,s); 
        }
        D.allChm(M); 
        for(auto j : col[i-1]){
            ll s = D.get(j); 
            s += u[i]*cnt[i-1][j]; 
            D.set(j,s); 
        }
    }
    cout << D.getM() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}