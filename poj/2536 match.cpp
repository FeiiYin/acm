/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
typedef long long LL;

const int N = 3e2 + 5;
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

int match[N];
int check[N];

bool dfs (int x) {
    for (int i = head[x]; ~ i; i = pic[i].next) {
        int to = pic[i].to;
        if (check[to]) continue;
        check[to] = true;
        /// ***
        if (match[to] == -1 || dfs(match[to])) {
            match[x] = to;
            match[to] = x;
            return true;
        }
    }
    return false;
}

int hag (int n, int m) {
    int tot = n + m;
    memset(match, -1, sizeof (match[0]) * (tot + 3));
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (match[i] == -1) {
            memset(check, 0, sizeof (check[0]) * (tot + 3));
            if (dfs(i))
                ans++;
        }
    }
    return ans;
}

double x[N], y[N];
inline double cal_dis (int i, int j) {
    return (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);
}

int main () {
    int tot, n, m, s, v;
    while (~ scanf("%d %d %d %d", &n, &m, &s, &v)) {
        init();
        for (int i = 1; i <= m + n; ++i) {
            scanf("%lf %lf", &x[i], &y[i]);
        }
        double dis = s * v * s * v;
        for (int i = 1; i <= n; ++i) {
            for (int j = n + 1; j <= n + m; ++j) {
                if (cal_dis(i, j) <= dis) {
                    add_edge(i, j, 0, 0);
                    //cout << "edge: " << i << " " << j << endl;
                }
            }
        }
        int ans = hag(n, m);
        printf("%d\n", n - ans);
    }
    return 0;
}

