/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 9e4 + 5;
const int mod = 1e9 + 9;

#define PII pair<int, int>
#define fi first
#define se second

struct node {
    int a, b, c, d, type;
    node () {}
    node (int a, int b, int c, int d)
        : a(a), b(b), c(c), d(d) {
//        if (b == d) type = 1; // shu
//        else type = 2; // heng
    }
};
node arr[N];

bool vis[10][10005];
PII link[10][10005];

int dx[] = {-1, 1, 0,  0};
int dy[] = {0,  0, 1, -1};

void work (int n, int m) {
    PII st, now;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (! vis[i][j]) {
                st = PII(i, j);
                break;
            }
    memset(vis, 0, sizeof vis);
    queue<PII> pq;
    pq.push(st);
    LL ans = 0;
    while (! pq.empty()) {
        now = pq.front(); pq.pop();
        int x = now.fi, y = now.se;
        //cout << x << " " << y << endl;
        for (int i = 0; i < 4; ++i) {
            int xx = x + dx[i], yy = y + dy[i];
            int a = link[xx][yy].fi, b = link[xx][yy].se;

            if (x == xx && xx == a && ! vis[a][b]) { // heng
                vis[a][b] = true;
                pq.push(PII(a, b));
                ans++;
            } else if (y == yy && yy == b && ! vis[a][b]) { // shu
                vis[a][b] = true;
                pq.push(PII(a, b));
                ans++;
            }
        }
        ans %= mod;
    }
    printf("%lld\n", ans);
}


int main () {
//    int kase; scanf("%d", &kase);
    int n, m, k;
    while (~ scanf("%d %d %d", &n, &m, &k)) {
        memset(link, 0, sizeof link);
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= k; ++i) {
            scanf("%d %d %d %d", &arr[i].a, &arr[i].b, &arr[i].c, &arr[i].d);
            link[ arr[i].a ][ arr[i].b ] = PII(arr[i].c, arr[i].d);
            link[ arr[i].c ][ arr[i].d ] = PII(arr[i].a, arr[i].b);
            vis[ arr[i].c ][ arr[i].d ] = vis[ arr[i].a ][ arr[i].b ] = true;
        }
        work(n, m);
    }
    return 0;
}
