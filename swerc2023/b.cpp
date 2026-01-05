#include <bits/stdc++.h>
#define pb push_back
using namespace std; 

// swerc 

const int N = 1010; 
int A[N],B[N]; 

vector<int> adj[N]; 
bool vis[N]; 
bool dfs(int v){
    vis[v] = true; 
    for(int b : adj[v]) {
        if(B[b] == -1 || !vis[B[b]]&&dfs(B[b])) {
            A[v] = b; 
            B[b] = v; 
            return true; 
        }
    }
    return false; 
}

int main(void){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n,m; cin>>n>>m; 
    for(int i=1;i<=n;i++){
        int x; cin>>x; 
        while(x--){
            int p; cin>>p; adj[i].pb(p); 
        }
    }
    int t = 0; 
    for(int i=1;i<=m;i++) B[i] = -1; 
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis)); 
        if(dfs(i)) t++; 
    }
    cout << t; 
}