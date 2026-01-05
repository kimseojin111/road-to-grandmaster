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

const int N = 300010; 
int a[N],l[N],r[N],rr[N]; 
int consider[N]; 
// 직사각형 세그   

int ans[N];

struct seg{
    vector<int> t; int n; 
    seg(int n) : n(n){
        t.resize(4*n+10); 
    }
    void upd(int node, int s, int e, int l, int r, int op){
        // op 1 add . op -1 erase 
        if(l<=s&&e<=r) {
            t[node] += op; return; 
        }
        if(r<s||l>e) return; 
        int m = s+e>>1; 
        upd(2*node,s,m,l,r,op); 
        upd(2*node+1,m+1,e,l,r,op); 
    }
    int qry(int node, int s, int e, int p){
        dbg(node,s,e,p,t[node])
        if(t[node]) return 1; 
        if(s==e) return 0; 
        int m = s+e>>1; 
        if(p<=m) return qry(2*node,s,m,p); 
        return qry(2*node+1,m+1,e,p); 
    }
}; 

void solve(){
    int n; cin>>n; 
    vector<pair<int,int>> tmp; 
    rrep(i,n) {
        cin>>a[i]; tmp.pb({a[i],i}); consider[i] = 1; 
    }
    sort(all(tmp)); 
    // 나 이하 집합 LM, 나보다 큰 집합 M 
    // l +1, u d +1,    r+1 -1, u d -1           x, 100, pos, idx 
    set<int> M,LM; 
    rrep(i,n) M.insert(i); 
    vector<array<int,4>> qrys; 
    for(int j=0;j<tmp.size();){
        int k = j; 
        vector<int> f; 
        while(k<tmp.size()&&tmp[k].first==tmp[j].first){
            f.pb(tmp[k].second); k++; 
        }
        for(auto x : f) LM.insert(x); 
        for(auto x : f) M.erase(x); 
        for(auto i : f){
            auto it = M.lower_bound(i); 
            if(it==M.end()) {
                continue; 
            }
            r[i] = *it; 
            auto fc = LM.lower_bound(r[i]); 
            if(fc==LM.end()) rr[i] = n; 
            else rr[i] = (*fc)-1; 
            if(it==M.begin()){
                l[i] = 1;  
            }
            else {
                it--; l[i] = (*it)+1; 
            }
            // [l[i],i] * [r[i],rr[i]]
            dbg(i,l[i],r[i],rr[i])
            qrys.pb({l[i],1,r[i],rr[i]}); 
            qrys.pb({i+1,-1,r[i],rr[i]}); 
        }
        j=k; 
    }
    int q; cin>>q; 
    rrep(i,q) {
        ans[i] = 0; 
        int l,r;cin>>l>>r; 
        qrys.pb({l,100,r,i}); 
    }
    sort(all(qrys)); 
    seg S(n+2); 
    dbg(qrys)
    for(auto [l,op,u,d]:qrys){
        if(op==1||op==-1){
            S.upd(1,0,n+2,u,d,op); 
        }
        else {
            int k = S.qry(1,0,n+2,u); 
            ans[d] = k; 
        }
    }
    rrep(i,q) {
        if(ans[i]) cout << "Yes\n";
        else cout << "No\n";
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