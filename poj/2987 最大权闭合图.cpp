/*
 * @Samaritan_infi
 */

/// 最大权闭合图
//#include<bits/stdc++.h>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
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

const int maxn = 5005, maxm = 6e4 + 5;
const int inf = 2147483640;

struct Edge {
    int v, next, u, cap;
}edge[maxm << 1];
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

//void dfs(int u) {
//    if(u == ed) return;
//    vis[u] = 1;
//    
//}
int main() {

    int n = read(), m = read();
    init();
    st = 0, ed = 1 + n;
    int x, l, r;
    ll sum = 0; char c;
    for(int i = 1; i <= n; i ++) {
        x = read();
        if(x >= 0) add_edge(st, i, x), sum += x;
        else if(x < 0) add_edge(i, ed, -x);
    }
    for(int i = 1; i <= m; i ++) {
        l = read(); r = read();
        add_edge(l, r, inf);
    }

    sum -= dinic();
    int ans = 0;
    /// 方法一： 已经证明， 最小的删去的点即所有正的结点的连边
    ///           即当前能在残存网络中能搜到的点数，即最小割的边数最小即答案
    
    /// 方法二：建流时让边的流量乘一个大常数再加一个数，
    ///  这样如果边数相同那么最小割仍是这些边，否则边数少的流量肯定要小
    ///  一般这个大常数为 结点数
    for(int i = 1; i <= n; i ++)
        if(dist[i]) ans ++;//, cout << i << endl;
    printf("%d %lld\n", ans, sum);
    return 0;
}
