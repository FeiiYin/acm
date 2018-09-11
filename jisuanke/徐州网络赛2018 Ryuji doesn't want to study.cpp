/*
 * @Samaritan_infi
 * 徐州网络赛2018 Ryuji doesn't want to study.cpp
 * 题意：单点修改，询问区间内所有前缀和的和。
 * 题解：用 BIT 维护 a[i] 以及 (n-i+1)*a[i] 的区间和，
 * 一次询问就是 (n-i+1)*a[i] 的区间和减去若干倍的 a[i] 的区间和
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1E5 + 100;
LL n, v[N];

namespace bit {
    LL cc[N], c[N];
    inline LL lowbit(LL x) { return x & -x; }
    void add(LL x, LL v) {
        for (LL i = x; i <= N; i += lowbit(i)) {
            cc[i] += (n + 1 - x) * v;
            c[i] += v;
        }
    }
    void add(LL l, LL r, LL v) { add(l, v); add(r + 1, -v); }
    LL sum(LL x, LL d) {
        LL ret = 0;
        for (LL i = x; i > 0; i -= lowbit(i))
            ret += cc[i] + c[i] * d;
        return ret;
    }
    LL query(LL l, LL r) {
        LL d = (r - l + 1) - (n + 1 - l);
        return sum(r, d) - sum(l - 1, d);
    }
}

int main() {
    int Q; cin >> n >> Q;
    for (int i = 1; i <= n; i ++) {
        LL t; scanf("%lld", &t);
        bit::add(i, t);
        v[i] = t;
    }
    while (Q--) {
        LL tp, a, b; scanf("%lld%lld%lld", &tp, &a, &b);
        if (tp == 2) {
            bit::add(a, b - v[a]);
            v[a] = b;
        } else {
            LL ans = bit::query(a, b);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
