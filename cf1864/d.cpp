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

#include <atcoder/modint> 
using namespace atcoder; 

using mint = modint998244353; 

struct trie{
    vector<int> cnt; 
    vector<int> pcnt; 
    vector<int> l,r; 
    int pv; 
    trie(int n) {
        int N = n*40;
        pv = 0;  
        cnt.resize(N); 
        pcnt.resize(N); 
        l.resize(N,-1); r.resize(N,-1); 
    }
    void ins(int x){
        int now = 0; 
        for(int k=29;k>=0;k--){
            //dbg(x,now)
            int kk = (x>>k)&1; 
            cnt[now]++; 
            if(kk){
                if(r[now]==-1) r[now] = ++pv; 
                pcnt[r[now]] = pcnt[now] + 1; 
                now = r[now];  
            }
            else {
                if(l[now]==-1) l[now] = ++pv; 
                pcnt[l[now]] = pcnt[now]; 
                now = l[now]; 
            }
        }
        cnt[now]++;
    }
    mint dfs(int x){
        if(l[x]==-1&&r[x]==-1){
            mint ans = 1; 
            dbg(cnt[x],pcnt[x])
            ans = ans*cnt[x]*cnt[x]*(pcnt[x]+1); 
            return ans; 
        }
        if(l[x]!=-1&&r[x]!=-1){
            mint ans = 1; 
            ans = ans*cnt[l[x]]*cnt[r[x]]*(pcnt[x]*2+3); 
            ans = ans + dfs(l[x]) + dfs(r[x]); 
            return ans; 
        }
        else {
            if(l[x]!=-1) return dfs(l[x]); 
            else return dfs(r[x]); 
        }
    }
}; 

void solve(){
    int n; cin>>n; 
    trie t(n); 
    rep(i,n){
        int a; cin>>a; t.ins(a); 
    }
    mint ans = t.dfs(0); 
    dbg(ans.val())
    //ans = (mint)332748120*9;
    //dbg(ans.val())
    ans = (ans/n)/n; 
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}