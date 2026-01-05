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

#include <atcoder/segtree>
using namespace atcoder; 

int op(int a, int b){return max(a,b);}
int e() {return -1;}

void solve(){
    int n; cin>>n; 
    vector<int> a(n+1),pa(n+1),b(n+1),pb(n+1); 
    rrep(i,n){
        cin>>a[i]; pa[a[i]]=i; 
    }
    set<int> s; 
    rrep(i,n) s.insert(i); 
    rrep(i,n){
        cin>>b[i]; if(b[i]!=0){
            s.erase(i); pb[b[i]] = i; 
        }
    }
    segtree<int,op,e> seg(n+1); 
    rrep(i,n){
        int x = seg.prod(1,pa[i]); 
        dbg(x,pb[i])
        if(pb[i]!=0){
            if(pb[i]<x){
                cout << -1 << "\n"; return; 
            }
        }
        else {
            auto it = s.upper_bound(x); 
            if(it==s.end()){
                cout << -1 << "\n"; return; 
            }
            pb[i] = *it; 
            dbg(i,pb[i])
            s.erase(it); 
        }
        seg.set(pa[i],pb[i]); 
    }
    rrep(i,n) b[pb[i]] = i; 
    rrep(i,n) cout << b[i] << " \n"[i==n];
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}