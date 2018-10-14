/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e3 + 5;
const int mod = 1e9 + 7;

long long dp[2][20][N];
int stone[N];

struct node {
    int a, b;
    node () {}
    node (int a, int b) : a(a), b(b) {}
    bool operator < (const node & k) const {
        return b < k.b;
    }
};

priority_queue<node> pq;

void work (int n, int d) {

    int nim = 0;
    for (int i = 1; i <= n; ++i)
        nim ^= stone[i];

    dp[0][0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        int now = i & 1;
        dp[now][0][0] = 1;
        for (int j = 1; j <= d; ++j) {
            for (int k = 0; k < 1024; ++k)
                (dp[now][j][k] = (dp[now ^ 1][j][k] + dp[now ^ 1][j - 1][k ^ stone[i]])) %= mod;
        }
    }

    LL ans = 0;
    for (int i = 0; i <= d; ++i)
        (ans += dp[n & 1][i][nim]) %= mod;
    printf("%lld\n", ans);
}


int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
        memset(dp,0,sizeof(dp));
        int n, d;
        scanf("%d %d", &n, &d);
        for (int i = 1; i <= n; ++i) scanf("%d", &stone[i]);
        work(n, d);
    }
    return 0;
}
