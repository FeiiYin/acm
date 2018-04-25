/*
 * @Samaritan_infi
 */
/// power Oj https://www.oj.swust.edu.cn/problem/show/1738
/// 最小路径覆盖
/// 最小路径覆盖问题模型，拆点做最大匹配，总点数减去最大流为需要的最少的边数
/// 拆点意思是这样的，第i个点的流量流向第j个点时表示第i个点的下一个点是j点，
/// 剩下的没办法流向终点的点就是没有点能到它那里，说明这个点是边的起点，根据这个来递归可以用来查找答案方案。
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

bool vis[maxn];
vector<int> output;
void dfs_ans(int u, int n) {
    if(u == ed) return;
    vis[u] = true;
    output.push_back(u);
    for(int i = head[u + n]; ~ i; i = edge[i].next) {
        if(edge[i].cap == 1) {
            dfs_ans(edge[i].v, n);
        }
    }
}

int main() {
    int n = read(), m = read();
    init();
    st = 0, ed = 1 + (n << 1);
    for(int i = 1; i <= n; i ++)
        add_edge(st, i, 1), add_edge(i + n, ed, 1);
    int l, r;
    for(int i = 1; i <= m; i ++) {
        l = read();
        r = read();
        add_edge(l, r + n, 1);
    }
    int ans = n - dinic();
    memset(vis, 0, sizeof vis);
    for(int i = head[0]; ~ i; i = edge[i].next) {
        if(edge[i].cap == 1 && ! vis[ edge[i].v ]) {
            output.clear();
            dfs_ans(edge[i].v, n);
            for(int i = output.size() - 1; i >= 0; i --) printf("%d ", output[i]); puts("");
        }
    }
    printf("%d\n", ans);
    return 0;
}
