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

struct fen{
    vector<ll> a; int n; 
    fen(int n) : n(n) {
        a.resize(n+1); 
    }
    void upd(int p, ll v){
        while(p<n){
            a[p]+=v; p+=p&-p; 
        }
    }
    ll qry(int p){
        ll re = 0; 
        while(p){
            re += a[p]; p-=p&-p; 
        }
        return re; 
    }
    ll qry(int l, int r){
        return qry(r) - qry(l-1); 
    }
}; 

void solve(){
    ll n,k; cin>>n>>k; 
    vector<int> p(n+1), rp(n+1); 
    rrep(i,n){
        cin>>rp[i]; p[rp[i]] = i; 
    }
    vector<ll> inv(n+1); 
    fen F(n+10); 
    rrep(i,n){
        inv[i] = F.qry(p[i]+1,n); 
        F.upd(p[i],1); 
    }
    ll lb = accumulate(all(inv),0LL); 
    ll ub = (ll)n*(n-1) - lb; 
    if(k<lb||k>ub||(k%2!=lb%2)) {
        cout << "NO\n"; return; 
    }
    int x = 1; 
    k -= lb; 
    while(k>=0){
        if(k>(x-1-inv[x])*2){
            k -= (x-1-inv[x])*2; x++; continue; 
        }
        vector<int> q(n+1); 
        for(int i=1;i<x;i++) q[i] = x-i; 
        for(int i=x;i<=n;i++) q[i] = i; 
        int pv = x; 
        dbg(x,q)
        while(k){
            if(p[q[pv-1]]<p[q[pv]]) {
                k-=2; 
            }
            swap(q[pv-1],q[pv]); pv--; 
        }
        cout << "YES\n"; 
        vector<int> ans(n+1); 
        rrep(i,n) ans[q[i]] = i; 
        rrep(i,n) cout<<ans[i]<<" \n"[i==n]; 
        return; 
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