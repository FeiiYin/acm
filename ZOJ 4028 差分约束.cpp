/*
 * @Samaritan_infi
 */
/// 值反边也反
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3f
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
int n,m;

const int maxn = 3e5 + 5;
const int mod = 1e9;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

int head[maxn];
struct edge {
    int to, next;
    ll val;
    edge() {}
    edge(int a, ll b, int c) {to = a, val = b, next = c;}
} e[maxn * 10];
int pos;
void init(int n) {
    for(int i = 0; i <= n; i ++) head[i] = -1;
    //memset(head, -1, sizeof head);
    pos = 0;
}
void add_edge(int u, int v, ll w) {
    e[pos] = edge(v, w, head[u]);
    head[u] = pos ++;
}
bool vis[maxn];
ll dis[maxn];
//int cnt[maxn];
void spfa(int st, int n) {
    queue<int> pq;
    for(int i = 1; i <= n; i ++) {
        vis[i] = 0;
        dis[i] = 0;
    }
//    memset(vis, 0, sizeof vis);
//    memset(dis, inf, sizeof dis);
    //memset(cnt, 0, sizeof cnt);
for(int i = 0;i <= n;++i) pq.push(i);
//
//    vis[st] = true; dis[st] = 0;
//    pq.push(st);
    while(! pq.empty()) {
        int u = pq.front(); pq.pop();
        vis[u] = false;
        //cout << u << endl;
        for(int i = head[u]; ~ i; i = e[i].next) {
                //cout << i << endl;
            int v = e[i].to;
            ll val = e[i].val;

            if(dis[v] < dis[u] + val) {
                dis[v] = dis[u] + val;
                if(! vis[v]) {
                    vis[v] = true;
                    pq.push(v);
                    //cnt[v] ++;
                    //if(cnt[v] >= n) return;
                }
            }
        }
    }
}


int pre[maxn];


int main() {
    int kase = read();
    while(kase --) {
        int n = read();
        init(n);
        for(int i = 0; i <= n; i ++) pre[i] = 0;
        //memset(pre, 0, sizeof pre);
        int a;
        for(int i = 1; i <= n; i ++) {
            a = read();
            if(pre[ a - 1 ])
                add_edge(pre[ a - 1 ], i, 1);
            if(pre[ a ]) add_edge(i, pre[ a ], 0);
            pre[ a ] = i;
        }
        int st = 0;
        ll l, r;
        for(int i = 1; i <= n; i ++) {
            //l = read(), r[i] = read();
            scanf("%lld %lld", &l, &r);
            add_edge(st, i, l);
            add_edge(i, st, -r);
        }

        spfa(st, n);

        //show(dis, n);
        for(int i = 1; i < n; i ++)
            printf("%lld ", dis[i]);

        printf("%lld\n", dis[n]);
    }
    return 0;
}
/*
4
6
1 2 3 2 4 3
0 5
2 4
3 3
1 2
3 5
1 5
5
1 2 1 3 1
100 200
200 300
200 400
400 500
100 500
7
1 2 3 1 1 4 2
0 3
0 3
0 3
0 3
0 3
0 3
0 3
2
1 1
1 2
2 3
*/
