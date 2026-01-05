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

using i128 = __int128_t;
struct Line {
    i128 anum, aden, bnum, bden;
    Line() {}
    Line(i128 _anum, i128 _aden, i128 _bnum, i128 _bden) : anum(_anum), aden(_aden), bnum(_bnum), bden(_bden) {}
    int cmpSlope(const Line& A, const Line& B) {
        i128 lhs = A.anum * B.aden;
        i128 rhs = B.anum * A.aden;
        if (lhs < rhs) return -1;
        if (lhs > rhs) return 1;
        return 0;
    }
    pair<i128,i128> valueFrac(i128 x) const {
        i128 num = anum * x * bden + bnum * aden;
        i128 den = aden * bden;
        return {num, den};
    }
    i128 valueCeil(i128 x) const {
        auto p = valueFrac(x);
        i128 num = p.first, den = p.second;
        if (num >= 0) return (num + den - 1) / den;
        return num / den;
    }
};

struct Cross { i128 num, den; };

static Cross intersectX(const Line& A, const Line& B) {
    i128 anum = A.anum*B.aden - B.anum*A.aden;
    i128 aden = A.aden*B.aden;
    i128 bnum = B.bnum*A.bden - A.bnum*B.bden;
    i128 bden = A.bden*B.bden;
    i128 num = bnum * aden;
    i128 den = anum * bden;
    return {num, den};
}

struct Hull {
    vector<Line> st;
    vector<Cross> cross;
    void clear() { st.clear(); cross.clear(); }
    void addLine(Line ln) {
        if (!st.empty() && Line::cmpSlope(ln, st.back()) == 0) {
            i128 LHS = ln.bnum * st.back().bden;
            i128 RHS = st.back().bnum * ln.bden;
            if (LHS >= RHS) return;
            else {
                st.pop_back();
                if (!cross.empty()) cross.pop_back();
            }
        }
        while (st.size() >= 1) {
            if (st.size() == 1) break;
            Line l1 = st[st.size()-2];
            Line l2 = st[st.size()-1];
            Cross x12 = intersectX(l1, l2);
            Cross x2n = intersectX(l2, ln);
            bool ge = (x12.num * x2n.den >= x2n.num * x12.den);
            if (ge) {
                st.pop_back();
                cross.pop_back();
            } else break;
        }
        if (!st.empty()) cross.push_back(intersectX(st.back(), ln));
        st.push_back(ln);
    }
    i128 queryCeil(i128 x) const {
        if (st.empty()) return (i128)LLONG_MAX;
        int l = 0, r = (int)cross.size()-1, ans = (int)cross.size();
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (cross[mid].num <= x * cross[mid].den) {
                ans = mid + 1;
                l = mid + 1;
            } else r = mid - 1;
        }
        return st[ans].valueCeil(x);
    }
};

void solve(){
    int n; cin >> n;
    vector<ll> a(n+1);
    rrep(i,n) cin >> a[i];
    vector<ll> dp(n+1);
    struct Node { ll v; ll B; };
    vector<Node> st;
    Hull hull;
    for (int i = 1; i <= n; ++i) {
        ll x = a[i];
        ll carry = dp[i-1];
        while (!st.empty() && st.back().v >= x) {
            carry = min(carry, st.back().B);
            st.pop_back();
        }
        st.pb({x, carry});
        hull.clear();
        for (int k = 0; k < (int)st.size(); ++k) {
            ll v = st[k].v;
            ll B = st[k].B;
            i128 anum = 1, aden = (i128)v;
            i128 bnum = (i128)B * (i128)v + (i128)(v - 1);
            i128 bden = (i128)v;
            hull.addLine(Line(anum, aden, bnum, bden));
        }
        i128 xi = (i128)x;
        i128 val = hull.queryCeil(xi);
        dp[i] = (long long)val;
    }
    cout << dp[n] << "\n";
}

signed main() {
   cin.tie(0)->ios::sync_with_stdio(0);
   cout.tie(nullptr);
   int t = 1;
   cin >> t;
   while(t--) solve(); 
   return 0;
}