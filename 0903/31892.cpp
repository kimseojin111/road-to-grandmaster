#include <bits/stdc++.h> 
#define rrep(i,n) for(int i=1;i<=n;i++)
#define pb push_back 
#define all(v) (v).begin(), (v).end()
using namespace std; 

const int N = 400010; 
int b[N],e[N]; 
vector<int> adj[N]; 

int in[N], low[N], par[N]; 
int pv; 

void dfs(int v, int p){
    //cerr << v << " " << p << "\n";
	in[v] = low[v] = ++pv; 
	par[v] = p; 
	for(auto ne : adj[v]) if(ne!=p){
		if(!in[ne]) dfs(ne,v), low[v] = min(low[v],low[ne]); 
		else low[v] = min(low[v],in[ne]); 
	}
}

vector<int> bcc[N]; 
int cpp; 
bool vis[N];

int edge[N]; 
int bn[N]; 
 int cp;

void dfss(int v, int p, int col){
	if(vis[v]) return; 
	vis[v] = 1; 
	bcc[col].pb(v); 
	for(auto ne : adj[v]) if(ne!=p){
        if(par[ne]!=v) continue;
		if(in[ne]<in[v]) continue; 
        if(vis[ne]) continue;
		if(low[ne]>in[v]) {
			cpp++; 
			dfss(ne,v,cpp); 
		} else dfss(ne,v,col); 
	}	
}

bool kmp(vector<int> a, vector<int> b){
	vector<int> fail(b.size()); 
	for(int i=1,j=0; i<b.size(); i++) {
		while(j&&b[j]!=b[i]) j=fail[j-1]; 
		if(b[j]==b[i]) j++; 
		fail[i] = j; 
	}
	for(int i=0,j=0;i<a.size();i++){
		while(j&&a[i]!=b[j]) j=fail[j-1]; 
		if(a[i]==b[j]) j++; 
		if(j==b.size()) return true; 
	}
	return false; 
}

vector<int> BCC[N]; 
vector<pair<int,int>> bcc_edge[N]; 
vector<int> bcc_vertex[N]; 
vector<pair<int,int>> st; 
int bcc_odd[N]; 


void fuck(int v, int p){
    vis[v] = 1; 
    assert(p==par[v]);
    for(auto ne : adj[v]) if(ne!=p) {
        if(par[ne]==v||in[ne]<in[v]) st.pb({ne,v}); 
        if(vis[ne]) continue; 
        assert(par[ne]==v);
        if(!vis[ne]) fuck(ne,v); 
        if(low[ne]>=in[v]){
            vector<pair<int,int>> f; 
            while(1){
                auto [a,b] = st.back(); st.pop_back(); 
                bcc_edge[cp].pb({a,b}); 
                BCC[a].pb(cp); BCC[b].pb(cp); 
                bcc_vertex[cp].pb(a); bcc_vertex[cp].pb(b); 
                if(min(a,b)==min(ne,v)&&max(a,b)==max(ne,v)) break; 
            }
            cp++; 
        }
    }
}

struct fen {
    vector<int> v; int n; 
    fen(int n):n(n){
        v.resize(n+1); 
    }
    void upd(int p, int x){
        while(p){
            v[p]+=x; p-=p&-p; 
        }
    }
    int qry(int p){
        int re = 0; 
        while(p<=n){
            re += v[p]; p+=p&-p; 
        }
        return re; 
    }
}; 


int main(void){
	ios::sync_with_stdio(false); cin.tie(nullptr); 
	int n,m; cin>>n>>m; 
	rrep(i,n) cin>>b[i]>>e[i]; 
	rrep(i,m){
		int a,b; cin>>a>>b; adj[a].pb(b); adj[b].pb(a); 
	}
    fen F(1000100); 
	//cout << "input" << endl;
	rrep(i,n) if(!in[i]) dfs(i,i); 
    //cout << 1 <<endl;
	rrep(i,n) if(!vis[i]) {
		cpp++; 
		dfss(i,i,cpp); 	
	}
    //cout << 1 <<endl;
	for(int i=0;i<=cpp;i++){
		for(auto x : bcc[i]) bn[x] = i;
	}
	rrep(i,n) for(auto ne : adj[i]) if(ne>i) {
		if(bn[ne]==bn[i]) edge[bn[i]]++; 
	}
    cp = 0; 
    memset(vis,0,sizeof(vis)); 
    rrep(i,n) if(!vis[i]) {
        fuck(i,i); 
        assert(st.empty());
    }
    for(int i=0;i<cp;i++){
        sort(all(bcc_vertex[i])); 
        auto& v = bcc_vertex[i]; v.erase(unique(all(v)),v.end()); 
        if((v.size()%2)&&bcc_edge[i].size()==bcc_vertex[i].size()&&bcc_vertex[i].size()>2) bcc_odd[i] = 1; 
        if(bcc_vertex[i].size()==2) bcc_odd[i]=1;
    }
    rrep(i,n){
        sort(all(BCC[i])); BCC[i].erase(unique(all(BCC[i])),BCC[i].end()); 
    }
    memset(vis,0,sizeof(vis)); 
    auto inv = [&](vector<int>&v){
        long long re = 0; 
        for(auto x : v){
            re = re + F.qry(x); 
            F.upd(x,1); 
        }
        for(auto x : v) F.upd(x,-1); 
        return (re&1LL); 
    }; 
	auto chk = [&](int p){
 		auto& v = bcc[p]; 
		if(v.size()==0) return true; 
		if(v.size()==1){
			int x = v[0]; 
			return b[x]==e[x]; 
		}	
		if(edge[p]>v.size()){
			vector<int> bb,ee;
			for(auto x : v) bb.pb(b[x]), ee.pb(e[x]); 
			sort(all(bb)); sort(all(ee));
			if(bb!=ee) return false; 
            for(int i=0;i<bb.size();){
                int j = i; while(j<bb.size()&&bb[j]==bb[i]) j++; 
                if(j-i>1) return true; 
                i=j;  
            }
            for(auto x : v){
                for(auto i : BCC[x]) { 
                    if(!bcc_odd[i]) {
                        return true; 
                    }
                }
            }
            bb.clear(); 
            ee.clear(); 
            for(auto x : v) bb.pb(b[x]), ee.pb(e[x]); 
            return inv(bb)==inv(ee); 
		}
		else {
            int a=v[0],b1=v.back(); 
			vector<int> bb,ee; 
			for(auto x : v) bb.pb(b[x]),ee.pb(e[x]); 
			for(auto x : v) bb.pb(b[x]); 
			return kmp(bb,ee); 
		}
	}; 
	for(int i=0;i<=cpp;i++) if(!chk(i)){
		cout << "impossible"; return 0; 
	}
	cout << "possible"; return 0;
}