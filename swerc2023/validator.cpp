#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate n
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // Read and validate array a of size n
    for (int i = 0; i < n; i++) {
        int ai = inf.readInt(1, n, "a_i");
        if (i < n - 1) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // Read and validate q
    int q = inf.readInt(1, 1000000, "q");
    inf.readEoln();

    // Read and validate each query
    for (int i = 0; i < q; i++) {
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(1, n, "r");
        ensuref(l <= r, "Query l and r should satisfy l <= r");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}