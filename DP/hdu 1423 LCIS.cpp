/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x7fffffff;

int num[2][N];
//int dp[N][N];
int dp[2][N];

int main () {
    int m, n, x, y;
    int kase; scanf("%d", &kase); while (kase--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &num[0][i]);
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i)
            scanf("%d", &num[1][i]);

        for (int i = 1; i <= n; ++i) {
            int pre_max = 0;
            for (int j = 1; j <= m; ++j) {
                /// dp[i][j] = dp[i-1][j];
                dp[i & 1][j] = dp[(i & 1) ^ 1][j];
                if (num[0][i] > num[1][j])
                    /// pre_max = max(pre_max, dp[i][j]);
                    pre_max = max(pre_max, dp[i & 1][j]);
                if (num[0][i] == num[1][j])
                    /// dp[i][j] = pre_max + 1;
                    dp[i & 1][j] = pre_max + 1;
            }
    //        for (int j = 1; j <= m; ++j)
    //            cout << dp[i & 1][j] << " "; cout << endl;
        }

    //    cout << endl;
    //    for (int i = 1; i <= 2; ++i) {
    //        for (int j = 1; j <= m; ++j)
    //            cout << dp[i][j] << " ";
    //        cout << endl;
    //    }

        int ans = 0, pre = INF, pos = -1;
        for (int i = 1; i <= m; ++i)
            ans = max(ans, dp[n & 1][i]);

    //    vector <int> output;
    //    while (true) {
    //        for (int i = m; i >= 1; --i) {
    //            if (dp[n & 1][i] == ans && num[1][i] < pre) {
    //                ans--;
    //                pre = num[1][i];
    //                output.push_back(num[1][i]);
    //                if (! ans)
    //                    break;
    //            }
    //        }
    //    }


        printf("%d\n", ans);
        memset(dp[0], 0, sizeof (int) * (m + 5));
        memset(dp[1], 0, sizeof (int) * (m + 5));

        if (kase) puts("");
    //    for (int i = output.size() - 1; i >= 1; --i)
    //        printf("%d ", output[i]);
    //    printf("%d\n", output[0]);
    }

    return 0;
}

/*
5
1 4 2 5 6
4
1 6 2 4
*/
