/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long LL;

const int N = 1e4 + 5;
const int INF = 1e5 + 5;
const int mod = 1e9 + 7;

struct node {
    double l, r, h;
    int val;
    node () {}
    node (double _l, double _r, double _h, int _val)
    : l(_l), r(_r), h(_h), val(_val) {}
    void show () {
        printf("%.1f %.1f %.1f %d\n", l, r, h, val);
    }
    bool operator < (const node &k) const {
        return h < k.h;
    }
};

node line[N];
double xrr[N]; int xrr_cnt;

double tree[N];
int mark[N];
void push_up (int rt, int l, int r) {
    /// avoid segment being recovered
    if (mark[rt])
        tree[rt] = xrr[r + 1] - xrr[l];
    /// reach leaf and not been add
    /// which cannot be omitted, otherwise should memset tree array to 0 every case
    else if (l == r)
        tree[rt] = 0;
    else
        tree[rt] = tree[rt<<1] + tree[rt<<1|1]; 
}

void update (int rt, int l, int r, int L, int R, int val) {
//    cout << "update: " << l << " " << r << " " << L << " " << R << endl;
    if (L <= l && r <= R) {
        mark[rt] += val;
        push_up(rt, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        update(rt<<1, l, mid, L, R, val);
    if (R > mid)
        update(rt<<1|1, mid+1, r, L, R, val);
    push_up(rt, l, r);
}

int main () {
    int n, kase = 1;
    while (~ scanf("%d", &n) && n) {
        double a, b, c, d;
        xrr_cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
            xrr[xrr_cnt++] = a;
            xrr[xrr_cnt++] = c;
            line[i << 1] = node(a, c, b, 1);
            line[i << 1|1] = node(a, c, d, -1);
        }
        /// hash
        sort (xrr, xrr + xrr_cnt);
        map <double, int> xmp;

        xrr_cnt = unique(xrr, xrr + xrr_cnt) - xrr;

        for (int i = 0; i < xrr_cnt; ++i)
            xmp[ xrr[i] ] = i + 1;
        for (int i = xrr_cnt; i >= 1; --i)
            xrr[i] = xrr[i-1];

        n <<= 1;
        /// solve
        sort (line, line + n);
        double ans = 0.0;
        for (int i = 0; i < n; ++i) {
            int l = xmp[ line[i].l ];
            int r = xmp[ line[i].r ];
//            line[i].show();
            /// update r - 1 is very important, since it's [ a, b )
            /// update {a, b} and {b, c}, b is one point and should be update only once
            update(1, 1, xrr_cnt, l, r-1, line[i].val);
            // cout << "tree: "; for (int i = 1; i <= 10; ++i) cout << tree[i] << " "; cout << endl;
            ans += tree[1] * (line[i+1].h - line[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", kase++, ans);
    }
    return 0;
}
