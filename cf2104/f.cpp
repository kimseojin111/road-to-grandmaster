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

ll ncr[30][30]; 

ll pw10[30]; 

ll nhr(int n, int r){
    return ncr[n+r-1][r-1]; 
}

int sz(ll x){
    if(x<=0) return 0; 
    string s = to_string(x);
    return s.size(); 
}

ll wtf(int i, string& s, int pv){
    if(i==s.size()) return 1; 
    if(s[i]-'0'>=pv){
        ll fuck = nhr(s.size()-i-1,10-pv+1)*(s[i]-'0'-pv); 
        return fuck+wtf(i+1,s,s[i]-'0'); 
    }
    if(s[i]=='0'){
        return wtf(i+1,s,pv); 
    }
    return nhr(s.size()-i-1,10-pv+1); 
}

ll compute(ll x){
    if(x==0) return 1; 
    string s = to_string(x); 
    ll ans = 0; 
    int l = s.size(); 
    //dbg(x,l,wtf(1,s,s[0]))
    ans = nhr(l-1,10)*((s[0]-'0')-1) + wtf(1,s,s[0]-'0'); 
    return ans; 
}

ll gg(ll x){
    if(x<=9) return x; 
    map<ll,ll> M; 
    ll re = 0; 
    for(int i=0;i<=8;i++){
        ll y = (x-i)/10; 
        if(sz(y)==sz(x)-1) {
            if(M.find(y)==M.end()) {
                M[y] = compute(y); 
                dbg(y,compute(y))
            }
            re += M[y]; 
        } 
    }
    for(int i=0;i<=8;i++){
        if(x<10*i+9) break; 
        ll y = (x-i*10-9)/100; 
        if(sz(x)==2 && i==0) continue; 
        if(sz(y)==sz(x)-2){
            if(M.find(y)==M.end()){
                M[y] = compute(y); 
                dbg(y,compute(y))
            }
            re += M[y]; 
        }
    }
    return re; 
}

ll psum[30]; 


void solve(){
    ll n; cin>>n; 
    int s = sz(n); 
    if(n==pw10[s]-1){
        cout << psum[s-1] << "\n"; return; 
    }
    if(n<=10){
        cout << n << "\n"; return; 
    }
    ll ans = psum[s-2] + gg(n);
    cout << ans << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
    ncr[0][0] = 1; 
    ncr[1][0] = ncr[1][1] = 1; 
    for(int n=2;n<30;n++){
        ncr[n][0] = ncr[n][n] = 1; 
        for(int r=1;r<n;r++) ncr[n][r] = ncr[n-1][r] + ncr[n-1][r-1]; 
    }
    gg(42);
    pw10[0] = 1; 
    for(int i=1;i<=10;i++) pw10[i] = pw10[i-1]*10; 
    psum[0] = gg(pw10[1]-1); 
    for(int i=1;i<9;i++){
        psum[i] = gg(pw10[i+1]-2)+1; 
        psum[i] += psum[i-1]; 
    }
    cin >> t;
    while(t--) solve(); 
    return 0;
}