/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e5 + 5;
#define PII pair<int, int>

/// Josephus
/// people from 0 to n - 1
/// ans[0] = 0
/// ans[i] = (ans[i-1] + jump) % num[i]
LL Josephus (LL n, LL k, LL start = 1) {
    if (k == 1)
        return (n - 1 + start) % n;
    LL ans = 0;
    for (LL i = 2; i <= n; ) {
        /// multi
        /// ans + m * k < i + (m - 1)
        /// m < (i - 1 - ans) / (k - 1)
        if (ans + k < i) {
            LL t = (i - 1 - ans) / (k - 1);
            if (t * (k - 1) == i - 1 - ans)
                t--;
            if (i + t > n) {
                ans = (ans + (n + 1 - i) * k + start) % n;
                return ans;
            }
            /// order cannot reverse since i has to be enlarge
            i += t;
            ans = (ans + t * k) % i;
        } else {
            ans = (ans + k) % i;
            ++i;
        }
    }
    return (ans + start) % n;
}

int main() {
    LL n, k;
    while (~ scanf("%lld %lld", &n, &k)) {
        LL ans = Josephus(n, k);
        printf("%lld\n", !ans ? n : ans);
    }
    return 0;
}
