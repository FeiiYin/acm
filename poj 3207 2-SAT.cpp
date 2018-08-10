/*
 * @Samaritan_infi
 */
//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

const int N = 2e3 + 5;

vector<int> edge[N];
vector<int> reverse_edge[N];
vector<int> vs;
/// 记录属于第几个联通块
int belong[N];
bool vis[N];

void add_edge(int l, int r) {
    edge[l].push_back(r);
    reverse_edge[r].push_back(l);
}

void dfs(int now) {
    //cout << now << endl;
    vis[now] = true;
    for(int i = 0; i < edge[now].size(); i ++) {
        int to = edge[now][i];
        if(! vis[to])
            dfs(to);
    }
    vs.push_back(now);
}

void rdfs(int now, int scc_num) {
    vis[now] = true;
    belong[now] = scc_num;
    for(int i = 0; i < reverse_edge[now].size(); i ++) {
        int to = reverse_edge[now][i];
        if(! vis[to])
            rdfs(to, scc_num);
    }
}

int scc(int n) {
    memset(vis, 0, sizeof vis);
    vs.clear();
    for(int i = 1; i <= n; i ++)
        if(! vis[i]) dfs(i);

    memset(vis, 0, sizeof vis);
    int scc_num = 0;
    for(int i = vs.size() - 1; i >= 0; i --)
        if(! vis[ vs[i] ])
            rdfs(vs[i], ++ scc_num);
    return scc_num;
}



int a[N], b[N];

void solve(int n) {
    int scc_num = scc(n * 2);
    /// 判断是否满足
    for(int i = 1; i <= n; i ++) {
        if(belong[i] == belong[n + i]) {
            puts("the evil panda is lying again");
            return;
        }
    }
    puts("panda is telling the truth...");
}

int main() {
    int n, m;
    while(~ scanf("%d %d", &n, &m)) {
        for(int i = 0; i <= m * 2; i ++) {
            edge[i].clear();
            reverse_edge[i].clear();
            belong[i] = 0;
        }
        int l, r;
        for(int i = 1; i <= m; i ++) {
            scanf("%d %d", &a[i], &b[i]);
        }

        for(int i = 1; i <= m; i ++)
            for(int j = 1; j < i; j ++) {
                /// xi xj  yi  yj
                if(a[i] < a[j] && b[i] > a[j] && b[i] < b[j]
                   || b[i] > b[j] && a[i] > a[j] && a[i] < b[j]) {
                    add_edge(i, m + j);
                    add_edge(j, m + i);
                    add_edge(m + i, j);
                    add_edge(m + j, i);
                }
            }

        solve(m);
    }
    return 0;
}
