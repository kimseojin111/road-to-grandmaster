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
    int n,x,y; cin>>n>>x>>y;
    string s,t; cin>>s>>t; 
    // 0,x 1,y 
    int s0=0,s1=0,t0=0,t1=0; 
    for(auto c:s) if(c=='0') s0++; else s1++;
    for(auto c:t) if(c=='0') t0++; else t1++; 
    if(s0!=t0||s1!=t1){
        cout << "No" << "\n"; return; 
    }
    auto get = [&](auto s){
        vector<pair<int,int>> re; 
        for(int i=0;i<s.size();){
            int j = i; 
            while(j<s.size()&&s[j]==s[i]) j++; 
            if(s[i]=='0'){
                int m = (j-i)/x, d = (j-i)%x; 
                rep(k,m) re.pb({0,x}); 
                if(d) re.pb({0,d}); 
            }
            if(s[i]=='1'){
                int m = (j-i)/y, d = (j-i)%y;
                rep(k,m) re.pb({1,y}); 
                if(d) re.pb({1,d}); 
            }
            i=j; 
        }
        return re; 
    };
    auto v = get(s); 
    auto vv = get(t); 
    auto gett = [&](auto v){
        vector<pair<int,int>> a; 
        for(auto [ty,s]:v){
            if(ty==0&&s!=x) a.pb({ty,s}); 
            if(ty==1&&s!=y) a.pb({ty,s}); 
        }
        return a; 
    }; 
    if(gett(v)!=gett(vv)){
        cout << "No" << "\n"; return; 
    }
    auto fuck = [&](auto v){
        vector<int> re; 
        vector<int> ree;
        int p = 0,q=0; 
        // p -> 0 사이 껴있는 B(1y)      q -> 1 사이 껴있는 A(0x)
        for(auto [ty,s]:v){
            if(ty==0&&s==x) q++;
            else if(ty==1&&s==y) p++; 
            else if(ty==0){
                re.pb(p); p=0; 
            }
            else if(ty==1){
                ree.pb(q); q=0; 
            }
        }
        re.pb(p); ree.pb(q); 
        return make_pair(re,ree); 
    }; 
    if(fuck(v)!=fuck(vv)){
        cout << "No" << "\n"; return; 
    }
    cout << "Yes" << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}