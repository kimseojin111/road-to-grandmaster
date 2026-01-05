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

// long long inv(long long a, long long b){
//     return 1<a ? b - inv(b%a,a)*b/a : 1;
// }

const int N = 5010; 
mint fac[N]; 
mint inv[N]; 

void solve(){
    // max(x) or min(x) or assign x 
    // 마지막에 x 일 확률 -> 마지막이 assign x 이거나 직전에 <x 이고 max(x) 가 일어남 
    int n,m,Q; cin>>n>>m>>Q; 
    vector<int> a(n); 
    rep(i,n) {
        cin>>a[i]; a[i]-=i; 
    }
    vector<pair<int,int>> qry; 
    rep(dd,Q){
        int i,x; cin>>i>>x; i--; 
        x-=i; 
        qry.pb({i,x}); 
    }
    //mint ans = 0; 
    dbg(qry)
    rep(i,n){
        // chmin 0    assign 1   chmax 2
        mint ans = 0; 
        ans += fac[Q]*i; 
        dbg(ans)
        // <val, idx>, op
        vector<pair<pair<int,int>,int>> v; 
        int pv = 0; 
        for(auto [j,x]:qry){
            if(j<i) v.pb({{x,pv},2}); 
            else if(j==i) v.pb({{x,pv},1}); 
            else v.pb({{x,pv},0}); 
            pv++; 
        }
        sort(all(v)); 
        vector<int> p_min(Q); 
        vector<int> s_max(Q); 
        for(int i=0;i<Q;i++){
            p_min[i] = (i==0? 0:p_min[i-1]) + (i>0 ? v[i-1].ss==0 || v[i-1].ss==1: 0); 
        }
        for(int i=Q-1;i>=0;i--){
            s_max[i] = (i==Q-1?0:s_max[i+1]) + (i<Q-1 ? v[i+1].ss==2 || v[i+1].ss==1 : 0); 
            //dbg(i,s_max[i])
        }
        bool flag = true; 
        //int u = 0; 
        dbg(v)
        rep(u,Q){
            auto asdf = v[u]; 
            auto [val,idx] = asdf.ff; 
            int op = asdf.ss; 
            int p = p_min[u], q = s_max[u];
            if(op==2){
                // max 
                dbg(val,a[i])
                if(p+q==0){
                    if(val>a[i]) {
                        flag = false; 
                        ans += val*fac[Q]; continue; 
                    }
                    else continue; 
                } else {
                    if(p==0){
                        if(a[i]>val) continue; 
                    }
                    mint prob = (mint)p*inv[p+q]*inv[p+q+1]; 
                    ans += val*fac[Q]*prob; flag = false; continue; 
                }
            }
            if(op==1){
                if(p+q==0) {
                    flag = false; ans += val*fac[Q]; continue; 
                } 
                mint prob = inv[p+q+1]; 
                ans += val*fac[Q]*prob; 
                flag = false; continue;
            }
            if(op==0){
                if(p+q==0){
                    // chmin 
                    if(val<a[i]){
                        flag = false; 
                        ans += val*fac[Q]; 
                        continue; 
                    } else continue; 
                } 
                else {
                    // mint prob = (mint)q/(p+q)/(p+q+1); 
                    if(q==0){
                        if(a[i]<val) continue; 
                    }
                    flag = false; 
                    mint prob = (mint)q*inv[p+q]*inv[p+q+1]; 
                    ans += val*fac[Q]*prob; flag = false; continue; 
                }
            }
        }
        if(flag) ans += a[i]*fac[Q]; 
        cout << ans.val() << " "; 
    }
    cout << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   fac[0] =1 ; 
   for(int i=1;i<N;i++) fac[i] = i*fac[i-1]; 
   for(int i=1;i<N;i++) inv[i] = (mint)1/i; 
   while(t--) solve(); 
   return 0;
}