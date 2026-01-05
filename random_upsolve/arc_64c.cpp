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

const int N = 2010; 
double x[N],y[N],r[N]; 
double dist(int i, int j){
    double dd = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]); 
    dd = sqrt(dd); 
    return max(dd-r[i]-r[j],0.0); 
}

bool vis[N]; 
double dis[N]; 
void solve(){
    int s = 0, d = 1001; 
    cin>>x[0]>>y[0]>>x[1001]>>y[1001];
    int n; cin>>n; 
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>r[i]; 
    for(int i=0;i<=d;i++) dis[i]=1e18; 
    d = n+1; 
    x[d]=x[1001],y[d]=y[1001]; 
    dis[0] = 1; 
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<>> pq; 
    pq.push({0.0,0}); 
    while(!pq.empty()){
        auto [di,i] = pq.top(); pq.pop();
        if(vis[i]) continue; 
        vis[i] = 1; 
        for(int j=0;j<=d;j++) if(!vis[j]){
            double nj = di + dist(i,j); 
            if(nj<dis[j]){
                dis[j] = nj; pq.push({nj,j}); 
            }
        }
    }
    cout << fixed; 
    cout.precision(12); 
    cout << dis[d];
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}