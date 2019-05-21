/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;
const int M = 1e4 + 5;
const int INF = 0x3f3f3f3f;

#define PII pair<int, int>
#define pb push_back
#define fi first
#define se second

struct Edge {
    int to, next, dis, cost;
    Edge () {}
    Edge (int _to, int _next, int _dis, int _cost)
    : to(_to), next(_next), dis(_dis), cost(_cost) {}
    bool operator < (const Edge & k) const {
        return dis > k.dis;
    }
};
int head[N], pic_cnt;
Edge pic[M];

void init () {
    memset(head, -1, sizeof head);
    pic_cnt = 0;
}

inline void add_edge (int x, int y, int dis, int cost) {
    pic[++pic_cnt] = Edge(y, head[x], dis, cost);
    head[x] = pic_cnt;
}

int dis[N], cost[N];
void dij (int n, int tot, int st = 1) {
    int ed = n;
    priority_queue <Edge> pq;
    memset(dis, INF, sizeof (dis[0]) * (n + 3));
    memset(cost, 0, sizeof (cost[0]) * (n + 3));
    dis[st] = 0;
    pq.push(Edge(st, 0, 0, 0));

    while (! pq.empty()) {
        Edge now = pq.top(); pq.pop();
        int now_pos = now.to;
        if (now_pos == ed)
            break;
        if (now.dis > dis[now_pos] && now.cost > cost[now_pos])
            continue;

        for (int i = head[now_pos]; ~ i; i = pic[i].next) {
            int to = pic[i].to;
            int to_dis = now.dis + pic[i].dis;
            int to_cost = now.cost + pic[i].cost;
            if (to_cost <= tot) {
                pq.push(Edge(to, 0, to_dis, to_cost));
                if (to_dis <= dis[to]) {
                    dis[to] = to_dis;
                    cost[to] = to_cost;
                }
            }
        }
    }
    printf("%d\n", dis[ed] == INF ? -1 : dis[ed]);
}

int main () {
    int tot, n, m;
    while (~ scanf("%d %d %d", &tot, &n, &m)) {
        int x, y, dis, cost;
        init();
        for (int i = 0; i < m; ++i) {
            scanf("%d %d %d %d", &x, &y, &dis, &cost);
            add_edge(x, y, dis, cost);
        }
        dij(n, tot);
    }
    return 0;
}
