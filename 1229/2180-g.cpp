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
    int q; cin>>q; 
    vector<pair<int,int>> st; 
    mint n=0; 
    mint sum=0; 
    ll mod = 1000000006; 
    ll pn=0; // mod 1000000006; 
    while(q--){
        int x; 
        int op; cin>>op; 
        dbg(op)
        if(op==2){
            cin>>x; 
            // add x 
            if(pn%2==0){
                st.pb({x,1}); 
            } else st.pb({x,3}); 
            sum += (n+1)*x; 
            n = n*2+1; 
            pn = (pn*2+1)%mod; 
        } 
        if(op==1){
            int dd = -1; 
            for(int i=st.size()-1;i>=0;i--){
                auto& [x,ii] = st[i]; 
                dbg(st)
                if(ii==0||ii==1){
                    sum -= x; 
                    ii = (ii+1)%4; break; 
                } else {
                    ii = (ii+1)%4; 
                }
            }
            n -= 1; 
            pn = (pn-1+mod)%mod; 
        }
        if(op==3){
            dbg(n,pn,sum)
            mint pw = mint(2).pow(pn); 
            mint tmp = pw/4 + (pw-1)/n/2; 
            cout << (tmp*sum).val() << "\n";
        }
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