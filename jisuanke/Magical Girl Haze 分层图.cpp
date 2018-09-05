/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 4e6 + 5;
const int M = 6e6 + 5;


struct edge {
    int to, val, next;
    edge() {}
    edge(int a, int b, int c) : to(a), val(b), next(c) {}
};
edge e[M];
int head[N], tot;

inline void add_edge(int u, int v, int w) {
    e[tot] = edge(v, w, head[u]);
    head[u] = tot ++;
}


bool vis[N];
const ll INF = 1e16;
ll dis[N];
struct node {
    ll val; int to;
    node() {}
    node(ll a, int b) : val(a), to(b) {}
    bool operator < (const node & k) const {
        return val > k.val;
    }
};
void dijkstra(int n) {
    priority_queue<node> pq;
    memset(vis, 0, sizeof(vis[0]) * (n + 3));
    for(int i = 0; i <= n; i ++) dis[i] = INF;
    vis[1] = 0; dis[1] = 0;
    pq.push(node(0, 1));
    node temp;
    int to, u; ll d;
    while(! pq.empty()) {
        temp = pq.top(); pq.pop();
        to = temp.to;
        d = temp.val;
        if (vis[to]) continue;
        vis[to] = true;

        for (int i = head[to]; ~ i; i = e[i].next) {
            u = e[i].to;
            if (! vis[u]) {
                if (dis[u] > dis[to] + e[i].val)
                    dis[u] = dis[to] + e[i].val;
                pq.push(node(dis[u], u));
            }
        }
    }
}

int main() {
    int kase; scanf("%d", &kase);
    while (kase --) {
        int n, m, k; scanf("%d %d %d", &n, &m, &k);
        int u, v, w;
        tot = 0;
        memset(head, -1, sizeof(head[0]) * (n * (k + 1) + 3));
        for (int i = 0; i < m; i ++) {
            scanf("%d %d %d", &u, &v, &w);
            for (int j = 0; j <= k; j ++)
                add_edge(j * n + u, j * n + v, w);
            for (int j = 0; j < k; j ++)
                add_edge(j * n + u, (j + 1) * n + v, 0);
        }
        dijkstra(n * (k + 1));
        ll ans = INF;
//        for (int i = 1; i <= n * (k + 1); i ++)
//            cout << dis[i] << " "; cout << endl;
        for (int i = 0; i <= k; i ++)
            ans = min(ans, dis[n + i * n]);
        printf("%lld\n", ans);
    }
    return 0;
}
