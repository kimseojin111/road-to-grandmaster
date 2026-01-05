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

const int N = 200010; 
int a[N]; 
int ra[N]; 
int dpL[N],dpR[N]; 


void solve(){
    int n; cin>>n;  
    rrep(i,n){
        cin>>a[i]; 
        ra[a[i]] = i;
        dpL[i] = 1, dpR[i] = n;  
    }
    set<int> cur; 
    set<int> le,re; 

    auto get_prev = [&](set<int>&s, int x){
        auto it = s.lower_bound(x); 
        if(it==s.begin()) return -1; 
        return *(prev(it)); 
    }; 
    auto get_next = [&](set<int>&s, int x){
        auto it = s.upper_bound(x);
        if(it==s.end()) return n+100; 
        return *it; 
    };
    rrep(i,n){
        int now = ra[i]; 
        int fuck = get_prev(le,now); 
        if(fuck!=-1){
            if(get_next(cur,fuck)>now){
                int gg = get_prev(le,fuck); 
                dpL[now] = max(dpL[now],gg+1); 
            }
            else dpL[now] = max(dpL[now],fuck+1); 
        }
        fuck = get_next(re,now); 
        if(fuck<=n){
            if(get_prev(cur,fuck)<now){
                int gg = get_next(re,fuck); 
                dpR[now] = min(dpR[now],gg-1); 
            }
            else dpR[now] = min(dpR[now],fuck-1); 
        }

        cur.insert(now); 
        auto t = cur.lower_bound(now); 
        int chk = -1; if(t!=cur.begin()) chk = *(prev(t)); 
        if(le.count(chk)) le.erase(chk); 
        auto p = cur.upper_bound(now); if(p!=cur.end()) le.insert(now); 
        chk = -1; auto tt = cur.upper_bound(now); 
        if(tt!=cur.end()) chk = *tt; 
        if(re.count(chk)) re.erase(chk); 
        auto q = cur.lower_bound(now); if(q!=cur.begin()) re.insert(now); 
    }

    rrep(i,n){
        a[i] = n+1-a[i]; 
        ra[a[i]] = i;
    }
    cur.clear(); le.clear(); re.clear(); 
    rrep(i,n){
        int now = ra[i]; 
        int fuck = get_prev(le,now); 
        if(fuck!=-1){
            if(get_next(cur,fuck)>now){
                int gg = get_prev(le,fuck); 
                dpL[now] = max(dpL[now],gg+1); 
            }
            else dpL[now] = max(dpL[now],fuck+1); 
        }
        fuck = get_next(re,now); 
        if(fuck<=n){
            if(get_prev(cur,fuck)<now){
                int gg = get_next(re,fuck); 
                dpR[now] = min(dpR[now],gg-1); 
            }
            else dpR[now] = min(dpR[now],fuck-1); 
        }

        cur.insert(now); 
        auto t = cur.lower_bound(now); 
        int chk = -1; if(t!=cur.begin()) chk = *(prev(t)); 
        if(le.count(chk)) le.erase(chk); 
        auto p = cur.upper_bound(now); if(p!=cur.end()) le.insert(now); 
        chk = -1; auto tt = cur.upper_bound(now); 
        if(tt!=cur.end()) chk = *tt; 
        if(re.count(chk)) re.erase(chk); 
        auto q = cur.lower_bound(now); if(q!=cur.begin()) re.insert(now); 
    }
    rrep(i,n){
        dbg(i,dpL[i],dpR[i]); 
    }
    vector<pair<int,int>> v; 
    rrep(i,n) v.pb({dpL[i],dpR[i]}); 
    sort(all(v)); 
    ll ans = 0;
    int mx = 0; int pv = 0;   
    rrep(i,n){
        while(pv<v.size()&&v[pv].ff<=i){
            mx =max(mx,v[pv].ss); pv++; 
        }
        ans += (mx-i+1); 
    }
    cout << ans << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}