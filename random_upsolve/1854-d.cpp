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
    int Q =0;
    int n; cin>>n; 
    auto qry = [&](int u, int k, vector<int> s) {
        // u 시작 k 이동 벡터 s 
        cout << "? " << u << " " << k << " " << s.size() << " "; 
        for(auto x : s) cout << x << " "; 
        cout << endl; 
        Q++; 
        assert(Q<=2000);
        int x; cin>>x; return x;
    }; 
    auto ed = [](vector<int> a) {
        sort(all(a));
        cout << "! " << a.size() << " "; 
        for(auto x : a) cout << x << " "; 
        cout << endl; return; 
    }; 
    // find ancestor of cycle 
    auto get = [&](int a, int k){
        vector<int> can; 
        rrep(i,n) can.pb(i);
        while(can.size()>1){
            vector<int> l, r;
            dbg(can)
            int i = 0;  
            for(i=0;2*i<can.size();i++){
                l.pb(can[i]); 
            }
            while(i<can.size()){
                r.pb(can[i++]); 
            }
            if(qry(a,k,l)) {
                can = l; 
            }
            else can = r; 
        }   
        return can[0]; 
    };
    int st = get(1,n+100); 
    int K = 63;
    // get K in cycles 
    vector<int> cyc; 
    cyc.pb(st); 
    while(cyc.size()<K){
        int b = cyc.back(); 
        if(cyc.size()>1&&b==cyc[0]) {
            break; 
        }
        cyc.pb(get(b,1)); 
    }
    auto gogo = [&](vector<int> cyc){
        vector<int> in(n+1); 
        for(auto x : cyc) in[x] = 1; 
        rrep(i,n) if(!in[i]){
            if(qry(i,n,cyc)) cyc.pb(i); 
        }
        ed(cyc); 
    }; 
    if(cyc.back()==cyc[0]){
        cyc.pop_back(); gogo(cyc); 
        return; 
    }
    while(1){
        // cyc 
        vector<int> in(n+1); 
        for(auto x : cyc) in[x] = 1; 
        int ad = 0; 
        int dd = cyc.size(); 
        vector<int> tt; 
        rrep(i,n) if(!in[i]){
            if(qry(i,K,cyc)) {
                ad++; tt.pb(i); 
            }
        }
        for(auto x : tt) cyc.pb(x); 
        if(ad>=K) {
            K<<=1; continue;
        }
        else break;
    }
    dbg(cyc)
    gogo(cyc); 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}