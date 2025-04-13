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

#include <atcoder/modint> 
using namespace atcoder; 

using mint = modint998244353; 
struct node {
    mint path[130]; 
    mint p[65]; 
}; 

node fuck[63]; 

bool flag = false; 

node merge(node a, node b){
    node t; 
    t.p[0] = 1; 
    for(int i=1;i<65;i++){
        t.p[i] = a.p[i-1] + b.p[i-1]; 
    }
    for(int i=0;i<130;i++){
        if(flag&&i==0){
            dbg(a.path[i].val(),b.path[i].val())
        }
        t.path[i] = a.path[i] + b.path[i]; 
    }
    for(int i=0;i<65;i++) for(int j=0;j<65;j++) if(i+j+2<130){
        t.path[i+j+2] += a.p[i]*b.p[j]; 
    }
    for(int i=0;i<65;i++){
        t.path[i+1] += a.p[i] + b.p[i]; 
    }
    return t; 
} 

node get(ll n, int k){
    //dbg(n,k,fuck[1].path[0].val())
    if(n==1) return fuck[1];
    ll t = (1LL<<k)+(1LL<<k-1); 
    if(n==(1LL<<k+1)-1) return fuck[k+1];  
    if(n<t){
        dbg(n,t)
        flag = true; 
        return merge(get(n-(1LL<<k-1),k-1),fuck[k-1]); 
    }
    return merge(fuck[k],get(n-(1LL<<k),k-1)); 
}

mint poi[130]; 
mint poii[130]; 

void solve(){
    ll n,m; cin>>n>>m; 
    int k = 0; 
    while((1LL<<k)<=n) k++; 
    k--; 
    node shit = get(n,k); 
    shit.path[0] = n; 
    mint ans = 0; 
    for(int i=0;i<5;i++){
        dbg(shit.path[i].val())
    }
    for(int i=1;i<=m;i++){
        mint pi = i, pii=i-1; 
        if(i==1) pii=0;
        mint mm = m;  
        mint pm = mm.pow(n-1); 
        for(int l=0;l<130;l++){
            mint tmp = (pi-pii)*i*pm*shit.path[l]; 
            pi *= i; pii *= (i-1);
            pm /= m; 
            ans += tmp; 
        }
    }
    //ans *= 2; 
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   node a; 
   memset(a.path,0,sizeof(a.path)); 
   memset(a.p,0,sizeof(a.p)); 
   fuck[0] = a; 
   a.p[0] = 1; 
   fuck[1] = a;
   for(int i=2;i<63;i++) {
    fuck[i]= merge(fuck[i-1],fuck[i-1]); 
   }
   while(t--) solve(); 
   return 0;
}