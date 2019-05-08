/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e6 + 5;
const int INF = 0x7fffffff;

/**
 * dp[i][j] : 取前j个数（必取第j个数） 分成 i 段的最大值
 * dp[i][j] = max(dp[i][j-1] + num[j], dp[i-1][k] + num[j])
 * 滚动优化
 */

int num[N];
int dp[N], pre[N];

int main () {
    int m, n, x, y;
    while (~ scanf("%d %d", &m, &n)) {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &num[i]);

        int pre_max;
        for (int i = 1; i <= m; ++i) {
            pre_max = -INF;
            for (int j = i; j <= n; ++j) { /// start from i, very important
                dp[j] = max(dp[j-1], pre[j-1]) + num[j];
                pre[j-1] = pre_max;
                pre_max = max(pre_max, dp[j]);
            }
        }
        printf("%d\n", pre_max);


        memset(dp, 0, sizeof (int) * (n + 5));
        memset(pre, 0, sizeof (int) * (n + 5));
    }
    return 0;
}
