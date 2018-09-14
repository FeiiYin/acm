/*
 * @Samaritan_infi
 * https://vjudge.net/problem/UVALive-8522
 * 银牌提
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;
map<int, int> cnt;
int a[N], b[N], ans[N];

struct Seg {
    int m, tag;
    Seg * ls, * rs;
    void push_up () {
        m = min(ls->m + tag, rs->m + tag);
    }
    void push_down () {
        ls->tag += tag;
        rs->tag += tag;
        tag = 0;
    }
    Seg (int l, int r) {
        ls = rs = nullptr;
        tag = 0; m = INF;
        if (l == r) {
            m = - cnt[l];
            return;
        }
        int mid = (l + r) >> 1;
        ls = new Seg(l, mid);
        rs = new Seg(mid + 1, r);
        push_up();
    }
    void modify (int l, int r, int L, int R, int v) {
        if (r < L || R < l) return;
        if (L <= l && r <= R) { tag += v; return; }
        push_down();
        int mid = l + r >> 1;
        ls->modify(l, mid, L, R, v);
        rs->modify(mid + 1, r, L, R, v);
        push_up();
    }
} * SegTree;

int a_len;
int Min () { return SegTree->m + SegTree->tag; }
void add(int x, int v) {
    int p = lower_bound(a + 1, a + a_len + 1, x) - a;
    if (p == a_len + 1) return;
    SegTree->modify(1, a_len, p, a_len, v);
}

int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
        int n, m, k; scanf("%d %d %d", &n, &m, &k);
        cnt.clear();
        for (int i = 1; i <= n; i ++) {
            scanf("%d", &a[i]);
            cnt[ a[i] ] ++;
        }
        sort (a + 1, a + 1 + n);
        a_len = unique(a + 1, a + n + 1) - a;
        int pre = 0;
        for (auto it : cnt) {
            it.second += pre;
            pre = it.second;
        }
        for (int i = 1; i <= m; i ++)
            scanf("%d", &b[i]);
        SegTree = new Seg(1, a_len);
        memset(ans, -1, sizeof ans);
        int i = 1, j = 1;
        
        while (j <= m) {
            while (Min() >= 0) {
                ans[i] = j - 1;
                add(k - b[i], -1);
                i ++;
            }
            while (Min() < 0 && j <= m) {
                add(k - b[j], 1);
                j ++;
            }
        }
        
        int q; scanf("%d", &q);
        while (q --) {
            int l, r; scanf("%d %d", &l, &r);
            int res = 1;
            if (ans[l] == -1 || r < ans[l]) res = 0;
            printf("%d\n", res);
        }
    }
    return 0;
}

/*
1
3 4 5
1 1 1
4 4 4 3
2
1 3
2 4
*/
