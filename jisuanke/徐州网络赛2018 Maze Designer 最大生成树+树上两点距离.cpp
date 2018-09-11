/*
 * @Samaritan_infi
 * 计算课 徐州网络赛2018 Maze Designer 最大生成树+树上两点距离.cpp
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3e5 + 5;
struct Edge {
    int u, v, val;
    Edge () {}
    Edge (int a, int b, int c) {
        u = a; v = b; val = c;
    }
    bool operator < (const Edge & k) const {
        return val < k.val;
    }
};

priority_queue<Edge> pq;
int par[N];

int find_par(int x) {
    if (x == par[x]) return x;
    return par[x] = find_par(par[x]);
}

bool unite (int x, int y) {
    int a = find_par(x), b = find_par(y);
    if (a == b) return false;
    par[a] = b;
    return true;
}

vector<int> tree[N];

void work_on_max_tree(int n, int m) {
    for (int i = 0; i <= n * m; i ++)
        par[i] = i;
    Edge e;
    int edge_num = 0, point = n * m - 1;
    while (! pq.empty()) {
        e = pq.top(); pq.pop();
        if (unite(e.u, e.v)) {
            tree[e.u].push_back(e.v);
            tree[e.v].push_back(e.u);
            edge_num ++;
            if (edge_num >= point) break;
        }
    }

}

/// LCA
int pre[32][N]; /// Ancestor nodes
int dep[N];     /// depth of nodes

void dfs (int now, int pa) {
    pre[0][now] = pa;
    for (int to : tree[now]) if (to != pa) {
        dep[to] = dep[now] + 1;
        dfs(to, now);
    }
}

void init_lca (int n) {
    dfs(0, -1);
    for (int k = 0; k < 20; k ++) {
        for (int v = 0; v < n; v ++) {
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
    int n, m; scanf("%d %d", &n, &m);
    char op1[5], op2[5];
    int x, y, u, v;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            scanf("%s %d %s %d", op1, &x, op2, &y);
            u = i * m + j;
            if (op1[0] == 'D') {
                v = (i + 1) * m + j;
                pq.push(Edge(u, v, x));
            }
            if (op2[0] == 'R') {
                v = i * m + j + 1;
                pq.push(Edge(u, v, y));
            }
        }
    }
    work_on_max_tree(n, m);
    init_lca(n * m);
    int query; scanf("%d", &query);
    while (query --) {
        scanf("%d %d %d %d", &x, &y, &u, &v);
        x --, y --, u --, v --;
        x = x * m + y;
        y = u * m + v;
        int k = lca(x, y);
        /// 树上两点距离
        printf("%d\n", dep[x] + dep[y] - 2 * dep[k]);
    }
    return 0;
}
