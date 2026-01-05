#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int N = 16000010;
constexpr int MAX_PRIMES = 1300000; // 적절한 여유값, psum 최대 인덱스 확보

constexpr array<ll, N> generate_primes() {
    array<ll, N> is_prime{};
    for (int i = 2; i < N; i++) is_prime[i] = 1;
    for (int i = 2; i * 2 < N; ++i) {
        if (is_prime[i]) {
            for (int j = i * 2; j < N; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    return is_prime;
}

constexpr array<ll, MAX_PRIMES> generate_psum(const array<ll, N>& is_prime) {
    array<ll, MAX_PRIMES> psum{};
    int f = 1;
    for (int i = 2; i < N; ++i) {
        if (is_prime[i]) {
            psum[f] = psum[f - 1] + i;
            ++f;
        }
    }
    return psum;
}

// 컴파일 타임에 prime, psum 생성
constexpr auto PRIME = generate_primes();
constexpr auto PSUM = generate_psum(PRIME);

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    sort(a.begin(), a.end());
    ll sum = accumulate(a.begin(), a.end(), 0LL);
    for (int i = 0; i < n; ++i) {
        if (sum >= PSUM[n - i]) {
            cout << i << '\n';
            return;
        }
        sum -= a[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
