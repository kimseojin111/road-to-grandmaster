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

void solve(){
    int a,b,c,d,m; 
    cin>>a>>b>>c>>d>>m; 
    vector<array<int,5>> v; 
    map<array<int,3>,array<int,2>> M; 
    for(int k=0;k<30;k++){
        int aa = (a>>k)&1, bb = (b>>k)&1, cc = (c>>k)&1, dd=(d>>k)&1, mm = (m>>k)&1; 
        if(M.find({aa,bb,mm})==M.end()){
            v.pb({aa,bb,mm,cc,dd}); 
            M[{aa,bb,mm}] = {cc,dd}; 
            continue; 
        }
        auto [p,q] = M[{aa,bb,mm}]; 
        if(p!=cc || q!=dd){
            cout << -1 << "\n"; return; 
        }
        // if(M[{aa,bb,mm}]!={cc,dd}){
        //     cout << -1 << "\n"; return; 
        // }
    }
    a=b=c=d=m=0; int bi = 0;  
    for(auto [aa,bb,mm,cc,dd]:v){
        a |= (aa<<bi); 
        b |= (bb<<bi); 
        c |= (cc<<bi); 
        d |= (dd<<bi); 
        m |= (mm<<bi); 
        bi++; 
    }
    #define CAST(X) std::bitset<sizeof(X)*8>
#define ACCESS(X) *((std::bitset<sizeof(X)*8>*)&X)
    unordered_map<CAST(pair<int,int>),bool> vis; 
    unordered_map<CAST(pair<int,int>),int> dis; 
    //priority_queue<array<int,3>,vector<array<int,3>>,greater<>> pq; // dis, a, b 

    queue<array<int,3>> q; 
    auto chk = [&](pair<int,int> x, int dnow){
        dbg(x,dnow)
        if(vis[x]) return; 
        q.push({x.first,x.second,dnow+1}); 
    }; 
    q.push({a,b,0}); 
    while(!q.empty()){
        auto [a,b,d] = q.front(); q.pop(); 
        if(vis[{a,b}]) continue; 
        dis[ACCESS({a,b})] = d; 
        vis[{a,b}] = 1; 
        chk({a&b,b},d); 
        chk({a|b,b},d); 
        chk({a,a^b},d); 
        chk({a,b^m},d); 
    }
    if(!vis[{c,d}]) {
        cout << -1 << "\n"; 
    }
    else cout << dis[{c,d}] << "\n"; 


    // dis[{a,b}] = 0; 
    // auto chk = [&](pair<int,int> x, int dnow){
    //     dbg(x,dnow)
    //     if(vis[x]) return; 
    //     if(dis.find(x)==dis.end() || dis[x]>dnow+1){
    //         dis[x] = dnow+1; 
    //         pq.push({dnow+1,x.first,x.second}); 
    //     }
    // }; 
    // pq.push({0,a,b}); 
    // while(!pq.empty()){
    //     auto [di,a,b] = pq.top(); pq.pop(); 
    //     dis[{a,b}] = di; 
    //     if(vis[{a,b}]) continue; 
    //     vis[{a,b}] = 1; 
    //     chk({a&b,b},di); 
    //     chk({a|b,b},di); 
    //     chk({a,a^b},di); 
    //     chk({a,b^m},di); 
    // }
    // if(vis.find({c,d})==vis.end()){
    //     cout << -1 << "\n"; 
    // }
    // else {
    //     cout << dis[{c,d}] << "\n";
    // }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}