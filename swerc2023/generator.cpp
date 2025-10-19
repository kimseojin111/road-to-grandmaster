#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1); // seed = 1

    // 입력 파라미터
    int n     = opt<int>(1); // 배열 크기
    int q     = opt<int>(2); // 쿼리 개수
    int maxA  = opt<int>(3); // a_i의 최대값

    assert(1 <= n && n <= 1000000);
    assert(1 <= q && q <= 1000000);
    assert(1 <= maxA && maxA <= n);

    // 배열 출력
    println(n);
    for (int i = 0; i < n; ++i) {
        int val = rnd.next(1, maxA);
        cout << val << " \n"[i == n - 1];
    }

    // 쿼리 출력
    println(q);
    for (int i = 0; i < q; ++i) {
        int l = rnd.next(1, n);
        int r = rnd.next(l, n); // l <= r
        println(l, r);
    }
}
