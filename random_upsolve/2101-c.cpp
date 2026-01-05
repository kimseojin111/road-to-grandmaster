#include <bits/stdc++.h>
#define pb push_back 
#define all(v) (v).begin(), (v).end()
using ll = long long;
using namespace std; 

int main(void){
	ios::sync_with_stdio(false); cin.tie(nullptr); 
	int t; cin>>t; 
	while(t--){
		int n; cin>>n; 
		vector<int> a(n+1);
		vector<vector<int>> chk(n+1); 
		for(int i=1;i<=n;i++) {
			cin>>a[i]; 
			chk[a[i]].push_back(i);
		}
		vector<int> R(n+1),l(n+1); 
		// R 
		priority_queue<int> pq; 
		vector<int> tmp; 
		for(int i=n;i>0;i--){
			for(int x : chk[i]) pq.push(x); 
			if(!pq.empty()){
				tmp.pb(pq.top()); 
				pq.pop();
			}
		}
		priority_queue<int,vector<int>,greater<>> pqq; 
		vector<int> u; 
		for(int i=n;i>0;i--){
			for(int x : chk[i]) pqq.push(x); 
			if(!pqq.empty()){
				u.pb(pqq.top()); 
				pqq.pop(); 
			}
		}
		ll ans = 0; 
		sort(all(u)); sort(all(tmp),[](auto a, auto b){
			return a>b; 
		}); 
		ll shit = 0; 
		for(int i=0;i<u.size();i++){
			//cerr << tmp[i] << " " << u[i] << endl; 
			shit += (tmp[i]-u[i]); 
			ans = max(ans,shit); 
		}
		cout <<ans << "\n"; 
	}
}
