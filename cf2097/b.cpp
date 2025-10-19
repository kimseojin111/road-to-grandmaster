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
using mint = modint1000000007; 

const int N = 2000101; 
int x[N], y[N]; 

vector<int> adj[N]; 
vector<int> radj[N]; 

bool vis[N]; 
int deg[N]; 
int match[N]; 
void add(int i, int j){
    adj[i].pb(j); 
    radj[j].pb(i); 
    deg[i]++; 
}

void er(int i, int j){
    adj[i].erase(find(all(adj[i]),j)); 
    radj[j].erase(find(all(radj[j]),i)); 
}


void solve(){
    int n,m,k; cin>>n>>m>>k; 

    auto ext = [&](){
        vector<int> fuck; 
        for(int i=2;i<=k*2;i+=2){
            for(auto x : adj[i]) fuck.pb(x); 
            adj[i].clear(); 
            vis[i] = 0; 
            deg[i] = 0; 
        }
        for(auto x : fuck) radj[x].clear(); 
    };


    for(int i=1;i<=2*k+1;i+=2) {
        cin >> x[i] >> y[i]; 
    }
    for(int i=3;i<=2*k+1;i+=2){
        int d = abs(x[i]-x[i-2]) + abs(y[i]-y[i-2]); 
        if(d!=2) {
            cout << 0 << "\n"; ext(); return; 
        }
        if(abs(x[i]-x[i-2])==2 || abs(y[i]-y[i-2])==2){
            int mx = (x[i]+x[i-2])/2, my = (y[i]+y[i-2])/2; 
            int mm = mx*m+my; 
            add(i-1,mm); 
        }
        else {
            int mm = x[i]*m + y[i-2]; 
            add(i-1,mm); 
            mm = x[i-2]*m + y[i]; 
            add(i-1,mm); 
        }
    }
    mint ans = 1; 
    for(int i=2;i<=k*2;i+=2){
        if(!vis[i]){
            vector<int> shit; 
            queue<int> q; 
            q.push(i); 
            while(!q.empty()){
                int f= q.front(); q.pop();
                if(vis[f]) continue; 
                vis[f] = 1; 
                shit.pb(f); 
                for(auto x : adj[f]) for(auto y : radj[x]) if(!vis[y]) q.push(y); 
            }
            set<int> ff; 
            for(auto x : shit) for(auto y : adj[x]) ff.insert(y); 
            int degg = 0; 
            for(auto x : shit) degg += adj[x].size(); 
            if(ff.size()<shit.size()) {
                cout << 0 << "\n"; ext(); return; 
            }
            if(ff.size()==shit.size()){
                if(degg==2*shit.size()) ans *= 2; 
            }
            else {
                ans *= (shit.size()+1); 
            }
        }
    }
    cout << ans.val() << "\n";
    ext(); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}