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

ll nd[40]; 

void solve(){
    int n,q; cin>>n>>q; 
    vector<int> aa(n); 
    rep(i,n) cin>>aa[i]; 
    sort(all(aa)); 
    reverse(all(aa)); 
    unordered_map<int,ll> dd; 
    rep(i,q){
        int x; cin>>x;
        if(x==0){
            cout << 0 << "\n"; continue;
        }
        if(dd.find(x)!=dd.end()) {
            cout << dd[x] << "\n"; continue; 
        }
        int xx = x; 
        if(aa[0]>=x){
            cout << 0 << "\n"; continue; 
        }
        if(n==1){
            cout << x-aa[0] << "\n"; continue; 
        }
        priority_queue<int> pq; 
        int pc = __builtin_popcount(x); 
        rep(i,min(n,pc)) pq.push(aa[i]); 
        int ans = 0;
        for(int k=30;k>=0;k--) if((x>>k)&1){
            if(pq.top()>x) break; 
            int p = pq.top(); pq.pop(); 
            int q = pq.top(); pq.pop(); 
            if(q>=(1<<k)){
                break; 
            }
            if(p>=x) break; 
            if(p<(1<<k)){
                ans += (1<<k) - p; 
                pq.push(q); 
                pq.push(0); 
                x -= (1<<k); 
                continue; 
            } else {
                pq.push(q); 
                p -= (1<<k); 
                x -= (1<<k); 
                pq.push(p); 
                continue; 
            }
        }
        dd[xx] = ans; 
        cout << ans << "\n";
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