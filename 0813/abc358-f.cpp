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

int a[120][120]; 

pair<int,int> ne[120][120]; 

//
//
//                               S i r o t a n   w a t c h e s   o v e r   y o u .
//
//                                          ...Jggg+J+JJJg@NQmgJa.....,       
//                                 ....gH@@@@HHB""""7"YYYYHMMMMMMM@@@@@@@Hma,.   
//                            ...JH@@MMHY"!                        ? __""YH@@@@N&...     
//                        ..JH@@HY"~                                          _TW@@@Mme.    
//                     .Jg@@#"=                                                   _TTM@@N..     
//                  .Jg@@MY!                                                          ?T@@@h,.   
//                .-@@@B!                                                                (TM@@@L     
//              .(H@MY                                                                      ?W@@@+    
//             .W@@@                                                                          .T@@@[       
//           .d@@M!                                                                             .T@@N,   
//          .d@M@'                                                                                -W@@o. 
//         (@@M\                                                                                    ?M@N,
//        -d@M%                    ..,                                      ..,                      j@@b  
//       d@@M=                     TM9                                      ?MD                       W@@[ 
//      .H@M:                                                                                         .W@H,
//      H@Ht                                                                                           ,@@#   
//     (@@M~                                                                                           .@@h.
//    .@@M%                        ..gmHHJ.                             .JdHga.                        .H@@e  
//    j@@#_                       .@@@@@@@b                            J@@@@@@@h.                      .H@@\ 
//    d@@@                       .4@@@@@@MF                            (@@@@@@@@                        H@@b  
//    d@@[                         ?"BMY"=            .d@@@@H,          ?TWHHY"!                        d@@e    
//    J@@b          .JJJ-..,                         ,@@@@@@M%                       .........         -@@@M. 
//    ?@@M\         ?YHHM@@@@b                ..      .W@@HP                        X@@HMWY"=          d@@@#
//    ,@@@L.                                 ?H@Ng&+gd@@#H@@NHaJ+gH@[                                  J@@@] 
//     X@@@[            ......                 ?"YYYYY""   ?"YHHHB"^                 .....            (@@@#   
//      WH@N+.      .W@@@@MHB=                                                      .TWH@M@Hmc       .H@@M~    
//     .H@@@@N,      _!~                                                                            .d@@@N,   
//   .J@@#T@@@N,                                                                                  .d@@@@@@@b. 
//  (@@@@! .T@@@n,                                                                              .(H@@@H>.W@@@x  
// (@@@F      4@@@@MaJ.                                                                       .d@@@@Y77   4@@@r 
//.H@@P         ?TM@@@@N...                                                               .-JH@HMY=        d@@N,
//(@@@F             ?"WM@@@MQa-,.                                                  .(J(JN@@M#"             Z@@@L
// d@@H,                 (M@@@@@@@Ng&maJ....                           .. ...J.J+W@@@@@@HY!               .dH@b 
// ?M@@@N&.        ..(JW@@@MM"?7""TYHMH@@HH@@@@@HHHgkHagHa(mggdmmagH@H@@Q@@HMMMHY"7!TMM@@@HaJ,.        ..H@@@M^ 
//   ?"W@@@@MN@@@@@H@@MMY"                  _???!"= ?WMMBYYTMH=7""Y@""?"~^             _"YM@@@@@@@@MH@@@@@#"^ 
//       ?77WMMMYB""!      


void solve(){
    int n,m,k; cin>>n>>m>>k; 
    if(k<n||k>n*m) {
        cout << "No"; return;
    }
    if(k%2!=n%2){
        cout << "No"; return;
    }
    // for(int i=1;i<=n;i++) a[i][m] = 1; 
    for(int i=1;i<=n-1;i++) ne[i][m] = {i+1,m}; 
    k -= n; 
    //dbg(k)
    auto addR = [&](int i, int j){
        ne[i][j+1] = {i,j}; 
        ne[i][j] = {i+1,j}; 
        ne[i+1][j] = {i+1,j+1}; 
    }; 
    for(int i=1;i+1<=n;i+=2){
        for(int j=m-1;j>=1;j--) {
            if(k){
              //  dbg(i,j)
                addR(i,j); k-=2; 
            }
        }
    }
    auto addD = [&](int i, int j){
        ne[i-1][j] = {i,j}; 
        ne[i][j] = {i,j+1};
        ne[i][j+1] = {i-1,j+1}; 
    }; 
    if(k){
        for(int i=1;i+1<m;i+=2){
            if(k){
                //a[n][i] = a[n][i+1] = 1; 
                addD(n,i); 
                k-=2; 
            }
        }
    }
    cout << "Yes\n";
    auto chk = [&](int i, int j, int ii, int jj){
       // dbg(i,j,ne[ii][jj])
        if(ii==ne[i][j].ff&&jj==ne[i][j].ss) return true; 
        if(i==ne[ii][jj].ff&&j==ne[ii][jj].ss) return true; 
        return false; 
    }; 
    for(int i=2;i<=2*n+2;i++){
        if(i==2){
            rep(j,2*m-1) cout<<'+'; cout<<"S+\n"; continue; 
        }
        if(i==2*n+2){
            rep(j,2*m-1) cout<<'+'; cout<<"G+"; return; 
        }
        if(i%2){
            int ii = i/2; 
            cout << '+';
            for(int j=1;j<=m-1;j++){
                cout << 'o'; 
               // dbg(ii,j,ii,j+1,ne[ii][j+1])
                if(chk(ii,j,ii,j+1)) cout << '.'; else cout << '|'; 
            }
            cout <<"o+\n"; 
        }
        else {
            int ii = (i-2)/2;
            rrep(j,m){
                cout << '+'; 
                if(chk(ii,j,ii+1,j))cout << '.'; else cout << '-'; 
            }
            cout << "+\n"; 
        }
    }
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   //cin >> t;
   while(t--) solve(); 
   return 0;
}