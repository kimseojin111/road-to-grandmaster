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

struct Zz{
    int n, lgf, lgg; ll z;
    vector<int> f;
    vector<vector<int>> up;
    vector<int> meet0, g0, c0;
    vector<vector<int>> gup, sumup, lastm;

    Zz() {}
    Zz(int nn, ll zz, const vector<ll>& x){ init(nn, zz, x); }

    void init(int nn, ll zz, const vector<ll>& x){
        n = nn; z = zz;

        f.resize(n+2);
        int r = 1;
        rrep(i, n){
            if (r < i+1) r = i+1;
            while (r <= n && x[r] <= x[i] + z) ++r;
            f[i] = (r <= n ? r : n+1);
        }
        f[n+1] = n+1;

        lgf = 1; while ((1<<lgf) <= n+1) ++lgf;
        up.resize(lgf);
        rep(k, lgf) up[k].resize(n+2);
        rrep(i, n+1) up[0][i] = f[i];
        rrep(k, lgf-1){
            rrep(i, n+1){
                up[k][i] = up[k-1][ up[k-1][i] ];
            }
        }

        meet0.resize(n+2);
        g0.resize(n+2);
        c0.resize(n+2);

        rrep(i, n){
            int j = (i+1 <= n ? i+1 : n+1);
            int m = meet(i, j);
            meet0[i] = m;
            int K = cnt(i, m) - 1;            // m = f^K(i)
            if (m <= n) c0[i] = 2*K + 2; else c0[i] = 0;
            g0[i] = f[m];
        }
        meet0[n+1] = n+1; g0[n+1] = n+1; c0[n+1] = 0;

        lgg = 1; while ((1<<lgg) <= n+1) ++lgg;
        gup.resize(lgg); sumup.resize(lgg); lastm.resize(lgg);
        rep(k, lgg){
            gup[k].resize(n+2);
            sumup[k].resize(n+2);
            lastm[k].resize(n+2);
        }
        rrep(i, n+1){
            gup[0][i] = g0[i];
            sumup[0][i] = c0[i];
            lastm[0][i] = meet0[i];
        }
        rrep(k, lgg-1){
            rrep(i, n+1){
                int mid = gup[k-1][i];
                gup[k][i]   = gup[k-1][mid];
                sumup[k][i] = sumup[k-1][i] + sumup[k-1][mid];
                lastm[k][i] = lastm[k-1][mid];
            }
        }
    }

    int cnt(int s, int r){
        if (s > r) return 0;
        int t = 1, cur = s;
        rep(hh, lgf){
            int k = lgf-1-hh;
            int v = up[k][cur];
            if (v <= r){ t += (1<<k); cur = v; }
        }
        return t;
    }

    int meet(int u, int v){
        if (u == v) return u;
        int a = u, b = v;
        rep(hh, lgf){
            int k = lgf-1-hh;
            if (up[k][a] != up[k][b]){
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    }

    int ask(int l, int r){
        if (l > r) return 0;
        if (l == r) return 1;
        int ans = 0, i = l;
        rep(hh, lgg){
            int k = lgg-1-hh;
            int lm = lastm[k][i];
            if (lm <= n && lm + 1 <= r){
                ans += sumup[k][i];
                i = gup[k][i];
            }
        }
        if (i <= r){
            int A = cnt(i, r);
            int B = (i+1 <= r ? cnt(i+1, r) : 0);
            int m = meet(i, (i+1 <= n ? i+1 : n+1));
            if (m <= r) ans += A + B - 1; else ans += A + B;
        }
        return ans;
    }
};

void solve(){
    int n; ll z; cin >> n >> z;
    vector<ll> x(n+1);
    rrep(i, n) cin >> x[i];
    Zz S(n, z, x);
    int q; cin >> q;
    while (q--){
        int l, r; cin >> l >> r;
        cout << S.ask(l, r) << "\n";
    }
}


signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1; cin>>t;
   while(t--) solve(); 
   return 0;
}
