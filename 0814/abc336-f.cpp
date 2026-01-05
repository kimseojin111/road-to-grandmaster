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
    int h,w; cin>>h>>w; 
    using board = vector<vector<int>>; 
    auto trans = [&](board b, int op){
      //  dbg(b,op)
        int x = op&1; int y = (op>>1)&1; 
        for(int i=0;i<=h-1;i++) {
            for(int j=0;j<=w-1;j++){

                int ii = h-2-i+x*2, jj = w-2-j+y*2; 
                if(ii<0||ii>=h||jj<0||jj>=w) continue; 
                if(make_pair(i,j)>make_pair(ii,jj)) swap(b[i][j],b[ii][jj]); 
            }
        }
        //dbg(b)
        return b; 
    }; 
    board s(h,vector<int>(w,0)); 
    board e(h,vector<int>(w,0)); 
    rep(i,h) rep(j,w) cin>>s[i][j]; 
    rep(i,h) rep(j,w) {
        e[i][j] = w*i+j+1; 
    }
    struct fuck {
        board b; int cnt; int op; 
    }; 
    vector<fuck> l; vector<fuck> r; 
    queue<fuck> q; 
    q.push({s,0,-1}); 
    while(!q.empty()){
        auto [b,cnt,op] = q.front(); q.pop(); 
        l.pb({b,cnt,op}); 
        if(cnt==10) continue;  
        rep(k,4) if(k!=op){
            auto bb = trans(b,k); 
            q.push({bb,cnt+1,k}); 
        }
    }
    while(!q.empty()) q.pop(); 
    q.push({e,0,-1}); 
    while(!q.empty()){
        auto [b,cnt,op] = q.front(); q.pop(); 
       //q dbg(b,cnt,op)
        r.pb({b,cnt,op}); 
        if(cnt==10) continue;  
        rep(k,4) if(k!=op){
            auto bb = trans(b,k); 
            q.push({bb,cnt+1,k}); 
        }
    }
    auto cmp = [](const fuck& l, const fuck& r){
        if(l.b!=r.b) return l.b<r.b; 
        return l.cnt<r.cnt; 
    }; 
    sort(all(l),cmp); sort(all(r),cmp); 
    int ans = 40; 
    // for(auto [b,cnt,op]:l){
    //     dbg("l",b,cnt)
    // }
    // for(auto [b,cnt,op]:r){
    //     dbg("r",b,cnt)
    // }
    for(int lv=0,rv=0;lv<l.size();lv++){
        while(rv<r.size()&&l[lv].b>r[rv].b) rv++; 
        if(rv<r.size()&&l[lv].b==r[rv].b){
            
            ans = min(ans,l[lv].cnt+r[rv].cnt); 
        }
    }
    cout << (ans==40 ? -1 : ans) << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}