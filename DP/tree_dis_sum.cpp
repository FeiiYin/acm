树上每个点到其他点距离和
二次换根
/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
#define PII pair<int, int>
#define fi first
#define se second
#define pb push_back

vector <PII> edge[N];


int dis[N], sum[N], siz[N];

void dfs (int x, int pre) {
    sum[x] = 0;
    siz[x] = 1;
    for (PII now : edge[x]) if (now.fi != pre) {
        dfs(now.fi, x);
        siz[x] += siz[now.fi];
        sum[x] += sum[now.fi] + now.se * siz[now.fi];
//        if (x == 1)
//            cout << sum[x] << " " << sum[now.fi] << " " << now.se << " " << siz[now.fi] << endl;
    }
}


void dfs2 (int x, int pre, int n) {
    for (PII now : edge[x]) if (now.fi != pre) {
        int to = now.fi;
        dis[to] = sum[to] + (dis[x] - sum[to] - now.se * siz[to])
                + (n - siz[to]) * now.se;
        dfs2(to, x, n);
    }
}

int main () {
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            edge[i].clear();

        int u, v, w;
        for (int i = 1; i < n; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            edge[u].pb({v, w});
            edge[v].pb({u, w});
        }

        dfs(1, -1);
        /// dis[rt] == sum[rt]
        dis[1] = sum[1];
        dfs2(1, -1, n);

        for (int i = 1; i <= n; ++i) {
            printf("%d ", sum[i]);
        } puts("");

        for (int i = 1; i <= n; ++i) {
            printf("%d ", dis[i]);
        } puts("");
    }
    return 0;
}

/*
2
2
1 2 1
5
1 2 1
2 3 1
2 4 1
4 5 2
*/
