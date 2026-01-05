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

const int N = 300000;
int cnt[N]; 

int tmp[N]; 

void solve(){
    ll n,m,q; cin>>n>>m>>q; 
    unordered_set<int> in; 

    auto add = [&](int a){
        cnt[a]++; in.insert(a); 
        if(cnt[a]==m){
            int s = a; 
            while(cnt[s]==m){
                cnt[s] = 0; in.erase(s); 
                cnt[s+1]++; s++; in.insert(s); 
            }
        }
    }; 

    auto erase = [&](int a){
        if(cnt[a]>0){
            cnt[a]--; if(cnt[a]==0) in.erase(a); 
        }
        else {
            auto it = *in.lower_bound(a); 
            for(int j=a;j<it;j++) {
                cnt[j] = m-1; in.insert(j); 
            }
            cnt[it]--; if(cnt[it]==0) in.erase(it); 
        }
    };

    rrep(i,n){
        int a; cin>>a; 
        tmp[i] = a; add(a); 
    }

    auto get = [&](){
        if(in.size()>1) {
            cout << (*in.rbegin()+1) << " "; return; 
        }
        else {
            int x = *in.begin(); 
            if(cnt[x]==1) cout << x << " "; 
            else cout << (x+1) << " "; 
        }
    }; 

    while(q--){
        int x,y; cin>>x>>y; 
        erase(tmp[x]); tmp[x] = y; 
        add(y); 
        get(); 
    }
    for(auto x : in) cnt[x] = 0; 
    cout << "\n"; 

}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}