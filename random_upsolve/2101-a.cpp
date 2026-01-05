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
int b[1010][1020]; 

void solve(){
    int n; cin>>n; 
    int x = 500, y = 500;
    vector<int> p, q;  
    b[x][y] = 0; 
    p.pb(x); q.pb(y); 
    int pv = 0; 
    for(int i=2;i<=n;i++){
        if((i%2)==0){
            y++; 
            for(int j=0;j<=i-1;j++){
                b[x][y] = ++pv; p.pb(x); q.pb(y); 
                x++; 
            }
            x--; 
            for(int j=0;j<i-1;j++){
                y--; b[x][y] = ++pv; p.pb(x); q.pb(y); 
            }
        }
        else {
            y--; 
            for(int j=0;j<i;j++) {
                b[x][y] = ++pv; p.pb(x); q.pb(y); x--; 
            }
            x++; 
            for(int j=0;j<i-1;j++){
                y++; b[x][y] = ++pv; p.pb(x); q.pb(y); 
            }
        }
    }
    int mx = *min_element(all(p)), Mx = *max_element(all(p)); 
    int my = *min_element(all(q)), My = *max_element(all(q)); 
    for(int i=mx;i<=Mx;i++) for(int j=my;j<=My;j++) cout << b[i][j] << " \n"[j==My]; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}