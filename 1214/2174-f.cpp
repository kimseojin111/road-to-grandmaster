#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

long long mod_pow(long long a, long long e) {
    a %= MOD;
    if (a < 0) a += MOD;
    long long r = 1;
    while (e > 0) {
        if (e & 1LL) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1LL;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> cnt(m + 1, 0);
        for (int i = 0; i < n; i++) {
            int c;
            cin >> c;
            cnt[c]++;
        }

        vector<int> mask(m + 1, 0);
        for (int i = 1; i <= m; i++) cin >> mask[i];

        // Special case n == 1
        if (n == 1) {
            bool ok = true;
            for (int i = 1; i <= m; i++) {
                if (mask[i] != 0) { ok = false; break; }
            }
            cout << (ok ? 1 : 0) << "\n";
            continue;
        }

        int L = n - 2;

        // dp[t] = A_t coefficients of G(x)
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        int max_sum = 0;
        int m_eff = 0;
        bool impossible = false;

        for (int i = 1; i <= m; i++) {
            int s = cnt[i];
            if (s == 0) {
                // total degree of an unused color is 0 (even) => mask must be 0
                if (mask[i] == 1) {
                    impossible = true;
                    break;
                }
                continue;
            }

            int r = mask[i] ^ (s & 1);   // required parity of occurrences in Prüfer code
            // b = (-1)^r : if r==0 -> +1, if r==1 -> -1
            bool neg = (r == 1);

            m_eff++;
            max_sum += s;

            // Multiply by (1 + b x^s)
            // descending loop to avoid overwriting needed dp[t-s]
            for (int t = max_sum; t >= s; --t) {
                if (!neg) {
                    dp[t] += dp[t - s];
                    if (dp[t] >= MOD) dp[t] -= MOD;
                } else {
                    dp[t] -= dp[t - s];
                    if (dp[t] < 0) dp[t] += MOD;
                }
            }
        }

        if (impossible) {
            cout << 0 << "\n";
            continue;
        }

        long long total = 0;
        for (int tSum = 0; tSum <= n; tSum++) {
            long long base = (long long)n - 2LL * tSum; // can be negative
            long long pw = mod_pow(base, L);
            total = (total + dp[tSum] * pw) % MOD;
        }

        long long inv2 = (MOD + 1) / 2;              // inverse of 2 mod MOD
        long long factor = mod_pow(inv2, m_eff);     // 2^{-m_eff}
        long long ans = (total * factor) % MOD;

        cout << ans << "\n";
    }
    return 0;
}
