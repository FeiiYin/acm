/*
 * @Samaritan_infi
 */
/// 题意: 给出一颗树, 树的点和边都有权值，对于每个点，选出一条路径，路径值为起点和终点权的乘积和路径权的和
///      使每个点的路径值最小，求所有点的路径值的和
/// 题解: 树的点分治，两个点如果在不同子树，路径和为两个点到当前重心的路径权和，如果在相同子树，分治递归
///      对于枚举的点通过　排序后求下凸包来处理。
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e5 + 5;
const long long INF = 1e16;
struct Edge {
    int to, val, next, ok;
    Edge () {}
    Edge (int a, int b, int c) : to(a), val(b), next(c) {ok = 1;}
};
Edge edge[N << 1]; int head[N], edge_num;
inline void edge_init () {
    memset(head, -1, sizeof head);
    edge_num = -1;
}
inline void add_edge (int u, int v, int w) {
    edge[++edge_num] = Edge(v, w, head[u]);
    head[u] = edge_num;
    edge[++edge_num] = Edge(u, w, head[v]);
    head[v] = edge_num;
}
/// 树分治
int all, now_root, siz[N], top_siz[N]; /// 当前: 剩余总顶点，当前重心，子树大小，最大子树大小
void find_root (int x, int pre) {
    siz[x] = 1; top_siz[x] = 0;
    for (int i = head[x]; ~i; i = edge[i].next) if (edge[i].ok && edge[i].to != pre) {
        find_root(edge[i].to, x);
        siz[x] += siz[edge[i].to];
        if (siz[edge[i].to] > top_siz[x]) top_siz[x] = siz[edge[i].to];
    }
    top_siz[x] = max(top_siz[x], all - top_siz[x]);
    if (top_siz[x] < top_siz[now_root]) now_root = x;
}

struct node {
    LL point, path; /// val
    node () {}
    node (LL a, LL b) {point = a, path = b;}
    bool operator < (const node & b) const {
        if (point == b.point) return path < b.path;
        return point > b.point;
    }
} A[N], temp[N];
int B[N], node_num;
int point_val[N];LL ans[N], path_val[N]; /// 点权, 最小值, 点到当前根的路径长度

inline bool cmp_by_point_val (int x, int y) {
    return point_val[x] < point_val[y];
}

void dfs (int x, int pre, LL path) {
    ++node_num;
    A[node_num] = node(point_val[x], path);
    B[node_num] = x;
    path_val[x] = path;
    for (int i = head[x]; ~i; i = edge[i].next)
        if (edge[i].ok && edge[i].to != pre)
            dfs(edge[i].to, x, path + edge[i].val);
}
inline double cal_pos (const node a, const node b) {
    return ((double)(b.path - a.path))/((double)(a.point-b.point));
}
inline LL cal (int x, int y) {
    return temp[y].point * point_val[x] + path_val[x] + temp[y].path;
}
void solve (int now) {
    node_num = 0;
    dfs (now, -1, 0);
    sort (A + 1, A + 1 + node_num);
    sort (B + 1, B + 1 + node_num, cmp_by_point_val);
    int temp_num = 1;
    temp[temp_num] = A[1];
    /// 凸包
    for (int i = 2; i <= node_num; ++i) if (A[i].point != A[i - 1].point) {
        while (temp_num > 1 && cal_pos(temp[temp_num - 1], temp[temp_num]) > cal_pos(temp[temp_num], A[i]))
            temp_num--;
        temp[++temp_num] = A[i];
    }
    for (int i = 1, cur = 1; i <= node_num; ++i) {
        while (cur < temp_num && cal(B[i], cur) > cal(B[i], cur + 1)) cur++;
        ans[B[i]] = min(ans[B[i]], cal(B[i], cur));
    }
    for (int i = head[now]; ~i; i = edge[i].next) if (edge[i].ok) {
        edge[i ^ 1].ok = 0;
        all = siz[ edge[i].to ];
        top_siz[0] = all + 1;
        find_root(edge[i].to, now_root = 0);
        solve(now_root);
    }
}

int main () {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &point_val[i]);
    int u, v, w;
    edge_init();
    for (int i = 1; i < n; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }
    for (int i = 1; i <= n; ++i) ans[i] = INF;
    top_siz[0] = all = n;
    find_root(1, now_root = 0);
    solve(now_root);
    LL output = 0;
    for (int i = 1; i <= n; ++i) output += ans[i];
    printf("%lld\n", output);
    return 0;
}
