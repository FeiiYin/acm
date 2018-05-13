/*
 * @Samaritan_infi
 */
/// 求最小消耗，不可以不取，所以是选一部分，不能用最大权闭合图，而且复杂度也不够
/// 我们求强连通分量后缩点，然后得出
/// 数据大用主席树来维护

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int a[maxn];

LL f[maxn * 35];

// Persistent SegmentTree
vector<int> G[maxn * 35];

struct node {
    int tag, ls, rs;
} nod[maxn * 35];

int cnt;
int id[maxn];
void build(int p, int tl, int tr){
    cnt++;
    if(tl == tr){
        id[tl] = p;
        nod[p].tag = a[tl];
        return;
    }
    int mid = (tl + tr) >> 1;
    nod[p].ls = cnt + 1, G[p].push_back(cnt + 1), build(cnt + 1, tl, mid);
    nod[p].rs = cnt + 1, G[p].push_back(cnt + 1), build(cnt + 1, mid + 1, tr);
}
void update(int l, int r, int &x, int y, int pos, int v) {
    nod[++cnt] = nod[y];
    x = cnt;
    if (l == r) {
        id[l] = x;
        nod[x].tag = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(l, mid, nod[x].ls, nod[y].ls, pos, v);
    else update(mid + 1, r, nod[x].rs, nod[y].rs, pos, v);
    G[x].push_back(nod[x].ls);
    G[x].push_back(nod[x].rs);
}
void query(int p, int tl, int tr, int l, int r, int x)
{
    if(tr < l || r < tl) return;
    if(l <= tl && tr <= r){
        G[x].push_back(p);
        return;
    }
    int mid = (tl + tr) >> 1;
    query(nod[p].ls, tl, mid, l, r, x);
    query(nod[p].rs, mid + 1, tr, l, r, x);
    return;
}

// Tarjan
stack<int> S;
int dfs_clock, dfn[maxn * 35], low[maxn * 35];
int bcc_cnt, bccno[maxn * 35];
void dfs(int u)
{
    dfn[u] = low[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!bccno[v]) low[u] = min(low[u], dfn[v]);
    }

    if(low[u] == dfn[u])
    {
        bcc_cnt++;
        while(1)
        {
            int x = S.top(); S.pop();
            bccno[x] = bcc_cnt;
            if(x == u) break;
        }
    }
}

void find_bcc(int n)
{
    memset(dfn, 0, sizeof(dfn));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock = bcc_cnt = 0;
    for(int i = 1; i <= n; i++) if(!dfn[i]) dfs(i);
}

int main(){
    int N, M, rt = 1;
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) scanf("%d", a + i);
    build(1, 1, N);
    scanf("%d", &M);
    while(M--){
        int op, x, y, l, r;
        scanf("%d %d", &op, &x);
        if(op == 0){
            scanf("%d", &y);
            update(1, N, rt, rt, x, y);
        }
        else{
            scanf("%d %d", &l, &r);
            query(rt, 1, N, l, r, id[x]);
        }
    }
    assert(cnt < maxn * 35);
    find_bcc(cnt);
    for(int i = 1; i <= cnt; ++i){
        f[bccno[i]] += nod[i].tag;
        for(int j = 0; j < G[i].size(); ++j){
            int to = G[i][j];
            if(bccno[to] != bccno[i]) f[bccno[i]] = 1e18;
        }
    }
    LL ans = 1e18;
    for(int i = 1; i <= bcc_cnt; ++i){
        ans = min(ans, f[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
