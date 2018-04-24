/*
 * @Samaritan_infi
 */
/// power Oj https://www.oj.swust.edu.cn/problem/show/1737
/// 最大权闭合图
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int maxn = 410, maxm = 3e4 + 5;
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
ll dinic() {
    ll maxnflow = 0, t;
    while(bfs()) {
        for(int i = 0; i <= ed; ++i) current[i] = head[i];
        while(t = dfs(st, inf))
            maxnflow += t;
    }
    return maxnflow;
}


int main() {
    int n = read(), m = read();
    init();
    st = 0, ed = 1 + n + m;
    int x, l, sum = 0; char c;
    for(int i = 1; i <= n; i ++) {
        x = read();
        sum += x;
        add_edge(st, i, x);
        while(true) {
            scanf("%d%c", &l, &c);
            add_edge(i, n + l, inf);
            if(c == '\n' || c == '\r') break;
        }
    }
    for(int i = 1; i <= m; i ++) {
        x = read();
        add_edge(n + i, ed, x);
    }
    sum -= dinic();
    ///选取方案
    ///选取 残量网络中 能从起点搜到的点，用最后一次的bfs 距离大于0
    for(int i = 1; i <= n; i ++) {
        if(dist[i]) printf("%d ", i);
    } puts("");
    for(int i = 1; i <= m; i ++) {
        if(dist[n + i]) printf("%d ", i);
    } puts("");
    printf("%d\n", sum - dinic());
    return 0;
}
