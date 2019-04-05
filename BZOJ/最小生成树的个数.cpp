/**
`* @Samaritan
 */
/// 最小生成树是可以按照边权由小到大求的，不同的方案中，每一个权值对应的边数仍应是相同的
/// 排序后，搜索即可，注意回溯需要拆分并查集，所以不能路径压缩

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define fi  first
#define se second

const int N = 1e2 + 5;
const int M = 1e3 + 5;
const int mod = 31011;

struct Edge {
    int u, v, val;
    Edge () {}
    Edge (int a, int b, int c)
    : u(a), v(b), val(c) {}
    bool operator < (const Edge &k) const {
        return val < k.val;
    }
};

struct Data {
    int l, r, val;
    Data () {}
    Data (int a, int b, int c)
    : l(a), r(b), val(c) {}
};

int par[N];
Edge edge[M];
Data data[M];
int find_par (int x) { return x == par[x] ? x : find_par(par[x]); }

/// 查看相同权值的边有多少个方案是等价的
/// x 原方案位置，now 枚举边的位置，
/// k 当前方案该权值的个数，sum统计方案数
void dfs (int x, int now, int k, int &sum) {
    if (now == data[x].r + 1) {
        if (k == data[x].val)
            sum++;
        return;
    }
    int p = find_par(edge[now].u), q = find_par(edge[now].v);
    if (p != q) {
        par[p] = q;
        dfs(x, now + 1, k + 1, sum);
        /// 由于这里回溯的时候需要分开联通快
        /// 采用路径压缩的话中间的块被合并了，再单独分开根就错误了
        par[p] = p;
        par[q] = q;
    }
    dfs(x, now + 1, k, sum);
}

int main () {
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) par[i] = i;
    for (int i = 1; i <= m; ++i)
        scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].val);
    sort (edge + 1, edge + m + 1);

    int pos = 0, temp = 0;
    for (int i = 1; i <= m; ++i) {
        if (edge[i].val != edge[i-1].val) {
            data[++pos].l = i;
            data[pos-1].r = i-1;
        }
        int x = find_par(edge[i].u), y = find_par(edge[i].v);
        if (x != y) {
            par[x] = y;
            data[pos].val++;
            temp++;
        }
    }
    data[pos].r = m;
    if (temp != n - 1) { puts("0"); return 0; }
    for (int i = 1; i <= n; ++i) par[i] = i;
    int ans = 1;
    for (int i = 1; i <= pos; ++i) {
        temp = 0;
        dfs(i, data[i].l, 0, temp);
        ans = (ans * temp) % mod;
        /// 把当前权值的父亲给标记上
        for (int j = data[i].l; j <= data[i].r; ++j) {
            int p = find_par(edge[j].u);
            int q = find_par(edge[j].v);
            if (p != q) par[p] = q;
        }
    }
    printf("%d\n", ans);
    return 0;
}
/*
4 6
1 2 1
1 3 1
1 4 1
2 3 2
2 4 1
3 4 1
*/
