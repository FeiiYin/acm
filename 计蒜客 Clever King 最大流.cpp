/*
 * @Samaritan_infi
 */
 /// 假设物品需要其他的前驱，有的有亏，有的有赚，甚至可能循环依赖
 /// 建图方式：
 /// 亏得向终点建立一条flow=|val[i]|
 /// 赚的向起点建立一条flow=val[i]
 /// 依赖关系 a依赖b  a向b建立无穷大流量的边
 /// 答案为 正的值减去最大流
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
//const ll inf = 2147483640;
#define inf 2147483640
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
    int kase = read();
    while(kase --) {
        int n = read(), m = read();
        init();
        st = 0, ed = 1 + n + m;
        ll sum = 0; int x;
        for(int i = 1; i <= n; i ++) {
            x = read();
            sum += x;
            add_edge(0, i, x);
        }
        for(int i = 1; i <= m; i ++) {
            x = read();
            add_edge(n + i, ed, x);
        }
        int a, b;
        for(int i = 1; i <= n; i ++) {
            a = read(); b = read();
            while(a --) {
                x = read();
                add_edge(i, n + x, inf);
            }
            while(b --) {
                x = read();
                add_edge(i, x, inf);
            }
        }
        ll t, maxnflow = 0;
        while(bfs()) {
            for(int i = 0; i <= ed; ++i) current[i] = head[i];
            while(t = dfs(st, inf))
                maxnflow += t;
        }
        //int ans = dinic();
        printf("%lld\n", sum - maxnflow);
    }
    return 0;
}
