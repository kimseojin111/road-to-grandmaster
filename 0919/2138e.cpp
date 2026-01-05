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

void solve(){
    int x; cin>>x; 
    auto print_ = [](vector<vector<int>> v){
        cout << v.size() << "\n"; 
        for(auto &w : v) {
            for(auto x : w) cout << x << " "; 
            cout << "\n"; 
        }
        return; 
    }; 
    if(x==0){
        print_({{0}}); return; 
    }
    if(x==1){
        print_({{1}}); return; 
    }
    if(x==2){
        print_({{1,-1},{1,1}}); return; 
    }
    unordered_set<int> s; 
    vector<array<int,3>> ans; 

    auto attempt = [&](int y){
        vector<int> u; 
        if(gcd(x,y)>1) return false; 
        if(y>x||y<1) return false; 
        dbg(y)
        u.pb(x); u.pb(y); 
        while(1){
            if(u.size()>50) break; 
            int sz = u.size();
            int b = u[sz-2], bb = u[sz-1]; 
            if(b==2&&bb==1) break;  
            u.pb(abs(b-bb)); 
        }
        dbg(y,u)
        if(u.size()>50) return false; 
        reverse(all(u)); 
        for(int i=0;i<u.size();i++){
            if(i==0) ans.pb({1,0,0}); 
            else if(i==1) ans.pb({-1,1,1}); 
            else {
                if(u[i]==u[i-1]+u[i-2]) ans.pb({-1,1,1}); 
                else {
                    assert(u[i]==u[i-1]-u[i-2]); ans.pb({1,1,1}); 
                }
            }
        }
        return true;  
    }; 

    double g = (sqrt(5)-1)/2; 
    int m = int(g*x); 
    dbg(m)
    int pv = 0; 
    while(1){
        int y = m+pv; 
        if(attempt(y)){
            vector<vector<int>> d(ans.size(),vector<int>(ans.size(),0)); 
            for(int i=0;i<ans.size();i++){
                auto [a,b,c] = ans[i]; 
                if(i==0) d[0][0] = 1; 
                else {
                    d[i-1][i] = a; d[i][i-1]=b; d[i][i] = c; 
                }
            }
            print_(d); return; 
        }
        y = m-pv; 
        if(attempt(y)){
            vector<vector<int>> d(ans.size(),vector<int>(ans.size(),0)); 
            for(int i=0;i<ans.size();i++){
                auto [a,b,c] = ans[i]; 
                if(i==0) d[0][0] = 1; 
                else {
                    d[i-1][i] = a; d[i][i-1]=b; d[i][i] = c; 
                }
            }
            print_(d); return; 
        }
        pv++; 
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