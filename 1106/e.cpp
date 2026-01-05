#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz, parity; // parity: (#odd in component) mod 2
    DSU(int n=0){init(n);}
    void init(int n){
        p.resize(n+1);
        sz.assign(n+1,1);
        parity.assign(n+1,0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
        parity[a]^=parity[b];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int n,m; cin>>n>>m;
        vector<int> u(m+1), v(m+1);
        vector<long long> w(m+1), suf(m+2, (long long)4e18);
        vector<int> deg(n+1,0);
        long long base=0;
        for(int i=1;i<=m;i++){
            cin>>u[i]>>v[i]>>w[i];
            deg[u[i]]++; deg[v[i]]++;  // loop -> +2 automatically
            base += w[i];
        }
        for(int i=m;i>=1;i--) suf[i]=min(suf[i+1], w[i]);

        DSU dsu(n);
        for(int i=1;i<=n;i++){ dsu.p[i]=i; dsu.parity[i]=deg[i]&1; }

        long long extra=0;
        for(int i=1;i<=m;i++){
            int a=dsu.find(u[i]), b=dsu.find(v[i]);
            if(a!=b){
                if(dsu.parity[a] && dsu.parity[b]) extra += suf[i];
                dsu.unite(a,b);
            }
        }
        cout << (base + extra) << '\n';
    }
    return 0;
}
