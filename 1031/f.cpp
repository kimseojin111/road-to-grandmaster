#include <bits/stdc++.h>
using namespace std;
const int MOD = 1'000'000'007;

inline int addmod(int a, int b){ int s=a+b; if(s>=MOD) s-=MOD; return s; }
inline int submod(int a, int b){ int s=a-b; if(s<0) s+=MOD; return s; }
inline int mulmod(long long a, long long b){ return int((a*b)%MOD); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    if(!(cin>>t)) return 0;

    vector<int> pow2(1,1); // pow2[k] = 2^k % MOD

    while(t--){
        int n; cin>>n;
        vector<vector<int>> g(n+1);
        for(int i=0;i<n-1;i++){
            int u,v; cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        while((int)pow2.size()<=n) pow2.push_back(addmod(pow2.back(), pow2.back()));

        if(n<=1){ cout<<0<<"\n"; continue; }

        // root at 1: parent & order
        vector<int> parent(n+1,-1), order; order.reserve(n);
        vector<int> st = {1}; parent[1]=0;
        while(!st.empty()){
            int v=st.back(); st.pop_back();
            order.push_back(v);
            for(int w: g[v]) if(w!=parent[v]){
                parent[w]=v; st.push_back(w);
            }
        }
        // subtree sizes
        vector<int> sz(n+1,1);
        for(int i=n-1;i>=0;i--){
            int v=order[i];
            for(int w: g[v]) if(w!=parent[v]) sz[v]+=sz[w];
        }

        const int TWO_N = pow2[n];

        // 1) edge term
        int edge_term = 0;
        for(int v=2; v<=n; ++v){
            int a = sz[v];
            int contrib = submod(submod(addmod(TWO_N,1), pow2[a]), pow2[n-a]);
            edge_term = addmod(edge_term, contrib);
        }

        // 2) leaf term  sum_v sum_branches (2^{s_i}-1)
        int leaf_term = 0;
        for(int v=1; v<=n; ++v){
            for(int w: g[v]){
                int s = (w==parent[v]) ? (n - sz[v]) : sz[w];
                leaf_term = addmod(leaf_term, submod(pow2[s], 1));
            }
        }

        // 3) const term  -2*(2^n - n - 1)
        int const_term = submod(0, mulmod(2, submod(submod(TWO_N, n), 1)));

        // 4) branching-in-S correction: sum_v B_v
        int sum_B = 0;
        const int TWO_Nm1 = pow2[n-1];
        for(int v=1; v<=n; ++v){
            long long sumA = 0, sumA2 = 0; // A_i = 2^{s_i}-1
            for(int w: g[v]){
                int s = (w==parent[v]) ? (n - sz[v]) : sz[w];
                int Ai = submod(pow2[s], 1);
                sumA = (sumA + Ai) % MOD;
                sumA2 = (sumA2 + 1LL*Ai*Ai) % MOD;
            }
            // sum_{i<j} A_i A_j = ( (sumA)^2 - sumA2 ) / 2  (mod)
            long long sumPairs = ( (sumA*sumA - sumA2) % MOD + MOD ) % MOD;
            // divide by 2 (MOD is odd prime)
            long long inv2 = (MOD + 1) / 2;
            sumPairs = (sumPairs * inv2) % MOD;

            int Bv = submod(submod(submod(TWO_Nm1, 1), (int)sumA), (int)sumPairs);
            sum_B = addmod(sum_B, Bv);
        }

        int ans = addmod(addmod(edge_term, leaf_term), addmod(const_term, submod(0, sum_B)));
        cout << ans << "\n";
    }
    return 0;
}
