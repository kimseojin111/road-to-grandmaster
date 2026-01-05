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
    int n; cin>>n; 
    if(n==4){
        cout << "4\n1 4\n3 1\n2 1\n3 1"; 
        return; 
    }
    vector<pair<int,int>> ans; 
    auto chk = [&]{
        ll cnt = 0; 
        int pv = 1e9; 
        for(auto [i,l]:ans) {
            if(i>pv) {
                cnt += l+1000; 
                //dbg('@',i,l,pv)
            }
            else cnt += l; 
            pv = i; 
        }
        dbg(cnt) 
        assert(cnt<=1000'000); 
    }; 
    auto chkk = [&]{
        unordered_set<int> s; 
        rrep(i,n) s.insert(i); 
        for(auto [i,l]:ans){
            if(s.find(i)!=s.end()){
                s.erase(i); 
                s.insert(i+l); 
            }
        }
        assert(s.size()==1&&*s.begin()==n); 
    }; 

    const int K = 63; 
    auto doit = [&](vector<int>& a, int k){
        // a -> 모두 b로 보내기 
        int d = (a.size()-1)/k; 
        vector<int> re; 
        for(int j=0;j<k-1;j++){
            for(int s=d*k;s>=0;s-=k){
                int p = s+j, q = s+j+1; 
                if(q<a.size()) ans.pb({a[p],a[q]-a[p]}); 
            }
        }
        for(int i=0;i<=d;i++) re.pb(a[min((int)a.size()-1,i*k+k-1)]);
        return re; 
    }; 
    vector<int> a; 
    rrep(i,n) a.pb(i); 
    auto b = doit(a,63); 
    auto c = doit(b,63); 
    dbg(c)
    for(int i=0;i+1<c.size();i++) ans.pb({c[i],c[i+1]-c[i]}); 
    chk(); 
    chkk(); 
    cout << ans.size() << "\n"; 
    for(auto [i,l]:ans) cout << i << " " << l << "\n";
}   

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) solve(); 
    return 0;
}