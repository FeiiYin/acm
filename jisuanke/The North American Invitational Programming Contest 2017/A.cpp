/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 3e2 + 5;
const int INF = 10000000;
char s[N];


struct node {
    int x, y, len, type, cmp;
    node () {}
    node (int a, int b, int d) {
        x = a; y = b; len = d;
        if (b >= 0) type = 1, cmp = -x;
        else type = 0, cmp = y - x;
    }
    bool operator < (const node &k) const {
        if (type != k.type) return type > k.type; /// first ((
        if (type == 1) return cmp < k.cmp;
        else return cmp > k.cmp;
    }
};
int val[N], dp[N * N], cpy[N * N];
node a[N];

int main () {
    int n;
    while (~ scanf("%d", &n)) {
        int len, x, y, pre, apos = 0, bpos = 0;
        int tot_len = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            len = strlen(s);
            tot_len += len;
            x = pre = 0;
            for (int j = 0; j < len; ++j) {
                if (s[j] == '(') ++x;
                else x--, pre = min(pre, x);
            }
            a[apos++] = node(pre, x, len);
        }
        for (int i = 1; i <= tot_len; ++i)
            cpy[i] = - INF;
        cpy[0] = 0;

        sort (a, a + apos);

        for (int i = 0; i < apos; ++i) {
            for (int j = 0; j <= tot_len; ++j)
                dp[j] =  cpy[j];
            for (int j = 0; j <= tot_len; ++j)
                if (j + a[i].x >= 0 && cpy[j] >= 0) {
                    dp[ j + a[i].y ] = max (dp[ j + a[i].y ], cpy[j] + a[i].len);
                }
            for (int j = 0; j <= tot_len; ++j)
                cpy[j] =  dp[j];
        }

        //for (int i = 0; i < tot_len; ++i) cout << dp[i] << " "; cout << endl;
        printf("%d\n", dp[0]);
    }
    return 0;
}
/*
4
))
((
(
)(
*/
