/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;

int num[N];
int pre[N];
int dp[N][N];

int main () {
    int m, n;
    while (~ scanf("%d %d", &m, &n)) {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &num[i]);

        /// 恰好分成 m 段，使最大的段最小，注意全负

        /// dp[i][j] = for (k from 1 to i - 1) min( max(dp[k][j-1], sum(k+1 to i)) )
        for (int i = 1; i <= n; ++i)
            dp[i][1] = pre[i] = pre[i-1] + num[i];

        for (int i = 1; i <= n; ++i) cout << dp[i][1] << " "; cout << endl;

        for (int j = 2; j <= m; ++j)
            // previous at most into i
            for (int i = j; i <= n; ++i) {
                dp[i][j] = INF;
                for (int k = j-1; k < i; ++k) {
                    int tmp = max(dp[k][j-1], pre[i] - pre[k]);
                    dp[i][j] = min(dp[i][j], tmp);
                }
            }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j)
                cout << dp[j][i] << " ";
            cout << endl;
        }
    }
    return 0;
}

/*
5 5
1 3 -3 3 1
5 5
-1 -1 -1 -1 -1
*/
