#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Seg {
    int n;
    vector<ll> t;
    Seg() : n(0) {}
    Seg(const vector<ll>& a) { build(a); }
    void build(const vector<ll>& a) {
        int m = (int)a.size();
        n = 1;
        while (n < m) n <<= 1;
        t.assign(2*n, LLONG_MIN);
        for (int i = 0; i < m; ++i) t[n+i] = a[i];
        for (int i = n-1; i >= 1; --i) t[i] = max(t[i<<1], t[i<<1|1]);
    }
    void point_update(int idx, ll val) { // 0-based idx
        int p = n + idx;
        t[p] = val;
        for (p >>= 1; p >= 1; p >>= 1) t[p] = max(t[p<<1], t[p<<1|1]);
    }
    ll all_max() const { return t[1]; }
};

static const int N = 200010;
ll a[N];

static inline vector<int> distinct_primes(int n) {
    vector<int> primes;
    for (int p = 2; 1LL*p*p <= n; ++p) {
        if (n % p == 0) {
            primes.push_back(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) primes.push_back(n);
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, q; 
        cin >> n >> q;
        for (int i = 1; i <= n; ++i) cin >> a[i];

        // factors of n → use p[j] = n / prime
        vector<int> primes = distinct_primes(n);
        vector<int> p; p.reserve(primes.size());
        for (int pr : primes) p.push_back(n / pr);

        // sums[j][r] : r in [0, p[j)-1]
        int P = (int)p.size();
        vector<vector<ll>> sums(P);
        for (int j = 0; j < P; ++j) {
            sums[j].assign(p[j], 0);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < P; ++j) {
                int r = i % p[j];
                sums[j][r] += a[i];
            }
        }

        // one segment tree per j to keep max over residues
        vector<Seg> seg(P);
        for (int j = 0; j < P; ++j) seg[j].build(sums[j]);

        auto current_answer = [&]() -> ll {
            ll mx = -1;
            for (int j = 0; j < P; ++j) {
                mx = max(mx, 1LL * p[j] * seg[j].all_max());
            }
            return mx;
        };

        cout << current_answer() << '\n';

        while (q--) {
            int idx; ll x; 
            cin >> idx >> x;
            ll delta = x - a[idx];
            if (delta != 0) {
                for (int j = 0; j < P; ++j) {
                    int r = idx % p[j];
                    sums[j][r] += delta;
                    seg[j].point_update(r, sums[j][r]);
                }
                a[idx] = x;
            }
            cout << current_answer() << '\n';
        }
    }
    return 0;
}