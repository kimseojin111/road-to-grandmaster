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
    string s; cin>>s; 
    if(s.size()<8){
        auto g = [](int x){
            string s = to_string(x); 
            int re = 0; for(auto c : s) re += (c-'0'); 
            return re; 
        }; 
        int n = stoi(s); 
        for(int i=n;i+1<=n*2;i++){
            if(i%g(i)==0&&(i+1)%g(i+1)==0){
                cout << i; return; 
            }
        }
        cout << -1; return;
    }
    if(s[0]=='1'){
        bool shit = true; 
        for(int i=1;i<s.size(); i++) if(s[i]!='0') shit=false; 
        if(shit){
            cout << 1; rep(i,s.size()-3) cout << 0; cout << "11"; return; 
        }
        else {
            cout << 2; rep(i,s.size()-1) cout << 0; return;  
        }
    }
    if(s[0]=='2'){
        cout << 3; rep(i,s.size()-5) cout <<0; cout << "5000"; return; 
    }
    if(s[0]=='3'){
        cout << 4; rep(i,s.size()-3) cout <<0; cout << "40"; return; 
    }
    if(s[0]=='4'||s[0]=='5'){
        cout << 6; rep(i,s.size()-4) cout << 0; cout << "200"; return; 
    }
    cout << 1; rep(i,s.size()-2) cout << 0; cout << "11"; return; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}