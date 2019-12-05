///
/**
 * @Samaritan
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define pb emplace_back
#define fi first
#define se second
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define PLI pair<LL, int>

LL quick_pow (LL a, LL b, LL mod) {
    LL ans = 1, base = a;
    while (b) {
        if (b & 1) (ans *= base) %= mod;
        b >>= 1;
        (base *= base) %= mod;
    }
    return ans;
}
void gcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        d = a; x = 1; y = 0;
    } else {
        gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}
LL get_inv(LL a, LL n) {
    LL d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}
inline int log2(const float &x) {
    return ((unsigned &) x >> 23 & 255) - 127;
}
template <typename type>
void show(type arr[], int len) {
    for (int i = 0; i <= len; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
struct node {
    int dist, id;
    node() {
    }
    node(int d, int i) : dist(d), id(i) {}
    bool operator < (const node& k) const {
        if (dist == k.dist)
            return id <= k.id;
        return dist < k.dist;
    }
};

const int mod = 998244353;
const int N = 1e5 + 5;
const int logN = 30;
const int INF = 0x3f3f3f3f;

const int maxn = 2e3 + 5;
const int maxm = 1e5 + 5;
//已经处理了重边问题
#define index Index
struct Edge {
    int u, v, next;
} edge[maxm];
int head[maxn], cnt;
int low[maxn], dfn[maxn], Stack[maxn], belong[maxn];
int index, top;
int block; //边双联通分量的数量
bool vis[maxn];
int n, m;

void add_edge (int u, int v) {
    edge[cnt] = (Edge) {u, v, head[u]}; head[u] = cnt++;
}
void tarjan (int u, int pre) {
    int v;
    low[u] = dfn[u] = ++index;
    Stack[top++] = u;
    vis[u] = 1;
    for (int i = head[u]; i+1; i = edge[i].next) {
        v = edge[i].v;
        if (pre+1 && pre == (i^1)) continue;
        if (!dfn[v]) {
            tarjan (v, i);
            if (low[u] > low[v]) low[u] = low[v];
        }
        else if (vis[v] && low[u] > dfn[v]) {
            low[u] = dfn[v];
        }
    }
    if (low[u] == dfn[u]) {
        block++;
        do {
            v = Stack[--top];
            vis[v] = 0;
            belong[v] = block;
        }
        while (v != u);
    }
}
void find_bcc () {
    memset(dfn, 0, sizeof dfn);
    memset(vis, 0, sizeof vis);
    index = top = block = 0;
    for (int i = 1; i <= n; ++i) if (!belong[i])
        tarjan (i, -1);
}

vector<int> e[N];
int dlen, st, ed;
bool vis2[N];
void dfs_d(int x, int par, int dep) {
    vis2[x] = true;
    if (dlen < dep) {
        dlen = dep;
        st = x;
    }
    for (int to : e[x]) if (to != par) {
        dfs_d(to, x, dep + 1);
    }
}
int pre[N], siz[N];
void dfs_d2(int x, int par, int dep) {
    if (dlen < dep) {
        dlen = dep;
        st = x;
    }
    pre[x] = par;
    siz[x] = 1;
    for (int to : e[x]) if (to != par) {
        dfs_d2(to, x, dep + 1);
        siz[x] += siz[to];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof head);
    int l, r;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &l, &r);
        add_edge(l, r);
        add_edge(r, l);
    }
    find_bcc();

//    for (int i = 1; i <= n; ++i) {
//        cout << belong[i] << " ";
////        cout << "new bcc: \n";
////        for (int x : bcc[i]) {
////            cout << x << " ";
////        }
////        cout << endl;
//    }
    /// circle
    int ans = n - block;
    for (int i = 0; i < cnt; i += 2) {
        int u = edge[i].u, v = edge[i].v;
        u = belong[u];
        v = belong[v];
        if (u != v) {
            e[u].pb(v);
            e[v].pb(u);
//            cout << "new pic: " << u << " " << v << endl;
        }
    }
//    cout << ans << endl;
    int tree_num = 0;
    /// every tree cal
    for (int i = 1; i <= block; ++i) if (!vis2[i]) {
        tree_num++;

        st = i;
        dlen = 0;
        dfs_d(i, -1, 0);
        ed = st;
        dlen = 0;
        dfs_d2(ed, -1, 0);
//        cout << "d: " << st << " " << ed << endl;
        int nx = st;
        /// end point will add value, or it will not be the d
        st = pre[st];
        while (st != ed && st != -1) {
            ans += max(0, (int)(siz[st] + 2 - e[st].size() - siz[nx] - 1));
//            cout << "add: " << st << " son: " << nx << " par: " << pre[st] << endl;
//            cout << ans << endl;
            nx = st;
            st = pre[st];
        }
    }
//    cout << ans << endl;
    ans += tree_num - 1;
    printf("%d\n", ans);
    return 0;
}
