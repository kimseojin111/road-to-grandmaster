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
#include <atcoder/modint> 
using namespace atcoder; 
using mint = modint998244353; 

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
void __print(mint x) {cerr << (x.val());}

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
mint fac[N],rfac[N]; 

int a[N]; 
int pos[N]; 
int posx[N]; 
int b[N]; 
int bsum[N]; 
int bgo[N]; 
int bcon[N]; 

mint ncr(int n, int r){
    if(r<0||r>n) return mint(0); 
    return fac[n]*rfac[r]*rfac[n-r]; 
}

void solve(){
    int n,k; cin>>n>>k; 
    rep(i,n){
        pos[i]=posx[i]=b[i]=bsum[i]=bgo[i]=bcon[i]=0; 
        char c; cin>>c; 
        if(c=='0') a[i] = -1; 
        else if(c=='1') a[i] = 1; 
        else a[i] = 0; 
    }
    rep(i,n) pos[i]=posx[i] = 0; 
    pos[0] = 1; posx[0] = a[0]; 
    for(int i=1;i<n;i++){
        if(pos[i-1]){
            if(a[i]==0){
                posx[i] = posx[i-1]; 
                pos[i] = 1; continue; 
            } else {
                if(posx[i-1]==0){
                    pos[i] = 1; posx[i] = a[i]; 
                } else {
                    if(a[i]!=posx[i-1]){
                        pos[i] = 0; break; 
                    }
                    pos[i] = 1; posx[i] = a[i]; 
                }
            }
        }
    }
    rep(i,n) b[i] = 0; // b-> 되냐 안되냐 
    b[n-1] = 1; 
    bsum[n-1] = a[n-1]; // 거기까지 합 
    if(b[n-1]) bgo[n-1] = a[n-1]; // bgo -> 거기서 값. 
    bcon[n-1] = (a[n-1]!=0); // bcon -> 거기까지 결정된 것의 개수 
    for(int i=n-2;i>=0;i--){
        int ne = (i+k-1<n ? bgo[i+k-1]:0); 
        if(a[i]==0){
            b[i] = 1; 
            bgo[i] = ne; 
            bcon[i] = bcon[i+1]; 
            bsum[i] = bsum[i+1]; 
            continue; 
        } else {
            if(ne==0){
                bgo[i] = a[i]; 
                bcon[i] = bcon[i+1]+(a[i]!=0); 
                bsum[i] = bsum[i+1]+a[i]; 
                b[i] =1; continue; 
            } else {
                if(ne!=a[i]){
                    b[i]=0; break; 
                } else {
                    b[i] = 1; 
                    bgo[i] = a[i]; 
                    bcon[i] = bcon[i+1]; 
                    bsum[i] = bsum[i+1]; 
                    continue; 
                }
            }
        }
    }
    for(int i=n-1;i>=0;i--){
        dbg(i,bcon[i],bsum[i])
    }
    mint ans = 0; 
    int cz = 0; 
    for(int i=0;i<=n-k-1;i++) {
        cz += (a[i]==0); 
        dbg(i,ans)
        if(pos[i]&&b[i+1]){
            dbg(i)
            int lx = posx[i]; 
            // 지금 오른쪽에 결정된 것 : bcon[i+1], 합 : bsum[i+1], 
            // 오른쪽에 합 0 : 
            int bc = bcon[i+1], bs = bsum[i+1]; 
            dbg(posx[i],bgo[i+1],bc,bs)
            if(posx[i]){
                if(bgo[i+1]==0){
                    bc++; bs += (posx[i]==1 ? -1 : 1); 
                    dbg("wtf??",bc,bs)
                    ans += ncr(k-1-bc,(k-1-bc-bs)/2); 
                } else if(bgo[i+1]==posx[i]) continue; 
                else {
                    dbg("wtf??")
                    ans += ncr(k-1-bc,(k-1-bc-bs)/2); 
                }
            } else {
                if(bgo[i+1]!=0){
                    ans += ncr(k-1-bc,(k-1-bc-bs)/2); 
                } else {
                    bc++; bs++; 
                    ans += ncr(k-1-bc,(k-1-bc-bs)/2); 
                    bs-=2; 
                    ans += ncr(k-1-bc,(k-1-bc-bs)/2); 
                }
            }

            // int x = (k-1-2*bs); // ncr(k-1-bc,x)
        }
    }
    dbg(ans)
    cz += (a[n-k]==0); 
    if(pos[n-k]) {
        // 이 뒤에 k-1 개에서 합이 >=0 or <= 0 
        int po=0,ne=0,ze=0; 
        for(int j=n-k+1;j<n;j++){
            if(a[j]==-1) ne++; 
            else if(a[j]==1) po++; 
            else ze++; 
        }
        for(int r=0;r<=ze;r++){
            // po + r - (ne + ze-r); 
            int shit = po+r-(ne+ze-r); 
            mint tmp = ncr(ze,r); 
            int lx = posx[n-k]; 
            dbg(tmp)
            if(shit>0){
                if(lx>=0){
                    ans += tmp; 
                }
            } else if(shit==0){
                ans += tmp * (lx==0 ? 2 : 1); 
            } else {
                if(lx<=0) {
                    ans += tmp; 
                }
            }
        }
    }
    cout << ans.val() << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   fac[0] = 1; rfac[0] = 1; 
   for(int i=1;i<N;i++){
    fac[i] = i*fac[i-1]; 
    rfac[i] = rfac[i-1]/i; 
   }
   while(t--) solve(); 
   return 0;
}