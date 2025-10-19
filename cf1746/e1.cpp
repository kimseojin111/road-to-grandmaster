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

const int N = (1<<17);
int ans[N];  

void solve(){
    int n; cin>>n; 
    // 0~16 
    auto qry = [&](int msk, int b){
        vector<int> v; 
        rrep(i,n){
            if((i&msk)==b){
                v.pb(i); 
            }
        }
        cout << "? "; 
        cout << v.size() << " "; 
        for(auto x : v) cout << x << " "; 
        cout << endl; 
        string s; cin>>s; 
        if(s=="YES") return 1; 
        return 0;  
    }; 
    auto hol = [&](int x){
        cout << '!' << " " << x << endl; 
        string s; cin>>s; 
        if(s==":)") return true; 
        return false;  
    }; 
    //for(int i=0;i<N;i++) ans[i] = -1; 
    set<int> msk;
    set<int> done;  
    int re = 0; 
    //for(int i=0;i<=16;i++) msk.insert((1<<i)); 
    for(int i=0;i<=2;i++) msk.insert((1<<i)); 
    while(msk.size()>1){
        int M = 0, Mans = 0; 
        while(!msk.empty()){
            int m = *msk.begin(); 
            int u = qry(m,ans[m]); 
            int v = qry(m,ans[m]); 
            if(u==v){
                if(u==1) {
                    re |= ans[m]; 
                } else {
                    re |= (m-ans[m]); 
                }
                msk.erase(m); 
                break; 
            }
            if(u==1){
                M |= m; 
                Mans |= ans[m]; 
            }
            else {
                M |= m; 
                Mans |= (m-ans[m]); 
            }
            msk.erase(m); 
        }
        if(M!=0){
            ans[M] = Mans; 
            msk.insert(M); 
        }
    }
    int m = *msk.begin(); 
    if(hol(re+ans[m])) return; 
    hol(re+m-ans[m]); 
    return;
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}