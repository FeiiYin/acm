/// 按照 x 坐标升序排列
/// 定义 dp[i][k] 表示第一个人走到第 i 个点第二个人走到第 k 个点的最短距离
/// 更新即可
/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
#include <stack>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;
const int M = 1e4 + 5;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

int x[N], y[N], id[N], re[N];
double dis[N][N];

bool cmp (int i, int j) {
    return x[i] < x[j];
}

inline double cal_dis(int i, int j) {
    return sqrt(1.0*(x[i]-x[j])*(x[i]-x[j])+1.0*(y[i]-y[j])*(y[i]-y[j]));
}
/// dp[i][j] :
double dp[N][N];

int main () {
    int n;
    while (~ scanf("%d", &n)) {
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &x[i], &y[i]);
            id[i] = i;
        }
        sort (id, id + n, cmp);
        for (int i = 0; i < n; ++i)
            re[ id[i] ] = i;
        for (int i = 0; i < n; ++i) {
            dis[i][i] = 0;
            for (int j = 0; j < i; ++j)
                dis[i][j] = dis[j][i] = cal_dis(re[i], re[j]);
        }

        /// memset is not valid for double
        /// memset(dp, INF, sizeof dp);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                dp[i][j] = 99999999.0;
        }
        dp[0][0] = 0;
        /// dp[i][j] = dp[j][i]
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i][j] = min(dp[i][j], dp[i-1][j] + dis[i][i-1]);
                /// dp[i][i-1] = min(dp[j][i-1] + dis[j][i])
                dp[i][i-1] = min(dp[i][i-1], dp[i-1][j] + dis[j][i]);
            }
        }

        printf("%.2f\n", dp[n-1][n-2] + dis[n-1][n-2]);
    }
    return 0;
}
