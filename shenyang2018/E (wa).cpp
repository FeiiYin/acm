/*
 * @Samaritan_infi
 */
/// 题意:
/// 题解:
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 5;
const LL INF = 1e15 + 1;
struct node {
    LL x, y, clan;
    node () {}
    node (LL _x, LL _y, LL _clan) : x(_x), y(_y), clan(_clan) {}
};
node ninja[N];
LL ori_x[N], ori_y[N];
#define lson rt<<1
#define rson rt<<1|1
#define fi first
#define se second
LL tree_max[N << 2][2][2], clan_max[N << 2][2][2]; ///  [tree][dimension][two]
inline void push_up_max (int rt) {
    for (int i = 0; i < 2; ++i) {
        vector< pair<LL, LL> > pq;
        pq.push_back(make_pair(tree_max[lson][i][0], clan_max[lson][i][0]));
        pq.push_back(make_pair(tree_max[rson][i][0], clan_max[rson][i][0]));
        if (clan_max[lson][i][1] != -1)
            pq.push_back(make_pair(tree_max[lson][i][1], clan_max[lson][i][1]));
        if (clan_max[rson][i][1] != -1)
            pq.push_back(make_pair(tree_max[rson][i][1], clan_max[rson][i][1]));

        sort(pq.begin(), pq.end());
        int j = pq.size() - 1;
        tree_max[rt][i][0] = pq[j].fi; clan_max[rt][i][0] = pq[j].se;
        if (pq.size() > 1) {
            while (j >= 0 && pq[j].se == clan_max[rt][i][0]) j--;
            if (j >= 0 && pq[j].se != clan_max[rt][i][0])
                tree_max[rt][i][1] = pq[j].fi, clan_max[rt][i][1] = pq[j].se;
            else
                clan_max[rt][i][1] = -1;
        }
    }
}
void build_max (int l, int r, int rt) {
    if (l == r) {
        tree_max[rt][0][0] = ninja[l].x;
        tree_max[rt][1][0] = ninja[l].y;
        clan_max[rt][0][0] = clan_max[rt][1][0] = ninja[l].clan;
        clan_max[rt][0][1] = clan_max[rt][1][1] = -1;
        return;
    }
    int mid = (l + r) >> 1;
    build_max(l, mid, lson);
    build_max(mid+1, r, rson);
    push_up_max(rt);
}
void modify_max (int l, int r, int rt, int X) {
    if (l == r) {
        tree_max[rt][0][0] = ninja[X].x;
        tree_max[rt][1][0] = ninja[X].y;
        clan_max[rt][0][0] = clan_max[rt][1][0] = ninja[X].clan;
        //clan_max[rt][0][1] = clan_max[rt][1][1] = -1;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= X) modify_max(l, mid, lson, X);
    else modify_max(mid + 1, r, rson, X);
    push_up_max(rt);
}
struct qnode {
    LL m[2][2]; LL c[2][2], flag;
    qnode () {flag = false;}
    void print () {
        cout << "max : " << endl;
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {printf("%lld ", m[i][j]);} puts("");
        cout << "clan : " << endl;
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {printf("%d ", c[i][j]);} puts("");
    }
};
qnode query_max (int l, int r, int rt, int L, int R) {
    if (L <= l && r <= R) {
        qnode ret;
        ret.flag = true;
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j)
            ret.m[i][j] = tree_max[rt][i][j], ret.c[i][j] = clan_max[rt][i][j];
        return ret;
    }
    int mid = (l + r) >> 1;
    qnode ret[2], ans;
    ans.flag = true;
    if (L <= mid) ret[0] = query_max(l, mid, lson, L, R);
    if (R > mid) ret[1] = query_max(mid + 1, r, rson, L, R);
    for (int i = 0; i < 2; ++i) if (! ret[i].flag) return ret[i ^ 1];
    vector< pair<LL, LL> > pq;
    for (int dim = 0; dim < 2; ++dim) {
        pq.clear();
        for (int i = 0; i < 2; ++i) if (ret[i].flag) {
            for (int j = 0; j < 2; ++j) if (ret[i].c[dim][j] != -1)
                pq.push_back(make_pair(ret[i].m[dim][j], ret[i].c[dim][j]));
        }
        sort(pq.begin(), pq.end());
        int j = pq.size() - 1;
        ans.m[dim][0] = pq[j].fi, ans.c[dim][0] = pq[j].se;
        while (j >= 0 && pq[j].se == ans.c[dim][0]) j--;
        if (j >= 0 && pq[j].se != ans.c[dim][0])
            ans.m[dim][1] = pq[j].fi, ans.c[dim][1] = pq[j].se;
        else
            ans.c[dim][1] = -1;
    }
    return ans;
}

