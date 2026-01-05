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
vector<int> adj[N]; 
int deg[N],par[N]; 

void init(int n){
    rrep(i,n){
        adj[i].clear(); deg[i]=par[i]=0; 
    }
}

void solve(){
    int n,m; cin>>n>>m; init(n); 
    while(m--){
        int a,b;cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
        deg[a]++; deg[b]++; 
    }

    auto ans = [&](int p,int a, int b){
        int cc = 0; 
        vector<pair<int,int>> e; 
        // for(auto x : adj[p]) {
        //     if(cc<2&&x!=a&&x!=b) {
        //         e.pb({x,p}); cc++; 
        //     } 
        // }
        // e.pb({p,a}); e.pb({p,b}); 
        rrep(i,n) par[i] = 0; 
        queue<int> q; q.push(a); 
        par[a] = a; 
        while(!q.empty()) {
            int f = q.front(); q.pop(); 
            for(auto ne : adj[f]) if(ne!=p&&par[ne]==0) {
                par[ne] = f; q.push(ne); 
            }
        }
        int nt = b; 
        vector<int> path; 
        set<int> s; 
        while(nt!=a){
            path.pb(nt); 
            s.insert(nt); 
            nt = par[nt]; 
        }
        path.pb(a); 
        s.insert(a); 
        vector<int> fff; 
        for(auto x : adj[p]) if(x!=a&&x!=b) fff.pb(x); 
        int c = fff[0], d = fff[1]; 
        auto pa = find(all(path),a), pb=find(all(path),b), pc = find(all(path),c), pd = find(all(path),d); 
        auto px = min({pa,pc,pd}); 
        e.pb({p,a}); e.pb({p,b}); e.pb({p,c}); e.pb({p,d}); 
        for(auto it = path.begin(); it!=px; it++){
            e.pb({*it,*next(it)}); 
        }

        // e.pb({nt,a}); 
        cout << e.size() << "\n";
        for(auto [p,q]:e) cout << p << " " << q << "\n";
    }; 

    rrep(i,n) if(deg[i]>=4){
        rrep(j,n) par[j] = 0; 
        for(auto x : adj[i]) {
            if(par[x]==0){
                par[x] = x; 
                queue<int> q; q.push(x); 
                while(!q.empty()){
                    int f = q.front(); q.pop(); 
                    for(auto ne : adj[f]) if(ne!=i&&par[ne]==0){
                        q.push(ne); par[ne] = x; 
                    } 
                }
            }
            else {
                int y = par[x]; 
                cout << "YES\n"; 
                ans(i,x,y); return; 
            }
        }
    }
    cout << "NO\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}