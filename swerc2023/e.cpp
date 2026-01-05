#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define fi first
#define se second
#define eb emplace_back
#define all(v) (v).begin(),(v).end()

int N;
vector<ll> H;
vector<ll> hs;
vector<int> seg;

ll mgcd(ll x, ll y) { return x % y == 0 ? y : mgcd(y, x % y); }

pll fmax(pll x, pll y) {
    __int128 a = (__int128)x.fi * y.se, b = (__int128)x.se * y.fi;
    return a > b ? x : y;
}

int lb(ll x) { return lower_bound(all(hs), x) - hs.begin(); }

void updseg(int idx, int l, int r, int x, int y, int z) {
    if(x <= l && r <= y) seg[idx] = z;
    else if(x <= r && l <= y) {
        int m = (l + r) / 2;
        updseg(idx * 2, l, m, x, y, z);
        updseg(idx * 2 + 1, m + 1, r, x, y, z);
    }
}

int gseg(int idx, int l, int r, int x) {
    if(l == r) return seg[idx];
    int m = (l + r) / 2;
    if(x <= m) return max(seg[idx], gseg(idx * 2, l, m, x));
    else return max(seg[idx], gseg(idx * 2 + 1, m + 1, r, x));
}

pll solve() {
    seg.clear();
    seg.resize(4 * N, -1);
    pll ans = pll(0, 1);

    for(int i = 1; i < N; i++) {
        if(H[i] < H[i - 1]) {
            int a = lb(H[i - 1]), b = lb(H[i]);
            updseg(1, 0, N - 1, b + 1, a, i);
        }
        else {
            int z = gseg(1, 0, N - 1, lb(H[i]));
            if(z >= 0) {
                ll k = i - z, a = H[i] - H[z], b = H[z - 1] - H[z];
                ll g = mgcd(a, b);
                a /= g; b /= g;
                ans = max(ans, pll(k * b + a, b));
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N;
    H.resize(N);
    for(int i = 0; i < N; i++) cin >> H[i];

    for(int i = 0; i < N; i++) hs.eb(H[i]);
    sort(all(hs));

    pll ans = solve();
    for(int i = 0; i < N / 2; i++) swap(H[i], H[N - i - 1]);
    ans = fmax(ans, solve());

    if(ans.se == 1) cout << ans.fi << "\n";
    else cout << ans.fi << "/" << ans.se << "\n";
    return 0;
}