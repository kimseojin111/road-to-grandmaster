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

const int N = 10100; 
ll a[N]; 
ll p[N]; 
ll l[N],r[N]; 

void init(int n){
    rrep(i,n) l[i]=r[i]=0;
}

int LB(ll x){
    if(x==0) return -1; 
    else return 63-__builtin_clzll(x); 
}

const ll ff = (1LL<<63)-1; 

void solve(){
    int n; cin>>n; 
    init(n); 
    rrep(i,n) cin>>a[i]; 
    rrep(i,n) {
        p[i] = p[i-1]^a[i]; 
    }    
    if(n==1){
        cout << 1 << "\n"; return; 
    }
    int d = n-2; 
    ll xo = p[n]; 
    // 제일 큰 비트 
    ll lb = LB(xo); 
    //dbg(xo,lb)
    if(lb==-1){
        l[1] = ff; r[n] = ff; 
    }
    else {
        l[1] = r[n] = (1LL<<lb); 
    }
    for(d=n-2;d>=0;d--){
        for(int i=1;i+d<=n;i++){
            int j = i+d; 
            ll xo = p[j]^p[i-1]; 
            int op = 0; 
            // 얘가 l[i] 을 갖거나 r[j]를 가지면? 
            if((xo&l[i])||(xo&r[j])||(xo==0&&l[i]==ff)||(xo==0&&r[j]==ff)){
                op=1; 
                int lb = LB(xo); 
                if(lb==-1) l[i] = ff, r[j] = ff; 
                else l[i] |= (1LL<<lb), r[j] |= (1LL<<lb); 
            }
            if(i==j) cout << op; 
        }
    }
    cout << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}