LL tree_min[N << 2][2][2]; LL clan_min[N << 2][2][2]; ///  [tree][dimension][two]
inline void push_up_min (int rt) {
    for (int i = 0; i < 2; ++i) {
        vector< pair<LL, LL> > pq;
        pq.push_back(make_pair(tree_min[lson][i][0], clan_min[lson][i][0]));
        pq.push_back(make_pair(tree_min[rson][i][0], clan_min[rson][i][0]));
        if (clan_min[lson][i][1] != -1)
            pq.push_back(make_pair(tree_min[lson][i][1], clan_min[lson][i][1]));
        if (clan_min[rson][i][1] != -1)
            pq.push_back(make_pair(tree_min[rson][i][1], clan_min[rson][i][1]));

        sort(pq.begin(), pq.end());
        int j = 0;
        tree_min[rt][i][0] = pq[j].fi; clan_min[rt][i][0] = pq[j].se;

        while (j < pq.size() && pq[j].se == clan_min[rt][i][0]) j++;
        if (j < pq.size() && pq[j].se != clan_min[rt][i][0])
            tree_min[rt][i][1] = pq[j].fi, clan_min[rt][i][1] = pq[j].se;
        else
            clan_min[rt][i][1] = -1;
    }
}
void build_min (int l, int r, int rt) {
    if (l == r) {
        tree_min[rt][0][0] = ninja[l].x;
        tree_min[rt][1][0] = ninja[l].y;
        clan_min[rt][0][0] = clan_min[rt][1][0] = ninja[l].clan;
        clan_min[rt][0][1] = clan_min[rt][1][1] = -1;
        return;
    }
    int mid = (l + r) >> 1;
    build_min(l, mid, lson);
    build_min(mid+1, r, rson);
    push_up_min(rt);
}
void modify_min (int l, int r, int rt, int X) {
    if (l == r) {
        tree_min[rt][0][0] = ninja[X].x;
        tree_min[rt][1][0] = ninja[X].y;
        clan_min[rt][0][0] = clan_min[rt][1][0] = ninja[X].clan;
        //clan_max[rt][0][1] = clan_max[rt][1][1] = -1;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= X) modify_min(l, mid, lson, X);
    else modify_min(mid + 1, r, rson, X);
    push_up_min(rt);
}
qnode query_min (int l, int r, int rt, int L, int R) {
    if (L <= l && r <= R) {
        qnode ret;
        ret.flag = true;
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j)
            ret.m[i][j] = tree_min[rt][i][j], ret.c[i][j] = clan_min[rt][i][j];
        return ret;
    }
    int mid = (l + r) >> 1;
    qnode ret[2], ans;
    ans.flag = true;
    if (L <= mid) ret[0] = query_min(l, mid, lson, L, R);
    if (R > mid) ret[1] = query_min(mid + 1, r, rson, L, R);
    for (int i = 0; i < 2; ++i) if (! ret[i].flag) return ret[i ^ 1];
    vector< pair<LL, LL> > pq;
    for (int dim = 0; dim < 2; ++dim) {
        pq.clear();
        for (int i = 0; i < 2; ++i) if (ret[i].flag) {
            for (int j = 0; j < 2; ++j) if (ret[i].c[dim][j] != -1)
                pq.push_back(make_pair(ret[i].m[dim][j], ret[i].c[dim][j]));
        }
        sort(pq.begin(), pq.end());
        int j = 0;
        ans.m[dim][0] = pq[j].fi, ans.c[dim][0] = pq[j].se;
        while (j < pq.size() && pq[j].se == ans.c[dim][0]) j++;
        if (j < pq.size() && pq[j].se != ans.c[dim][0])
            ans.m[dim][1] = pq[j].fi, ans.c[dim][1] = pq[j].se;
        else
            ans.c[dim][1] = -1;
    }
    return ans;
}

int main () {
    int kase, _ = 1; scanf("%d", &kase); while (kase--) {
        int n, m; scanf("%d %d", &n, &m);
        memset(tree_max, 0, sizeof tree_max);
        memset(tree_min, 0, sizeof tree_min);
        memset(clan_max, -1, sizeof clan_max);
        memset(clan_min, -1, sizeof clan_min);
        LL x, y, clan;
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld %lld", &x, &y, &clan);
            ori_x[i] = x;
            ori_y[i] = y;
            ninja[i] = node(x + y, x - y, clan);
            //ninja[i] = node(x, x, clan);
        }
        build_max(1, n, 1);
        build_min(1, n, 1);
        int op, l, r;
        LL k;
        printf("Case #%d:\n", _++);
        while (m--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%lld %lld %lld", &k, &x, &y);
                ori_x[k] += x; ori_y[k] += y;
                ninja[k].x = ori_x[k] + ori_y[k]; ninja[k].y = ori_x[k] - ori_y[k];
                modify_max(1, n, 1, k);
                modify_min(1, n, 1, k);
            } else if (op == 2) {
                scanf("%lld %lld", &k, &clan);
                ninja[k].clan = clan;
                modify_max(1, n, 1, k);
                modify_min(1, n, 1, k);
            } else {
                scanf("%d %d", &l, &r);
                qnode qmax = query_max(1, n, 1, l, r);
                qnode qmin = query_min(1, n, 1, l, r);
                LL ans = -2e18;
                for (int dim = 0; dim < 2; ++dim) {
                    for (int i = 0; i < 2; ++i) if (qmax.c[dim][i] != -1) {
                        for (int j = 0; j < 2; ++j) if (qmin.c[dim][i] != -1) {
                            if (qmax.c[dim][i] != qmin.c[dim][j])
                                ans = max(ans, qmax.m[dim][i] - qmin.m[dim][j]);
                        }
                    }
                }
//                cout << " qmax  " << endl;
//                qmax.print();
//                cout << " qmin  " << endl;
//                qmin.print();
                //assert(ans >= 0);
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
