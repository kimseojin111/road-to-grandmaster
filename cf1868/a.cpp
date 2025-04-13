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

pair<int,int> chk(int x){
    // x = 2^a - 2^b 
    if(x==0) return {0,0}; 
    {
        // 2^a>x 인 최소의 a
        bool flag = x>0; 
        int a = 0; 
        if(x<0) x=-x; 
        while((1LL<<a)<=x) a++; 
        if(x==(1LL<<a-1)){
            if(flag) return {a-1,36}; 
            else return {36,a-1}; 
        }
        int bb = (1<<a)-x; 
        // bb = 1<<b 인지 체크 
        int b = 0; 
        while((1<<b)<bb)b++; 
        if(bb==(1<<b)) {
            if(flag) return {a,b}; 
            return {b,a}; 
        }
        else return {-1,-1}; 
    }
}

int deg[50]; 
int pl[50],mi[50]; 

void solve(){
    int n; cin>>n; 
    memset(deg,0,sizeof(deg)); 
    memset(pl,0,sizeof(pl)); 
    memset(mi,0,sizeof(mi)); 
    vector<int> a(n); 
    rep(i,n) cin>>a[i]; 
    ll sum = 0; 
    rep(i,n) sum+=a[i]; 
    if(sum%n!=0){
        cout << "No\n";return; 
    }  
    int d = sum/n; 
    int in = 0; 
    for(int i=0;i<n;i++){
        if(a[i]==d) continue; 
        int dif = d-a[i]; 
        auto [p,q] = chk(dif); 
        if(p==-1&&q==-1){
            cout << "No\n";return; 
        }
        if(p==36){
            // deg[q]-- or deg[q+1]-- deg[q]++ 
            // 
            pl[q]++; 
        }
        if(q==36){
            // deg[p]++ or deg[p]-- deg[p+1]++; 
            mi[p]++; 
        }
        dbg(dif)
        deg[p]++; deg[q]--; 
    }
    for(int i=30;i>=1;i--)
    {
        dbg(i,deg[i],pl[i],mi[i])
        int d = abs(deg[i]); 
        if(deg[i]<0){
            if(mi[i-1]>=d){
                deg[i-1]-=d*2; deg[i]+=d; 
            }
            else {
                cout << "No\n"; return; 
            }
        }
        if(deg[i]>0){
            if(pl[i-1]>=d){
                deg[i-1] += 2*d; deg[i]-=d; 
            }
        }
    }
    for(int i=0;i<33;i++){
        if(deg[i]){
            cout << "No\n"; return; 
        }
    }
    cout << "Yes\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}