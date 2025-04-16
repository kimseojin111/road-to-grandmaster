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

#define int ll 
const int N = 1001000;

int a[N],b[N]; 
ll v[N]; 

struct fuck{
    ll sum[N],cnt[N]; 
    ll ans;
    fuck() {
        memset(sum,0,sizeof(sum)); memset(cnt,0,sizeof(cnt)); 
        ans = 0; 
    } 
    void upd(int x){
        int xx = x; 
        while(xx<N){
            sum[xx] += x; 
            cnt[xx] ++; 
            xx += xx&-xx; 
        }
    }
    ll qrysum(int x){
        // x 이하 합 
        ll re = 0; 
        while(x){
            re += sum[x]; x-=x&-x; 
        }   
        return re; 
    }
    ll qrycnt(int x){
        int re = 0; 
        while(x){
            re += cnt[x]; x-=x&-x; 
        }
        return re; 
    }
    ll qrycnt(int l, int r){
        return qrycnt(r) - qrycnt(l-1); 
    }
    ll ins(int x, bool flag){
        ll p = qrysum(x) + qrycnt(x+1,N-1)*x; 
        if(flag) p+=x;  
        //dbg(x,qrysum(x))
        ans += p; 
        upd(x); 
        return ans; 
    }
}; 

fuck C,D; 
void solve(){
    dbg(1)
    int n; cin>>n;  
    rrep(i,n) cin>>a[i]; 
    rrep(i,n) cin>>b[i]; 
    rrep(i,n) cin>>v[i]; 
    vector<ll> c,d,tmp; 
    rrep(i,n) if(a[i]==1&&b[i]==0) c.pb(v[i]); 
    rrep(i,n) if(a[i]==0&&b[i]==1) d.pb(v[i]); 
    rrep(i,n) if(a[i]==1&&b[i]==1) tmp.pb(v[i]); 
    ll sum = accumulate(all(tmp),0LL); 
    dbg(c,d,tmp)
    for(auto x : c) C.ins(x,0); 
    for(auto x : d) D.ins(x,1); 
    ll ans = C.ans + D.ans + sum*(c.size()+d.size()); 
    dbg(C.ans,D.ans)
    sort(all(tmp),[](auto p, auto q){
        return p>q; 
    }); 
    dbg(tmp)
    int sz = c.size() + d.size(); 
    dbg(ans)
    for(ll x : tmp){
        sz+=2; 
        sum -= x; 
        C.ins(x,0); D.ins(x,1); 
        ll tt = C.ans + D.ans + sum*(sz); 
        ans = min(ans,tt); 
        dbg(ans)
    }
    cout << ans << "\n"; 
}   

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   solve(); 
   return 0;
}