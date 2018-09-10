/*
 * @Samaritan_infi
 * 区间最值更新不能用lazy
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e4 + 5;

int tree[N << 2][2];
#define lson node<<1
#define rson node<<1|1
inline void push_up(int node, int t) {
    tree[node][t] = max(tree[lson][t], tree[rson][t]);
}
void update (int node, int l, int r, int L, int R, int val, int t) {
    if (l == r) {
        tree[node][t] = max(tree[node][t], val);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) update(lson, l, mid, L, R, val, t);
    if (R > mid) update(rson, mid + 1, r, L, R, val, t);
    push_up(node, t);
}

int query (int node, int l, int r, int L, int R, int t) {
    if (L <= l && r <= R) {
        return tree[node][t];
    }
    int ans = 0;
    int mid = (l + r) >> 1;
    if (L <= mid) ans = max(ans, query(lson, l, mid, L, R, t));
    if (R > mid) ans = max(ans, query(rson, mid + 1, r, L, R, t));
    return ans;
}

struct node {
    int x, y, xid, yid, id;
    node () {}
    node (int a, int b, int c) {
        x = a;
        y = b;
        id = c;
    }
};
node arr[N];
int xrr[N], yrr[N];

bool cmp1(node a, node b) {
    return a.x < b.x;
}

bool cmp2(node a, node b) {
    return a.y < b.y;
}

bool cmp3(node a, node b) {
    return a.id < b.id;
}

map<int, int> xx;
map<int, int> yy;

int main() {
    int n;
    while (~ scanf("%d", &n)) {
        int x, y;
        for (int i = 1; i <= n; i ++) {
            scanf("%d %d", &x, &y);
            arr[i] = node(x, y, i);
        }

        sort(arr + 1, arr + 1 + n, cmp1);
        xx[0] = 1;
        int cur = 2, pre = arr[1].x;
        for (int i = 1; i <= n; i ++) {
            if (arr[i].x == pre) {
                arr[i].xid = cur;
            } else {
                pre = arr[i].x;
                cur ++;
                arr[i].xid = cur;
            }
            xx[ arr[i].x ] = arr[i].xid;
        }
        int xmax = arr[n].xid;
        sort(arr + 1, arr + 1 + n, cmp2);
        yy[0] = 1;
        cur = 2, pre = arr[1].y;
        for (int i = 1; i <= n; i ++) {
            if (arr[i].y == pre) {
                arr[i].yid = cur;
            } else {
                pre = arr[i].y;
                cur ++;
                arr[i].yid = cur;
            }
            yy[ arr[i].y ] = arr[i].yid;
        }
        int ymax = arr[n].yid;
        sort(arr + 1, arr + 1 + n, cmp3);
        memset(tree, 0, sizeof tree);

        ll ans = 0;
        for (int i = n; i >= 1; i --) {
            int xq = query(1, 1, xmax, arr[i].xid, xmax, 0);
            int yq = query(1, 1, ymax, arr[i].yid, ymax, 1);
            int xxi = xx[yq], yyi = yy[xq];

            if (arr[i].y > xq)
                ans += (ll)(arr[i].y - xq), update(1, 1, xmax, xxi , arr[i].xid, arr[i].y, 0);
            if (arr[i].x > yq)
                ans += (ll)(arr[i].x - yq), update(1, 1, ymax, yyi , arr[i].yid, arr[i].x, 1);

        }
        printf("%lld\n", ans);
    }
    return 0;
}
