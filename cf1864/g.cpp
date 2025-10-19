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

// 1) 고정 행, 열 구하기  직사각형 이뤄야함
// 2) 맨처음 움직인 행,열 개수 구하기 그니까 고정 열 or 고정 행에서 값들이 모두 같은 행 or 열 구해서 곱하기 
// 3) 걔네 rotate  
// 2) 이 과정 반복하면서 구하기 ok 
 
const int N = 510; 
int a[N][N]; 
int b[N][N]; 
int fixed_r[N]; 
int fixed_c[N]; 
int mv[N*N]; 

int rto[N]
int cto[N]; 

int ax[N*N],ay[N*N]; 
int bx[N*N],by[N*N]; 


void init(int n){
    rrep(i,n){
        fixed_r[i] = fixed_c[i] = 0; 
        rto[i] = cto[i] = 0; 
    }
    rrep(i,n*n) mv[i] = 0; 
}

#include <atcoder/modint> 
using namespace atcoder; 
using mint = modint998244353; 
mint fac[N]; 

void solve(){
    int n; cin>>n; 
    init(n); 
    rrep(i,n) rrep(j,n) {
        cin>>a[i][j]; ax[a[i][j]] = i, ay[a[i][j]] = j; 
    }
    rrep(i,n) rrep(j,n){
        cin>>b[i][j];  bx[b[i][j]] = i, by[b[i][j]] = j; 
    } 
    rrep(i,n) rrep(j,n) {
        if(a[i][j]==b[i][j]){
            fixed_r[i] = fixed_c[j] = 1; 
        }
    }
    bool shit = false; 
    rrep(i,n) rrep(j,n) if(fixed_r[i]&&fixed_c[j]){
        shit = true; 
        if(a[i][j]!=b[i][j]) {
            cout << 0 << "\n"; return; 
        }
    }
    int fx = 0,fy = 0; 
    rrep(i,n) if(!fixed_r[i]) fx++; 
    rrep(i,n) if(!fixed_c[i]) fy++; 
    if(!shit){
        cout << 0 << "\n"; return; 
    }
    set<pair<int,int>> wtf; 
    rrep(i,n*n){
        int dx = ax[i]-bx[i],dy = ay[i]-by[i]; 
        if(dx==0&&dy==0) continue; 
        if(dx==0){
            if(dy<0) dy+=n; 
            if(rto[ax[i]]==0) rto[ax[i]] = dy; 
            if(rto[ax[i]]!=dy){
                cout << 0 << "\n"; return; 
            }
            continue; 
        }
        if(dy==0){
            if(dx<0) dx+=n; 
            if(cto[ay[i]]==0) cto[ay[i]] = dx; 
            if(rto[ax[i]]!=dx){
                cout << 0 << "\n"; return; 
            }
            continue; 
        }
        if(wtf.find({dx,dy})!=wtf.end()) { 
            dbg(1)
            cout << 0 << "\n"; return; 
        }
        wtf.insert({dx,dy}); 
    }
    if(wtf.size()!=fx*fy){
        cout << 0 << "\n"; return; 
    }

    mint ans = 1; 
    auto rotate_r = [&](int r, int t){
        // v.begin()+t 가 앞을 가리키게 됨 
        if(t<0) t+=n; 
        vector<int> v; rrep(j,n) v.pb(a[r][j]); 
        for(auto x : v){
            if(mv[x]==2) return false; 
            mv[x]++; 
        }
        rotate(v.begin(),v.begin()+t,v.end()); 
        rrep(j,n) {
            a[r][j] = v[j-1]; ay[a[r][j]] = j;
        }
        return true; 
    }; 
    
    auto rotate_c = [&](int c, int t){
        // v.begin()+t 가 앞을 가리키게 됨 
        if(t<0) t+=n; 
        vector<int> v; rrep(j,n) v.pb(a[j][c]); 
        for(auto x : v){
            if(mv[x]==2) return false; 
            mv[x]++; 
        }
        rotate(v.begin(),v.begin()+t,v.end()); 
        rrep(j,n) {
            a[j][c] = v[j-1]; ax[a[j][c]] = j;
        }
        return true; 
    }; 

    if(fx==0){
        int cc = 0; 
        rrep(j,n) if(!fixed_c[j]) {
            c++; rotate_c(j,cto[j]); 
        }
        rrep(i,n) rrep(j,n) if(a[i][j]!=b[i][j]){
            cout << 0 << "\n"; return; 
        }
        cout << fac[cc].val() << "\n"; return; 
    }

    if(fy==0){
        int cc = 0; 
        rrep(j,n) if(!fixed_r[j]) {
            c++; rotate_r(j,rto[j]); 
        }
        rrep(i,n) rrep(j,n) if(a[i][j]!=b[i][j]){
            cout << 0 << "\n"; return; 
        }
        cout << fac[cc].val() << "\n"; return; 
    }


    auto print_ = [&](){
        //rep(i,n) rrep(j,n) cerr << a[i][j] << " \n"[j==n]; 
        //rrep(i,n*n) cerr << i << " " << ax[i] << " " << ay[i] << " \n"; 
    }; 
    
    cout << ans.val() << "\n"; 
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   fac[0] = 1; 
   for(int i=1;i<N;i++) fac[i] = fac[i-1]*i; 
   while(t--) solve(); 
   return 0;
}