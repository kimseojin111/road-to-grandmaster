#include<bits/stdc++.h>
using namespace std;

#define INF 4000000000000000000
#define ll long long

#define rrep(i,n) for(int i=1;i<=n;i++)
#define pb push_back 
const int S = 200010; 
int N, Q;
vector<int> g[S]; // 인접 리스트
int st[S]; // 정점의 DFS preorder 순서
int out[S]; 
int h[S]; // 정점의 level
ll D[S]; // 정점에서 루트까지 가는 경로의 길이
int p[19][S]; // 스파스 테이블

int type[500001]; // 현재 쿼리에서 정점이 어떤 집합에 속하는가?

vector<int> fuck[S]; 


struct fen{
    vector<ll> a; int n; 
    fen(int n) : n(n) {
        a.resize(n+1); 
    }
    void upd(int p, ll v){
        while(p<n){
            a[p]+=v; p+=p&-p; 
        }
    }
    ll qry(int p){
        ll re = 0; 
        while(p){
            re += a[p]; p-=p&-p; 
        }
        return re; 
    }
    ll qry(int l, int r){
        return qry(r) - qry(l-1); 
    }
}; 


void DFS(int n, int prev)
{
	static int ord = 0;
    //cerr << n << " " << prev << endl; 
	st[n] = ++ord;
	h[n] = h[prev] + 1;
	p[0][n] = prev;
	for(auto ne : g[n])
	{
		if (ne == prev) continue;
		D[ne] = D[n] + 1;
		DFS(ne, n);
	}
    out[n] = ord; 
}   

int LCA(int a, int b)
{
	if (h[a] < h[b]) swap(a, b);
	int gap = h[a]-h[b];
	for(int i=0; i<19; i++)
		if (gap & 1<<i)
			a = p[i][a];
	if (a == b) return a;
	for(int i=18; i>=0; i--)
		if (p[i][a] != p[i][b])
			a = p[i][a], b = p[i][b];
	return p[0][a];
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; 
    int n = N; 
	for(int i=0; i<N-1; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	// Euler Tour와 LCA 전처리
	DFS(1, 0);
	for(int i=1; i<19; i++)
		for(int j=1; j<=N; j++)
			p[i][j] = p[i-1][p[i-1][j]];
    rrep(i,n) {
        cin >> type[i]; fuck[type[i]].pb(i); 
        //cerr <<i << endl; 
    }
    fen FEN(n+10); 
    ll ans = 0; 
	rrep(i,n) 
	{
		vector<int> A = fuck[i]; 
        // for(auto x : A){
        //     cerr << st[x]<<" "; 
        // }cerr<<endl; 
       // cerr<< i << endl; 
        for(auto x : A) FEN.upd(st[x],1); 
		// 1. Euler Tour 순으로 정렬하기
    //    cerr<< i << endl; 
		sort(A.begin(), A.end(), [&](int a, int b){ return st[a] < st[b]; });

		// 2. 인접한 정점 쌍들의 LCA를 추가하기
		int sz = A.size();
		for(int i=1; i<sz; i++)
			A.push_back(LCA(A[i-1], A[i]));
		sort(A.begin(), A.end(), [&](int a, int b){ return st[a] < st[b]; });
		A.erase(unique(A.begin(), A.end()), A.end());
        // for(auto x : A){
        //     cerr << x<<" "; 
        // }cerr<<endl; 
		// 3. 압축된 트리를 명시적으로 구성하기
        // for(auto x : A){
        //     cerr << x<<" "; 
        // }cerr<<endl; 
        int ttt = fuck[i].size(); 
		for(int i=1; i<A.size(); i++)
		{
			int prev = LCA(A[i-1], A[i]), n = A[i];
            ll f = FEN.qry(st[n],out[n]); 
            //cerr << n << " nfprev" << f << " " << prev << " " << (D[n]-D[prev]) << endl; 
            //cerr << D[n] << " ? " << D[prev] << endl;
            ans += 1LL*f*(ttt-f)*(D[n]-D[prev]); 
			//G[prev].push_back({n, D[n]-D[prev]});
		}
        for(auto x:fuck[i]) FEN.upd(st[x],-1); 
      //  cerr << ans << " grrrrrrrr " << endl; 
	}
    cout<<ans; 
	return 0;
}