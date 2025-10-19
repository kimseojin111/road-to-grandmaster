#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    if(!(cin >> T)) return 0;
    while (T--) {
        int n; cin >> n;
        vector<long long> v(n+1);
        for (int i = 1; i <= n; ++i) cin >> v[i];

        vector<int> a(n+1), b(n+1), posA(n+1), posB(n+1);
        for (int i = 1; i <= n; ++i) { cin >> a[i]; posA[a[i]] = i; }
        for (int i = 1; i <= n; ++i) { cin >> b[i]; posB[b[i]] = i; }

        // m[x] = min(rank in A, rank in B)
        vector<pair<int,long long>> items; items.reserve(n);
        for (int x = 1; x <= n; ++x) {
            int m = min(posA[x], posB[x]);
            items.emplace_back(m, v[x]);
        }
        sort(items.begin(), items.end(), [](auto &L, auto &R){ return L.first < R.first; });

        long long ans = 0;
        priority_queue<long long> pq;
        int ptr = 0;
        for (int k = 1; k <= n; ++k) {
            while (ptr < n && items[ptr].first <= k) {
                pq.push(items[ptr].second);
                ++ptr;
            }
            if (!pq.empty() && pq.top() > 0) {
                ans += pq.top();
                pq.pop();
            }
            // If the best available is ≤ 0, skip giving Alice a pick at this “k”.
        }
        cout << ans << "\n";
    }
    return 0;
}
