/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;

vector<int> edge[N];

/// LCA
int pre[32][N]; /// Ancestor nodes
int dep[N];     /// depth of nodes

void dfs (int now, int pa) {
    pre[0][now] = pa;
    for (int e : edge[now]) if (e != pa) {
        dep[e] = dep[now] + 1;
        //dis[e.u] = dis[now] + e.val;
        dfs(e, now);
    }
}

void init_lca (int n) {
    dfs(1, -1); /// st, -1 根据起点标号dfs
    for (int k = 0; k < 20; k ++) {
        for (int v = 1; v <= n; v ++) {
            if (pre[k][v])
                pre[k + 1][v] = pre[k][ pre[k][v] ];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int k = 0; k < 20; k ++)
        if ((dep[v] - dep[u]) & (1 << k))
            v = pre[k][v];
    if (u == v) return u;
    for (int k = 19; k >= 0; k --) if (pre[k][u] != pre[k][v]) {
        u = pre[k][u];
        v = pre[k][v];
    }
    return pre[0][u];
}

int main () {
    int n; while (~ scanf("%d", &n)) {
        int l, r;
        for (int i = 1; i <= n; ++i) edge[i].clear();
        for (int i = 1; i < n; ++i) {
            scanf("%d %d", &l, &r);
            edge[l].push_back(r);
            edge[r].push_back(l);
        }
        init_lca(n);
        ll ans = 0; int k;
        for (int i = 1; i < n; ++i) {
            for (int j = i << 1; j <= n; j += i) {
                k = lca(i, j);
                ans = ans + dep[i] + dep[j] - (dep[k] << 1) + 1;
                //cout << k << endl;
                //cout << " ??? " << dep[i] << " " << dep[j] << " " << (dep[k] << 1) << endl;
                //cout << i << " " << j << " " << dep[i] + dep[j] - (dep[k] << 1) + 1 << endl;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
/*
6
1 2
2 3
3 4
4 5
5 6
*/
