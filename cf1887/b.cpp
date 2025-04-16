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

const int N = 500010;
ll a[N]; 
ll l[N],r[N]; 
ll col[N]; 

ll shit[N]; 

void solve(){
    int n; cin>>n; 
    rrep(i,n) cin>>a[i]; 

    set<pair<ll,ll>> diff; // idx dif 
    int ans = 0; 
    int q; cin>>q; 
    const ll inf = 2e18; 
    rrep(i,q){
        cin>>l[q]>>r[q]; 
        ll x; cin>>x; 
        col[q] = x;
        if(x==0) continue;  
        // diff [l[q]] -= x diff[r[q]+1] += x; 
        auto it = diff.lower_bound({l[q],-inf}); 
        if(it==diff.end()||(*it).first!=l[q]){
            diff.insert({l[q],x}); 
        }
        else {
            auto [lq,dd] = *it; 
            diff.erase(it); 
            dd+=x; 
            dbg(dd)
            if(dd!=0)diff.insert({l[q],dd}); 
        }
        it = diff.lower_bound({r[q]+1,-inf}); 
        if(it==diff.end()||(*it).first!=r[q]+1){
            diff.insert({r[q]+1,-x}); 
        }
        else {
            auto [rq,dd] = *it; 
            diff.erase(it); 
            dd-=x; 
            if(dd!=0)diff.insert({r[q]+1,dd}); 
        }
        if(diff.empty()) continue; 
        else if((*diff.begin()).second<0LL){
            diff.clear(); 
            ans = i; 
            continue; 
        }
    }
    dbg(ans)
    rrep(i,n+1) shit[i]=0; 
    rrep(i,ans){
        dbg(i,col[i])
        shit[l[i]]+=col[i]; shit[r[i]+1]-=col[i]; 
    }
    for(int i=2;i<=n;i++) shit[i]+=shit[i-1]; 
    rrep(i,n) cout << (a[i]+shit[i]) << " \n"[i==n];
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}