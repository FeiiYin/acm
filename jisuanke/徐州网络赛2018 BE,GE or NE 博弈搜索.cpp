/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e3 + 5;
int a[N], b[N], c[N];
int dp[N][300];

int n;
const int offset = 100;
int dfs (int turn, int score) {
    //cout << turn << " " << score << endl;
    if (turn > n) return score;
    if (dp[turn][score] != -1) return dp[turn][score];
    int ans;
    if (turn & 1) { /// K player max
        ans = 0;
        if (a[turn])
            ans = max(ans, dfs(turn + 1, min(offset << 1, score + a[turn])));
        if (b[turn])
            ans = max(ans, dfs(turn + 1, max(0, score - b[turn])));
        if (c[turn])
            ans = max(ans, dfs(turn + 1, 200 - score));
    } else {        /// S player min
        ans = 200;
        if (a[turn])
            ans = min(ans, dfs(turn + 1, min(offset << 1, score + a[turn])));
        if (b[turn])
            ans = min(ans, dfs(turn + 1, max(0, score - b[turn])));
        if (c[turn])
            ans = min(ans, dfs(turn + 1, 200 - score));
    }
    //cout << "out  " << turn << "  " << ans << endl;
    dp[turn][score] = ans;
    return ans;
}

int main () {
    int m, up, low;
    scanf("%d %d %d %d", &n, &m, &up, &low);
    for (int i = 1; i <= n; i ++)
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
    memset(dp, -1, sizeof dp);
    m += offset, up += offset, low += offset;
    int ans = dfs(1, m);
    if(ans >= up)       puts("Good Ending");
    else if(ans <= low) puts("Bad Ending");
    else                puts("Normal Ending");
    return 0;
}
