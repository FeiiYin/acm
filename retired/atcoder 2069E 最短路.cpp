/// 有、问题
///
/**
 * @Samaritan
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define pb emplace_back
#define fi first
#define se second
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define PLI pair<LL, int>

LL quick_pow (LL a, LL b, LL mod) {
    LL ans = 1, base = a;
    while (b) {
        if (b & 1) (ans *= base) %= mod;
        b >>= 1;
        (base *= base) %= mod;
    }
    return ans;
}

inline int log2(const float &x) {
    return ((unsigned &) x >> 23 & 255) - 127;
}

void show(int arr[], int len) {
    for (int i = 0; i <= len; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
struct node {
    int dist, id;
    node() {
    }
    node(int d, int i) : dist(d), id(i) {}
    bool operator < (const node& k) const {
        if (dist == k.dist)
            return id <= k.id;
        return dist < k.dist;
    }
};

const int mod = 998244353;
const int N = 1e5 + 5;
const int logN = 20;
const int INF = 0x3f3f3f3f;

vector<PII> edge[N];
int dist[N];
set<int> type[N];
//bool vis[N];

void work(int n) {
    memset(dist, INF, sizeof dist);
    dist[1] = 0;
    priority_queue<PII> p;
    p.push({0, 1});
    while(!p.empty()) {
        int now = p.top().second;
        int val = -p.top().first;
        p.pop();
        if (dist[now] < val)
            continue;
        for (const auto& pp : edge[now]) {
            int to = pp.first;
            int now_type = pp.second;
            int now_val = val;
            if (!type[now].count(now_type))
                now_val++;
//            int to_ca=ca+(!type[now].count(to_com));
            if (dist[to] > now_val) {
                dist[to] = now_val;
                p.push({-now_val, to});
                type[to].clear();
                type[to].insert(now_type);
            } else if(dist[to] == now_val) {
                type[to].insert(now_type);
            }
        }
    }
    return;
    memset(dist, INF, sizeof(dist[0]) * (n + 3));
    priority_queue<PII, vector< PII >, greater<> > pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        int pos = pq.top().second;
        int now_dist = pq.top().first;
        pq.pop();
//        if (vis[pos]) continue;
//        vis[pos] = true;
        if (now_dist > dist[pos]) continue;
        for (const auto& p : edge[pos]) {
            int to = p.first;
            int now_type = p.second;
            int now_val = dist[pos];
            if (!type[pos].count(now_type))
                now_val++;
            if (now_val < dist[to]) {
                dist[to] = now_val;
                type[to].clear();
                type[to].insert(now_type);
                pq.push({dist[to], to});
            } else if (now_val == dist[to]) {
                type[to].insert(now_type);
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; ++i)
        edge[i].clear();
    int l, r, c;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &l, &r, &c);
        edge[l].pb(r, c);
        edge[r].pb(l, c);
    }
    work(n);

    if (dist[n] >= INF)
        puts("-1");
    else
        printf("%d\n", dist[n]);
    return 0;
}

