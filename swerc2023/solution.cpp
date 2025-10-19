#include <bits/stdc++.h>
using namespace std; 
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rrep(i, n) for (int i = 1; i <= n; ++i)

const int N = 1000010; 
int a[N]; 
vector<int> pos[N]; 
int L[N],R[N]; 
int par[N]; 
int chk[N]; 
int find(int i){
    return i==par[i] ? i : par[i]=find(par[i]); 
}
int ans[N]; 
int ql[N],qr[N]; 

int psum[N]; 

void merge(int i, int j){
    i = find(i), j = find(j); 
    par[i] = j; 
    L[j] = min(L[i],L[j]); 
    R[j] = max(R[i],R[j]); 
}

int fen[N]; 

int qry(int x){
    int re = 0; 
    while(x){
        re += fen[x]; 
        x -= x&-x; 
    }
    return re; 
}
void upd(int x){
    while(x<N){
        fen[x] ++; x+=x&-x; 
    }
}

void solve(){
    int n; cin>>n; 
    rrep(i,n) par[i] = i, L[i] = i, R[i] = i; 
    rrep(i,n){
        cin>>a[i]; pos[a[i]].pb(i); 
    }
    vector<pair<int,int>> shit; 
    for(int i=n;i>0;i--){
        for(int x : pos[i]){
            chk[x] = 1; 
        }
        for(int x : pos[i]){
            if(chk[x-1]) merge(x-1,x); 
            if(chk[x+1]) merge(x+1,x); 
        }
        for(int j=0;j<pos[i].size();){
            int k = j; 
            while(k<pos[i].size()&&find(pos[i][j])==find(pos[i][k])) k++; 
            shit.pb({pos[i][j],pos[i][k-1]}); 
            j = k; 
        }   
    }
    sort(all(shit)); 
    shit.erase(unique(all(shit)),shit.end()); 
    for(auto [x,y]:shit) cout << x << " " << y << endl;
    for(auto [l,r] : shit) psum[l]++, psum[r]++; 
    for(int i=1;i<=n;i++) psum[i] += psum[i-1]; 
    // r 증가순으로   r, idx, l - > idx 0 추가 idx 1 쿼리 
    // l 이상인 것 합 
    int q; cin>>q; 
    vector<array<int,3>> v; 
    rrep(i,q){
        cin >> ql[i] >> qr[i]; 
        ans[i] = psum[qr[i]] - psum[ql[i]-1]; 
        v.pb({qr[i],i,ql[i]}); 
    }
    for(auto [l,r] : shit) v.pb({r,0,l});  
    sort(all(v)); 
    for(auto [r,op,l]:v){
        if(op==0){
            upd(l); 
        }
        else {
            int shit = qry(r) - qry(l-1); 
            ans[op] -= shit; 
        }
    }
    rrep(i,q) cout << ans[i] << "\n";
}

int main(void){
    ios::sync_with_stdio(false); cin.tie(nullptr); 
    solve(); 
}