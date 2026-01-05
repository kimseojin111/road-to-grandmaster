#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1'000'000'007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    vector<pair<int,int>> q(t);
    int maxN = 0, maxM = 0;
    for (int i = 0; i < t; i++) {
        int n, m;
        cin >> n >> m;
        q[i] = {n, m};
        maxN = max(maxN, n);
        maxM = max(maxM, m);
    }

    // queries grouped by n, then sorted by m
    vector<vector<pair<int,int>>> byN(maxN + 1);
    for (int i = 0; i < t; i++) {
        byN[q[i].first].push_back({q[i].second, i});
    }
    for (int n = 1; n <= maxN; n++) {
        sort(byN[n].begin(), byN[n].end());
    }

    vector<int> ans(t);

    // We only need 4^k for k up to max(2*maxN, maxM, maxN+1)
    int lim = max({2 * maxN + 2, maxM + 2, maxN + 2});
    vector<int> pow4(lim + 1, 1);
    for (int i = 1; i <= lim; i++) {
        pow4[i] = (long long)pow4[i - 1] * 4 % MOD;
    }

    // rolling arrays for dp1..dp4 (m from 0..maxM)
    vector<int> dp1_prev(maxM + 1, 0), dp2_prev(maxM + 1, 0),
                dp3_prev(maxM + 1, 0), dp4_prev(maxM + 1, 0);

    for (int n = 1; n <= maxN; n++) {
        vector<int> dp1_cur(maxM + 1, 0), dp2_cur(maxM + 1, 0),
                    dp3_cur(maxM + 1, 0), dp4_cur(maxM + 1, 0);

        long long Pn1 = pow4[n - 1];     // 4^(n-1)
        long long multStop = pow4[n + 1];// when m increases: stopFac *= 4^(n+1)

        // stopFac(n,1) = 4^((n+1)*2 - 4) = 4^(2n-2)
        long long stop = pow4[2 * n - 2];

        // pointer for answering queries at this n
        auto &vec = byN[n];
        int ptr = 0;

        for (int m = 1; m <= maxM; m++) {
            long long Pm1 = pow4[m - 1]; // 4^(m-1)
            long long Pm  = pow4[m];     // 4^m

            long long baseDown = (dp1_prev[m] + 2LL * dp2_prev[m]) % MOD;

            long long dp3Left = dp3_cur[m - 1];
            long long dp4Left = dp4_cur[m - 1];

            // dp1
            long long v1 = 7LL * stop % MOD;
            if (n > 1) {
                v1 = (v1 + (3LL * Pm1 % MOD) * baseDown) % MOD;
            }
            dp1_cur[m] = (int)v1;

            // dp2
            long long v2 = stop % MOD;
            if (n > 1) {
                v2 = (v2 + (3LL * Pm1 % MOD) * baseDown) % MOD;
            }
            if (m > 1) {
                long long bracket = (dp3Left + 5LL * dp4Left) % MOD;
                v2 = (v2 + Pn1 * bracket) % MOD;
            }
            dp2_cur[m] = (int)v2;

            // dp3
            long long v3 = 7LL * stop % MOD;
            if (m > 1) {
                long long bracket = (dp3Left + 2LL * dp4Left) % MOD;
                v3 = (v3 + (Pn1 * 3 % MOD) * bracket) % MOD;
            }
            dp3_cur[m] = (int)v3;

            // dp4
            long long v4 = stop % MOD;
            if (n > 1) {
                v4 = (v4 + Pm * baseDown) % MOD;
            }
            if (m > 1) {
                v4 = (v4 + (Pn1 * 3 % MOD) * dp4Left) % MOD;
            }
            dp4_cur[m] = (int)v4;

            // dp0 = dp1 + 3*dp2, Answer = 4*dp0 (restore the excluded (0,0))
            long long dp0 = (dp1_cur[m] + 3LL * dp2_cur[m]) % MOD;
            long long fullAns = 4LL * dp0 % MOD;

            while (ptr < (int)vec.size() && vec[ptr].first == m) {
                ans[vec[ptr].second] = (int)fullAns;
                ptr++;
            }

            // update stopFac for next m
            stop = stop * multStop % MOD;
        }

        dp1_prev.swap(dp1_cur);
        dp2_prev.swap(dp2_cur);
        dp3_prev.swap(dp3_cur);
        dp4_prev.swap(dp4_cur);
    }

    for (int i = 0; i < t; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
