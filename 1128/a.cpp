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

const int N = 200010; 
int ne[N], rne[N]; 
int a[N]; 
vector<int> pos[N]; 
bool vis[N]; 

void init(int n){
    rrep(i,n) ne[i] = rne[i] = 0; 
    rep(i,n) pos[i].clear(); 
}

struct union_find {
    int n; vector<int> par; vector<int> d; 
    union_find(int n) : n(n) {
        par.resize(n+1); d.resize(n+1); 
        rrep(i,n) par[i] = i; 
    }
    int find(int x){
        return x==par[x] ? x : par[x]=find(par[x]); 
    }
    bool merge(int a, int b){
        a = find(a), b = find(b); 
        if(a==b) return false; 
        par[a] = b; 
        d[b] = min(d[a],d[b]); 
        dbg(a,b,d[a],"wtf????????????")
        return true; 
    }
}; 

void solve(){
    // x+1 모두가 x랑 매칭되고 
    // 0 이 하나만 나오기 
    int n; cin>>n; 
    init(n); 
    union_find uf(n); 
    dbg(n); 
    rrep(i,n){
        cin>>a[i]; pos[a[i]].pb(i); 
        uf.d[i] = a[i]; 
    }
    ne[n] = -1; rne[1] = -1; 
    rrep(i,n-1) ne[i] = i+1; 
    for(int i=n;i>=2;i--) rne[i] = i-1; 
    dbg(n)
    auto erase = [&](int i) {
        {
            int a = rne[i], b = ne[i]; 
            if(a!=-1)ne[a] = b; if(b!=-1) rne[b] = a; 
        } 
    }; 
    for(int ia=n-1;ia>0;ia--){
        auto& p = pos[ia-1]; auto& q = pos[ia]; 
        dbg(p,q)
        for(auto x : p) vis[x] = 0; 
        for(auto x : q){
            // x 이전 최대 p 
            int l = rne[x]; 
            if(l!=-1&&(a[l]==ia||a[l]==ia-1)) {
                uf.merge(x,l); 
            } 
            int r = ne[x]; 
            if(r!=-1&&(a[r]==ia||a[r]==ia-1)) {
                dbg(x,r,"wtf??????????????")
                uf.merge(r,x); 
            }
            dbg(l,r)
        }
        for(auto x : q){
            int k = uf.find(x); 
            dbg(x,k,"wtf?",uf.d[k])
            if(uf.d[k]==ia-1){
                erase(x); continue; 
            } else {
                cout << "NO\n"; 
                return; 
            }
        }
    }
    if(pos[0].size()==1) {
        cout << "YES\n"; return;
    } else cout << "NO\n"; 
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) solve(); 
    return 0;
}