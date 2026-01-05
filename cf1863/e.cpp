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

const int N = 200100; 
vector<pair<int,int>> adj[N]; 
vector<pair<int,int>> radj[N]; 
int deg[N]; 
int h[N]; 
int dp[N]; 
int dpm[N]; 

void init(int n){
    rrep(i,n){
        adj[i].clear(); radj[i].clear(); deg[i] = 0; dp[i] = dpm[i] = 0; 
    }
}

void solve(){
    int n,m; ll k; cin>>n>>m>>k; 
    rrep(i,n) cin>>h[i]; 
    init(n); 
    rep(i,m){
        int a,b; cin>>a>>b; 
        if(h[a]<=h[b]) {
            adj[a].pb({b,0}); 
            radj[b].pb({a,0}); 
        }
        else {
            adj[a].pb({b,1}); 
            radj[b].pb({a,1}); 
        }
        deg[b]++; 
    }
    queue<int> q; 
    vector<int> st; 
    rrep(i,n) if(deg[i]==0){
        st.pb(i); q.push(i); 
    }
    while(!q.empty()){
        int f = q.front(); q.pop(); 
        if(radj[f].empty()){
            dpm[f] = h[f]; 
            dp[f] = 0; 
        }
        else {
            for(auto [child,dis] : radj[f]) {
                dbg(child,dis)
                dp[f] = max(dp[f],dp[child]+dis); 
            }
            dpm[f] = k; 
            for(auto [child,dis] : radj[f]) if(dp[f]==dp[child]+dis){
                dpm[f] = min(dpm[f],dpm[child]);  
            }
        }
        dbg(f,dp[f])
        for(auto [par,dis] : adj[f]){
            if(--deg[par]==0) q.push(par); 
        }
    }
    int D = *max_element(dp+1,dp+1+n); 
    vector<int> ed; 
    rrep(i,n) if(dp[i]==D || dp[i]==D-1) ed.pb(i); 
    sort(all(st),[&](auto a, auto b){
        return h[a]<h[b]; 
    }); 
    sort(all(ed),[&](auto a, auto b){
        return dpm[a]<dpm[b]; 
    });
    dbg(st,ed)
    multiset<ll> shit; 
    for(auto x : ed){
        shit.insert(k*dp[x] + h[x]); 
    }
    ll ans = 2e18; 
    for(int i=0,pv=0;i<st.size();){
        ans = min(ans,*shit.rbegin()-h[st[i]]);
        int j = i; 
        while(j<st.size()&&h[st[j]]==h[st[i]]) j++; 
        while(pv<ed.size()&&dpm[ed[pv]]==h[st[i]]){
            ll pr = k*dp[ed[pv]] + h[ed[pv]]; 
            shit.erase(shit.find(pr)); 
            shit.insert(pr+k); 
            pv++; 
        }
        i=j; 
    }
    cout << ans << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}