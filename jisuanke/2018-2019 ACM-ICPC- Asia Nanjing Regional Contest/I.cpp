/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define PII pair<int, int>
#define fi first
#define se second
#define mp make_pair

const int maxn = 1010, maxm = 4e4 + 5;
const int inf = 2147483640;

struct Edge {
    int v, next, u, cap;
}edge[maxm];
int k, head[maxn], dist[maxn], que[maxn], n, m, st, ed, current[maxn];

void init() {
    memset(head, -1, sizeof head);
    k = -1; /// very important cannot change
}

void add_edge(int u, int v, int cap) {
    edge[++k].u = u;
    edge[k].v = v;
    edge[k].cap = cap;
    edge[k].next = head[u];
    head[u] = k;
    edge[++k].u = v;
    edge[k].v = u;
    edge[k].cap = 0;
    edge[k].next = head[v];
    head[v] = k;
}
bool bfs() {
    int fro, top;
    memset(dist, 0, sizeof(dist));
    dist[st] = 1;
    fro = top =1;
    que[fro] = st;
    while(fro <= top)
    {
        int p = que[fro++];
        for(int kk = head[p]; ~kk; kk = edge[kk].next)
        {
            int v = edge[kk].v, cap = edge[kk].cap;
            if(cap && !dist[v])
            {
                dist[v] = dist[p] + 1;
                que[++top] = v;
                if(v == ed) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u, int maxflow) {
    if(u == ed || maxflow == 0) return maxflow;
    int t = 0;
    for(int& kk = current[u]; ~kk; kk = edge[kk].next)
    {
        int v =  edge[kk].v, cap = edge[kk].cap;
        if(cap && dist[v] ==  dist[u] + 1)
        {
            int f = dfs(v, min(cap, maxflow - t));
            t += f;
            edge[kk].cap -= f;
            edge[kk ^ 1].cap += f;
            if(t == maxflow) return t;
        }
    }
    if(t == 0) dist[u] = -1;
    return t;
}
LL dinic() {
    LL maxnflow = 0, t;
    while(bfs()) {
        for(int i = 0; i <= ed; ++i) current[i] = head[i];
        while(t = dfs(st, inf))
            maxnflow += t;
    }
    return maxnflow;
}

const int N = 550;
int monster[N];
vector<int> bekill[N];
int id[N];
bool vis[N];
int num[N];
bool cmp (int a, int b) {
    return monster[a] < monster[b];
}
bool cmp2(int a, int b) {
    return num[a] > num[b];
}
int main () {
    int n, m, k;
    while (~ scanf("%d %d %d", &n, &m, &k)) {
        init();
        int t, x;
        /// hero 1 - n, monster n + 1, n + m, st, 0, ed, n+m+1
        memset(monster, 0, sizeof monster);
        for (int i = 1; i <= m; ++i) bekill[i].clear();
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &num[i]);
            for (int j = 1; j <= num[i]; ++j) {
                scanf("%d", &x);
                monster[x]++;
                bekill[x].push_back(i);
                add_edge(i, n + x, 1);
            }
        }
        for (int i = 1; i <= m; ++i) id[i] = i;
        sort (id + 1, id + 1 + m, cmp);

        int yao = n+m+1;
        st = 0,  ed = yao+1;

        int zero = 0;
        add_edge(st, yao, k);

        for (int i = 1; i <= m; ++i) {
            add_edge(i+n, ed, 1);
        }
        for (int i = 1; i <= n; ++i) {
            add_edge(yao, i, 1);
            add_edge(st, i, 1);
        }

        int flow = dinic();
        printf("%d\n", flow);
    }
    return 0;
}
