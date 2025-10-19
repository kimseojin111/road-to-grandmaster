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

const int N = 1000100; 
int a[N]; 
vector<int> pos[N]; 

int op(int a, int b){
    return max(a,b); 
}

int e() {
    return 0; 
}

#include <atcoder/segtree>
using namespace atcoder; 

int fen[N]; 

void upd(int x, int v){
    while(x<N){
        fen[x]+=v; x+=x&-x;  
    }
}

int qry(int x){
    int re = 0;
    while(x){
        re += fen[x]; x-=x&-x; 
    } 
    return re; 
}

int qry(int l, int r){
    return qry(r) - qry(l-1); 
}

int ans[N]; 

void solve(){
    int n,q; cin>>n>>q; 
    segtree<int,op,e> seg(n+1); 
    rrep(i,n){
        cin>>a[i]; pos[a[i]].pb(i); upd(a[i],1); 
        //seg.set(i,a[i]); 
    }
    // a[i] 마다 업데이트 내용 정리 
    vector<pair<int,int>> to_erase; 
    for(int i=1;i<=n;i++){
        for(int j=0;j+1<pos[i].size();j++){
            int l = pos[i][j], r = pos[i][j+1]; 
            int M = seg.prod(l+1,r); 
            if(M==0){
                upd(i,-1); 
            }
            else to_erase.pb({M+1,i}); 
        }
        for(int j=0;j<pos[i].size();j++) seg.set(pos[i][j],i); 
    }
    vector<array<int,3>> query; 
    rep(i,q){
        int l,r; cin>>l>>r; query.pb({l,r,i}); 
    }
    sort(all(query)); 
    sort(all(to_erase));
    int pv = 0; 
    for(auto [l,r,idx] : query){
        while(pv<to_erase.size()&&to_erase[pv].first<=l){
            auto [fu,ck] = to_erase[pv]; 
            upd(ck,-1); pv++; 
        }
        ans[idx] = qry(l,r); 
    }
    rep(i,q) cout << ans[i] << "\n";
}   

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}