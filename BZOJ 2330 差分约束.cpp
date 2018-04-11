/*
 * @Samaritan_infi
 */
/// 卡vector，极限数据是单链
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int maxn = 1e5 + 5;
//vector< pair<int, int> > edge[maxn];
//void add_edge(int a, int b, int c) {
//    edge[a].push_back(make_pair(b, c));
//}

struct ss {
    int to, v;
    int next;
    ss() {}
    ss(int a, int b, int c) {to = a, v = b, next = c;}
} edge[maxn << 2];
int head[maxn], pos;

void add_edge(int a, int b, int c) {
    edge[++ pos] = ss(b, c, head[a]);
    head[a] = pos;
}

const ll inf = 0x7f;
ll dis[maxn];
bool vis[maxn];
int times[maxn];
void spfa(int n) {
    memset(vis, 0, sizeof vis);
    memset(dis, inf, sizeof dis);
    memset(times, 0, sizeof times);

    queue<int> pq;
    dis[0] = 0;
    times[0] ++;
    vis[0] = true;
    pq.push(0);

    while(! pq.empty()) {
        int x = pq.front();
        pq.pop();
        vis[x] = false;
        for(int i = head[x]; ~ i; i = edge[i].next) {
            int w = edge[i].v;
            int to = edge[i].to;
            if(dis[ to ] > dis[x] + w) {
                dis[to] = dis[x] + w;
                if(! vis[to]) {
                    vis[to] = true;
                    times[to] ++;
                    pq.push(to);
                    if(times[to] > n) {
                        puts("-1");
                        return;
                    }
                }
            }
        }
    }
    ll ans = 0;

    for(int i = 1; i <= n; i ++) ans += dis[i];//, cout << dis[i] << " ";
    printf("%lld\n", - ans);
}

int main() {
    int n = read(), t = read();
    pos = 0;
    memset(head, -1, sizeof head);
    //while(~ scanf("%d %d", &n, &t)) {
        int a, b, op;
        //for(int i = 1; i <= n; i ++) edge[i].clear();
        bool flag = false;
        for(int i = n; i >= 1; i --) add_edge(0, i, -1);
        /// 吃T
        ///for(int i = 1; i <= n; i ++) add_edge(0, i, -1); 
        
        while(t --) {
            op = read(); a = read(); b = read();
            if(op == 1) {
                add_edge(a, b, 0);
                add_edge(b, a, 0);
            } else if(op == 2) {
                if(a == b) flag = true;
                add_edge(a, b, -1);
            } else if(op == 3) {
                add_edge(b, a, 0);
            } else if(op == 4) {
                if(a == b) flag = true;
                add_edge(b, a, -1);
            } else {
                add_edge(a, b, 0);
            }
        }
        if(flag) {
            puts("-1");
            return 0;
            //continue;
        }
        spfa(n);
    //}
    return 0;
}
/*
5 7
1 1 2
2 3 2
4 4 1
3 4 5
5 4 5
2 3 5
4 5 1
-2 -2 -1 -3 -3
*/

