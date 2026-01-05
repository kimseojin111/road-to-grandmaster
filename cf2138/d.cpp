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
#include <atcoder/modint> 
using namespace atcoder; 
using mint = modint1000000007; 

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
void __print(mint x) {cerr << (x.val());}

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
    int n,m,q; cin>>n>>m>>q; 
    mint ans = 0; 
    vector<int> a(n); 
    rep(i,n) cin>>a[i]; 
    vector<pair<int,int>> qry(q); 
    rep(i,q) {
        cin>>qry[i].ff>>qry[i].ss; qry[i].ff-=1; 
    }
    dbg(a,qry)
    // chmin x  -> 0, x 
    // chmax x -> 1, x 
    // assign x -> 2, x 
    // 
    auto lb = [&](vector<int>& v, int x){
        // x 이상인 것 개수 
        auto it = lower_bound(all(v),x); 
        return int((v.end()) - it); 
    }; 

    auto iha = [&](vector<int>&v, int x){
        // x 미만인 것 개수 
        return int(lower_bound(all(v),x) - v.begin()); 
    };
    mint fac = 1; 
    rrep(i,q) fac*=i; 
    rep(i,n){
        vector<pair<int,int>> op; 
        vector<int> op0,op1,op2; 
        rep(d,q){
            auto [j,x] = qry[d]; 
            dbg(j,x)
            if(j==i) {
                op.pb({2,x}); op2.pb(x); 
            }
            if(j<i) {
                op.pb({1,x+(i-j)}); op1.pb(x+i-j); 
            }
            if(j>i) {
                op.pb({0,x-(j-i)}); op0.pb(x+i-j); 
            }
        }
        vector<int> g; 
        for(auto [dd,x]:op) g.pb(x); 
        dbg(g)
        g.pb(a[i]); 
        sort(all(g)); 
        sort(all(op0)); sort(all(op1)); sort(all(op2)); 
        g.erase(unique(all(g)),g.end()); 
        mint good = 0; 
        auto get = [&](int k) {
            int at = lb(op1,k) + lb(op2,k); 
            int bt = iha(op0,k) + iha(op2,k); 
            if(at+bt==0) {
                if(a[i]>=k) return (mint)1;
                else return (mint)0; 
            }
            return (mint)(at)/(mint)(at+bt); 
        }; 
        vector<mint> prob(g.size()); 

        for(int i=0;i<g.size();i++){
            mint kk = get(g[i]); 
            mint gg = 0; 
            if(i<g.size()-1) gg = get(g[i+1]); 
            good += (kk-gg)*g[i]; 

        }
        cout << (good * fac).val() << " "; 
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