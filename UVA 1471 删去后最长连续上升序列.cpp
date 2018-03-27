/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;
const int inf = 0x3f3f3f3f;
int save[maxn];
int f[maxn]; ///数组向右延伸的最长距离
int g[maxn]; ///数组向左延伸的最长距离
int dp[maxn];

int main() {
    int kase; scanf("%d" , &kase);
    while(kase --) {
        int n; scanf("%d" , &n);
        for(int i = 1; i <= n; i ++)
            scanf("%d", &save[i]);

        f[1] = 1;
        for(int i = 2; i <= n; i ++)
            if(save[i] > save[i - 1])
                f[i] = f[i - 1] + 1;
            else
                f[i] = 1;

        g[n] = 1;
        for(int i = n - 1; i > 0; i --)
            if(save[i] < save[i + 1])
                g[i] = g[i + 1] + 1;
            else
                g[i] = 1;

        int ans = 0;
        memset(dp, inf, sizeof dp);
        for(int i = 1; i <= n; i ++) {
            ///二分查找到比当前值小的那个的最大的前面的值
            int len = (lower_bound(dp + 1, dp + 1 + i, save[i]) - (dp + 1)) + g[i];
            ans = max(len, ans);
            dp[f[i]] = min(save[i], dp[f[i]]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
