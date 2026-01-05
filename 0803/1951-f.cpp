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

struct seg {
    vector<int> fen; 
    int N; 
    seg(int N): N(N) {
        fen.resize(N+3); 
    }
    void upd(int p, int v){
        while(p<N+2){
            fen[p] += v; p += p&-p; 
        }
    }
    int qry(int p){
        int re = 0; 
        while(p){
            re += fen[p]; p-=p&-p; 
        }
        return re; 
    }
    int qry(int l, int r){
        int re = qry(r)-qry(l-1);
        return re; 
    }
}; 


void solve(){
    ll n,k; cin>>n>>k; 
    vector<int> p(n+1),q(n+1); 
    vector<int> rp(n+1); 
    rrep(i,n) cin>>p[i]; 
    rrep(i,n) rp[p[i]] = i; 
    auto calc = [&](vector<int> p){
        ll re = 0; 
        seg f(n); 
        rrep(i,n){
            re = re + f.qry(p[i]+1,n); 
            f.upd(p[i],1); 
        }
        return re; 
    }; 
    ll m = calc(p);  
    vector<int> rr(n+1); 
    rrep(i,n) {
        q[i] = n+1-i; 
    }
    auto shit = [&]{
        rrep(i,n){
            rr[i] = q[p[i]]; 
        }
        return calc(q)+calc(rr); 
    }; 
    ll M = shit(); 
    dbg(m,M)
    if(k<m||k>M||(k%2!=m%2)){
        cout<<"NO"<<"\n"; return; 
    }
    int x = 0; 
    int l = 1,r=n; 
    while(l<=r){
        int m = l+r>>1; 
        for(int i=m;i>0;i--) q[i] = m+1-i; 
        for(int i=m+1;i<=n;i++) q[i] = i; 
        dbg(m,shit())
        if(shit()<=k) {
            x = m; l=m+1; 
        }
        else r=m-1; 
    }
    if(x==n){
        cout << "YES\n"; 
        rrep(i,n) cout<<(n+1-i) << " \n"[i==n]; 
        return; 
    }
    dbg(x)
    for(int i=1;i<=x;i++) q[i] = x+1-i; 
    for(int i=x+1;i<=n;i++) q[i] = i; 
    ll now = shit(); 
    int pv = 1; 
    dbg(q,now)
    while(now<k){
        if(rp[pv]<rp[x+1]) now+=2; 
        swap(q[pv],q[x+1]); pv++; 
        dbg(shit(),now)
    }
    cout << "YES\n"; 
    rrep(i,n) cout << q[i] << " \n"[i==n]; 
    assert(shit()==k);
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}