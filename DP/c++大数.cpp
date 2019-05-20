/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 1e4 + 5;
#define PII pair<int, int>

struct node {
    int a[N];
    int n;
    bool nag;

    node () {
        memset(a, 0, sizeof a);
        n = 0;
        nag = false;
    }

    node (int x) {
        memset(a, 0, sizeof a);
        n = 0;
        nag = false;
        while (x) {
            a[n] = x % 10;
            n++;
            x /= 10;
        }
    }

    void init () {
        n = 1;
    }

    void show () {
        if (nag) printf("-");
        for (int i = n - 1; i >= 0; --i)
            printf("%d", a[i]);
        printf("\n");
    }

    node operator + (node & k) {
        node c;

        int tot = max(n, k.n);
        int tmp = 0;
        for (int i = 0; i < tot; ++i) {
            tmp += a[i] + k.a[i];
            c.a[i] = tmp % 10;
            tmp /= 10;
        }
        if (tmp) {
            c.a[tot] = tmp;
            c.n = tot+1;
        } else
            c.n = tot;
        return c;
    }
    /// has to be a > k
    node operator - (node & k) {
        node c;

        int tot = max(n, k.n);
        int tmp = 0, tuiwei = 0;
        for (int i = 0; i < tot; ++i) {
            tmp = a[i] - tuiwei - k.a[i];
            if (tmp < 0) {
                tmp += 10;
                tuiwei = 1;
            } else {
                tuiwei = 0;
            }
            c.a[i] = tmp;
        }
        c.n = tot;

        while (c.a[c.n-1] == 0 && c.n > 0) {
            c.n--;
        }
        if (c.n == 0) {
            c.n = 1;
        }
        return c;
    }

    node operator * (node & k) {
        node c;
        for (int i = 0; i < n; ++i) {
            int tmp = 0;
            for (int j = 0; j < k.n; ++j) {
                c.a[i + j] += a[i] * k.a[j] + tmp;
                tmp = c.a[i + j] / 10;
                c.a[i + j] %= 10;
            }
            c.a[k.n + i] += tmp;
        }
        c.n = n + k.n;
        while (c.a[c.n-1] == 0 && c.n > 0)
            c.n--;
        if (c.n == 0)
            c.n = 1;
        return c;
    }
};

node arr[1005];
int main() {
    LL a, b;
    node one(1), two(2);
    arr[1].init();
    for (int i = 2; i <= 1000; ++i) {
        if (i & 1)
            arr[i] = arr[i-1] * two - one;
        else
            arr[i] = arr[i-1] * two + one;
    }
    while (~ scanf("%d", &a)) {
        /// odd f[i] = f[i-1] * 2 - 1
        /// even f[i] = f[i-1] * 2 + 1
        /// f[1] = 0
        arr[a].show();
    }
    return 0;
}
