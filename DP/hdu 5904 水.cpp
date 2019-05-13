/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5 + 5;
const int M = 1e6 + 5;

int arr[N], brr[N];
int dp[2][M];

int main() {
	int n, m, kase;	scanf("%d", &kase);
	while (kase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);
        for (int i = 0; i < m; ++i)
            scanf("%d", &brr[i]);

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            dp[0][ arr[i] ] = dp[0][ arr[i] - 1 ] + 1;
        }
        for (int i = 0; i < m; ++i) {
            dp[1][ brr[i] ] = dp[1][ brr[i] - 1 ] + 1;
            /// not dp[0] == dp[1]
            /// if dp[0] -> 0, 1, 2, 3, 4, dp[1] -> 2, 3, 4
            /// so ans = min(dp[0], dp[1])
            ans = max(ans, min(dp[0][ brr[i] ], dp[1][ brr[i] ]));
        }
        for (int i = 0; i < n; ++i)
            dp[0][ arr[i] ] = 0;
        for (int i = 0; i < m; ++i)
            dp[1][ brr[i] ] = 0;
        printf("%d\n", ans);
	}
	return 0;
}
