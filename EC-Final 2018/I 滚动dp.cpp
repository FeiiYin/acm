/**
`* @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define fi  first
#define se second

const int N = 101, M = 5051;
LL dp[2][N][M];
LL a[N], b[N], c[N];
/// EC-Final 2018 I : https://codeforces.com/gym/102056/problem/I
/// d: base attack value; x: accumulate value
/// ai: attack at i th round with ai + d
/// bi: x += bi
/// ci: d += ci
/// every round after d += x
/// i round, j attack time after, k attack time after sum
/// last must fight
/// dp[n][1][n] = an
/// ai: dp[i][j][k] + ai -> dp[i-1][j+1][k+i]
/// bi: dp[i][j][k] + (k-j*i)*bi -> dp[i-1][j][k]  |: sum(time - i)*bi
/// ci: dp[i][j][k] + ci*j -> dp[i-1][j][k]

int main(){
    int kase; scanf("%d", &kase);
    while (kase--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
        }
        memset(dp, 0, sizeof dp);
        dp[n&1][1][n] = a[n];

        for (int i = n; i >= 1; --i) {
            int last = i&1, now = last^1;
            for (int j = 0; j <= n-i; ++j) {
                int down = (i + i + j - 1) * j / 2, up = (n + n - j + 1) * j / 2;
                for (int k = down; k <= up; ++k) {
                    dp[now][j+1][k+i] = max(dp[now][j+1][k+i], dp[last][j][k] + a[i]);
                    dp[now][j][k] = max(dp[now][j][k], dp[last][j][k] + (k-j*i)*b[i]);
                    dp[now][j][k] = max(dp[now][j][k], dp[last][j][k] + j*c[i]);
                }
            }
            memset(dp[last], 0, sizeof dp[last]);
        }
        LL ans = 0;

        int up = (1+n)*n/2;
        for (int k = 0; k < 2; ++k) for (int i = 1; i <= n; ++i) for (int j = 1; j <= up; ++j)
            ans = max(ans, dp[k][i][j]);
        printf("%lld\n", ans);
    }
    return 0;
}
