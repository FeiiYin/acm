/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N = 4e5 + 5;

vector<int> child[N];
int fa[N], son[N], dep[N], dfn[N], sz[N], top[N], cnt;

/// 搜索 深度，子树大小，重儿子
void dfs1 (int now) {
    sz[now] = 1; dep[now] = dep[ fa[now] ] + 1;
    for (int to : child[now]) {
        dfs1(to);
        sz[now] += sz[to];
        if (sz[to] > sz[ son[now] ])
            son[now] = to;
    }
}
/// 搜索 dfs 标号(优先重儿子)，以及自己所在链的顶端结点
void dfs2 (int now) {
    dfn[now] = ++ cnt;
    if (now == son[ fa[now] ]) top[now] = top[ fa[now] ];
    else top[now] = now;
    if (son[now]) dfs2(son[now]);
    for (int to : child[now]) if (to != son[now])
        dfs2(to);
}

/// 线段树维护结点, unsigned 用于自然溢出
unsigned long long sum[N], mul[N], add[N];
#define lson node<<1
#define rson node<<1|1
inline void push_up (int node) {
    sum[node] = sum[node << 1] + sum[node << 1 | 1];
}

void push_down (int node, int len) {
    if (mul[node] != 1) {
        mul[lson] *= mul[node];
        add[lson] *= mul[node];
        mul[rson] *= mul[node];
        add[rson] *= mul[node];

        sum[lson] *= mul[node];
        sum[rson] *= mul[node];
        mul[node] = 1;
    }
    if (add[node]) {
        add[lson] += add[node];
        add[rson] += add[node];
        sum[lson] += (len - (len >> 1)) * add[node];
        sum[rson] += (len >> 1) * add[node];
        add[node] = 0;
    }
}

void build (int node, int l, int r) {
    mul[node] = 1; add[node] = sum[node] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    /// push_up initially all 0 do not need
}

void update (int node, int l, int r, int L, int R, ULL to_mul, ULL to_add) {
    if (L <= l && r <= R) {
        mul[node] *= to_mul;
        add[node] *= to_mul;
        add[node] += to_add;

        sum[node] *= to_mul;
        sum[node] += to_add * (r - l + 1);
        return;
    }
    push_down(node, r - l + 1);
    int mid = (l + r) >> 1;
    if (L <= mid) update(lson, l, mid, L, R, to_mul, to_add);
    if (R > mid) update(rson, mid + 1, r, L, R, to_mul, to_add);
    push_up(node);
}

ULL query (int node, int l, int r, int L, int R) {
    if (L <= l && r <= R) return sum[node];
    push_down(node, r - l + 1);
    int mid = (l + r) >> 1;
    ULL ans = 0;
    if (L <= mid) ans += query(lson, l, mid, L, R);
    if (R > mid) ans += query(rson, mid + 1, r, L, R);
    return ans;
}

int n; /// 原树顶点
/// 树链剖分
void update_path (int x, int y, ULL to_mul, ULL to_add) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        update(1, 1, n, dfn[top[x]], dfn[x], to_mul, to_add);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap (x, y);
    /// 深度低的，dfn也低
    update(1, 1, n, dfn[x], dfn[y], to_mul, to_add);
}

ULL query_path (int x, int y) {
    ULL ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap (x, y);
        ans += query(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap (x, y);
    ans += query(1, 1, n, dfn[x], dfn[y]);
    return ans;
}

inline void input (int n) {
    memset(son, 0, sizeof (int) * (n + 2));
    for (int i = 1; i <= n + 1; i ++)
        child[i].clear();
    int x;
    for (int i = 1; i < n; i ++) {
        scanf("%d", &x);
        fa[i + 1] = x;
        child[x].push_back(i + 1);
    }
    son[0] = -1;
    cnt = 0;
}

int main () {
    int m;
    while (~ scanf("%d", &n)) {
        input(n);
        dfs1 (1);
        dfs2 (1);
        build(1, 1, n);
        scanf("%d", &m);
        int op, u, v; ULL x;
        while (m --) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d %d %llu", &u, &v, &x);
                update_path(u, v, x, 0);
            } else if (op == 2) {
                scanf("%d %d %llu", &u, &v, &x);
                update_path(u, v, 1, x);
            } else if (op == 3) {
                scanf("%d %d", &u, &v);
                update_path(u, v, -1, -1);
            } else {
                scanf("%d %d", &u, &v);
                printf("%llu\n", query_path(u, v));
            }
        }
    }
    return 0;
}
