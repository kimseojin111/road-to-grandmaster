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

const int N = 200010; 
int a[N],vis[N],ind[N],state[N]; 
// -1 not decided 0 parent       1 child 
void solve(){
    int n; cin>>n; 
    rrep(i,n) {
        cin>>a[i]; state[i] = -1; ind[a[i]]++; 
    }
    queue<int> q; 
    rrep(i,n) if(ind[i]==0) q.push(i); 
    while(!q.empty()){
        int f = q.front(); q.pop(); 
        vis[f] = 1; 
        if(state[f]==-1){
            state[f] = 1; state[a[f]] = 0; 
        }
        dbg(f,state[f])
        ind[a[f]]--; if(ind[a[f]]==0) q.push(a[f]); 
    }
    rrep(i,n) if(!vis[i]){
        vector<int> cyc; 
        int j = i; 
        bool flag = false; 
        do{
            cyc.pb(j);
            vis[j] = 1;
            dbg(j,state[j])  
            if(state[j]==0) flag = true; 
            j = a[j]; 
        } while(j!=i); 
        dbg(flag)
        if(flag){
            int t = 0; while(state[cyc[t]]!=0) t++; 
            rotate(cyc.begin(),cyc.begin()+t,cyc.end()); 
            int s = cyc.size(); cyc.pb(cyc[0]); 
            for(int i=0;i<s;){
                int j = i; 
                if(state[cyc[i]]==0){
                    i++; continue; 
                } 
                while(state[cyc[j]]==-1)j++; 
                for(int k=i;k<j;k++){
                    if(k%2==i%2) state[cyc[k]]=1; 
                    else state[cyc[k]]=0;
                }
                i=j; 
            }
        }
        else{
            if(cyc.size()%2) {
                cout << -1 << "\n"; return; 
            }
            for(int i=0;i<cyc.size();i++){
                dbg(cyc[i],i&1)
                state[cyc[i]] = i&1; 
            }
        }
    }
    int s = accumulate(state+1,state+n+1,0); 
    cout << s << "\n"; 
    rrep(i,n) if(state[i]) cout << a[i] << " ";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}