/*
 * @Samaritan_infi
 */
/// 白书 p 247
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

const int maxn = 1e4 + 5;
const int maxm = maxn << 3;
const int mod = 998244353;

#define type int
const int INF = 0x3f3f3f3f;
//s源点t汇点N总点数
int s, t;
struct node {
    int u, v, next;
    type cap, flow, cost;
}edge[maxm];
int head[maxn], cnt;
int pre[maxn];
type dis[maxn];
bool vis[maxn];
int N;

void init () {
    memset (head, -1, sizeof head);
    cnt = 0;
}

void add_edge (int u, int v, type cap, type cost) {
    edge[cnt].u = u, edge[cnt].v = v, edge[cnt].cap = cap, edge[cnt].flow = 0;
    edge[cnt].cost = cost, edge[cnt].next = head[u], head[u] = cnt++;
    edge[cnt].u = v, edge[cnt].v = u, edge[cnt].cap = 0, edge[cnt].flow = 0;
    edge[cnt].cost = -cost, edge[cnt].next = head[v], head[v] = cnt++;
}

bool spfa (int s, int t) {
    queue <int> q;
    for (int i = 0; i < N; i++) {
        dis[i] = INF;
        vis[i] = 0;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = 1;
    q.push (s);
    while (!q.empty ()) {
        int u = q.front (); q.pop ();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].cap > edge[i].flow && dis[v] > dis[u]+edge[i].cost) {
                dis[v] = dis[u]+edge[i].cost;
                pre[v] = i;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push (v);
                }
            }
        }
    }
    if (pre[t] == -1)
        return 0;
    else
        return 1;
}

int MCMF (int s, int t, type &cost) {
    type flow = 0;
    cost = 0;
    while (spfa (s, t)) {
        type Min = INF;
        for (int i = pre[t]; i != -1; i = pre[edge[i^1].v]) {
            if (Min > edge[i].cap-edge[i].flow) {
                Min = edge[i].cap-edge[i].flow;
            }
        }
        for (int i = pre[t]; i != -1; i = pre[edge[i^1].v]) {
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost*Min;
        }
        flow += Min;
    }
    return flow;
}

int interval_l[maxn], interval_r[maxn], interval_val[maxn];

void solve(int interval_num, int cover_k) {
    vector<int> hash_vector;
    for(int i = 0; i < interval_num; i ++) {
        hash_vector.push_back(interval_l[i]);
        hash_vector.push_back(interval_r[i]);
    }
    hash_vector.push_back(0);
    hash_vector.push_back(100001);

    sort(hash_vector.begin(), hash_vector.end());
    hash_vector.erase(unique(hash_vector.begin(), hash_vector.end()), hash_vector.end());

    int node = hash_vector.size();
    s = node, t = s + 1;
    N = t + 1;
    add_edge(s, 0, cover_k, 0);
    add_edge(node - 1, t, cover_k, 0);
    for(int i = 0; i + 1 < node; i ++)
        add_edge(i, i + 1, cover_k, 0);
    for(int i = 0; i < interval_num; i ++) {
        int u = find(hash_vector.begin(), hash_vector.end(), interval_l[i]) - hash_vector.begin();
        int v = find(hash_vector.begin(), hash_vector.end(), interval_r[i]) - hash_vector.begin();
        u --; v;
        //cout << u << " " << v << endl;
        /// 从u向v连一条容量为1，费用为-w[i]的边
        add_edge(u, v, 1, -interval_val[i]);
    }
    int cost = cover_k + interval_num;
    MCMF(s, t, cost);
    printf("%d\n", - cost);
}

int main() {
    int kase = read();
    while(kase --) {
        init();
        int interval_num = read(), cover_k = read(); interval_num = read();
        for(int i = 0; i < interval_num; i ++) {
            scanf("%d %d %d", &interval_l[i], &interval_r[i], &interval_val[i]);
            //interval_l[i] --;
            //interval_r[i] ++;
        }
        solve(interval_num, cover_k);
    }
    return 0;
}
