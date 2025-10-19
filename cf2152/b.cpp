#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;
using namespace atcoder;

struct S {
    int cnt[2];
    int first_[2];
    int last_[2];
    int ans[2];
};
struct F { bool flip; };

static inline S e_unit() {
    S x{};
    for (int p=0;p<2;++p){
        x.cnt[p]=0;
        x.first_[p]=-1;
        x.last_[p]=-1;
        x.ans[p]=0;
    }
    return x;
}

static vector<int> tin, tout, euler_enter_node;

S op(const S& L, const S& R){
    if (L.cnt[0]==0 && L.cnt[1]==0) return R;
    if (R.cnt[0]==0 && R.cnt[1]==0) return L;
    S res = e_unit();
    for (int p=0;p<2;++p){
        res.cnt[p] = L.cnt[p] + R.cnt[p];
        if (L.cnt[p] > 0) res.first_[p] = L.first_[p];
        else res.first_[p] = R.first_[p];
        if (R.cnt[p] > 0) res.last_[p] = R.last_[p];
        else res.last_[p] = L.last_[p];
        res.ans[p] = L.ans[p] + R.ans[p];
        if (L.cnt[p] > 0 && R.cnt[p] > 0){
            int lastIdx  = L.last_[p];
            int firstIdx = R.first_[p];
            int u = euler_enter_node[lastIdx];
            if (firstIdx > tout[u]) res.ans[p] += 1;
        }
    }
    return res;
}
S e(){ return e_unit(); }

S mapping(const F& f, const S& s){
    if (!f.flip) return s;
    S t = s;
    for (int k=0;k<2;++k){
        t.cnt[k]    = s.cnt[k^1];
        t.first_[k] = s.first_[k^1];
        t.last_[k]  = s.last_[k^1];
        t.ans[k]    = s.ans[k^1];
    }
    return t;
}
F composition(const F& fnew, const F& fold){ return F{ bool(fnew.flip ^ fold.flip) }; }
F id(){ return F{false}; }

inline S make_leaf_from_euler(int idx, int present_if_entry){
    S nd = e_unit();
    if (euler_enter_node[idx] == 0){
        return nd;
    }
    if (present_if_entry){
        nd.cnt[0] = 1; nd.first_[0] = idx; nd.last_[0] = idx; nd.ans[0] = 0;
        nd.cnt[1] = 0; nd.first_[1] = -1;  nd.last_[1]  = -1; nd.ans[1] = 0;
    }else{
        nd.cnt[0] = 0; nd.first_[0] = -1;  nd.last_[0]  = -1; nd.ans[0] = 0;
        nd.cnt[1] = 1; nd.first_[1] = idx; nd.last_[1]  = idx; nd.ans[1] = 0;
    }
    return nd;
}

int n;
vector<vector<int>> adj;
vector<int> a;
int pv;

void dfs_euler(int v, int p){
    tin[v] = ++pv;
    euler_enter_node[tin[v]] = v;
    for (int to : adj[v]){
        if (to == p) continue;
        dfs_euler(to, v);
    }
    tout[v] = ++pv;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    if(!(cin>>T)) return 0;
    while(T--){
        cin >> n;
        adj.assign(n+1, {});
        a.assign(n+1, 0);
        for (int i=1;i<=n;i++) cin >> a[i];
        for (int i=0;i<n-1;i++){
            int u,v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        tin.assign(n+1,0);
        tout.assign(n+1,0);
        pv = 0;
        euler_enter_node.assign(2*n+2, 0);
        dfs_euler(1, 0);
        vector<S> base(2*n);
        for (int idx=1; idx<=2*n; ++idx){
            int u = euler_enter_node[idx];
            int present = (u>0 ? a[u] : 0);
            base[idx-1] = make_leaf_from_euler(idx, present);
        }
        lazy_segtree<S, op, e, F, mapping, composition, id> seg(base);
        S all = seg.all_prod();
        int initial_ans = (all.cnt[0] == 0) ? 0 : (all.ans[0] + 1);
        cout << initial_ans << '\n';
        int q; cin >> q;
        while(q--){
            int v; cin >> v;
            int L = tin[v], R = tout[v];
            seg.apply(L-1, R, F{true});
            S cur = seg.all_prod();
            int ans = (cur.cnt[0] == 0) ? 0 : (cur.ans[0] + 1);
            cout << ans << '\n';
        }
    }
    return 0;
}
