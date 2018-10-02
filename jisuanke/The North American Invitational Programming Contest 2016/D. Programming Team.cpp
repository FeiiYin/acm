/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3e3 + 5;
const double eps = 1e-5;
vector<int> edge[N];
int sal[N], pro[N], rec[N];

double dp[N][N], m;
int k, n;
int siz[N], dfn[N], tot, rev[N];
void init_dfs (int x) {
    siz[x] = 1;
    dfn[x] = ++tot;
    rev[tot] = x;
    for (int to : edge[x]) {
        init_dfs(to);
        siz[x] += siz[to];
    }
}

bool check (double m) {
    for (int i = 0; i <= k; ++i)
        dp[n + 2][i] = -10000000;
    dp[n + 2][0] = 0;
    dp[1][k] = -10000000;
//    cout << endl;
    for (int i = tot; i >= 1; --i) {
        int x = rev[i];
//        cout << x << endl;
        for (int p = 0; p <= k; p++) {
            if (p < 1) dp[i][p] = max(dp[i + siz[x]][p], 0.0);
            else
            dp[i][p] = max(dp[i+siz[x]][p], dp[i+1][p-1] + pro[x] - m * sal[x]);
        }
    }

//    for (int i = 1; i <= tot; i ++) {
//        for (int j = 0; j <= k; j++)
//            cout << dp[i][j] << " ";
//        cout << endl;
//    }
//    cout << dp[0][k] << endl;
//    cout << endl;
    return dp[1][k] > 0;
}

int main () {
    scanf("%d %d", &k, &n);
    k++;
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d", &sal[i], &pro[i], &rec[i]);
        edge[rec[i]].push_back(i);
    }
    tot = 0;
    init_dfs(0);
    double l = 0, r = k * 10000.0, mid;
    while (r - l > eps) {
        mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    if (check(r)) l = r;
    double ans = (long long)(l * 1000 + 0.5);
    ans = ans / 1000;
    printf("%.3f\n", ans);
    return 0;
}
/*
1 2
1000 1 0
1 1000 1
*/
