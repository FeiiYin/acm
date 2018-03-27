/*
 * @Samaritan_infi
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 200 + 5 ;
bool vis[maxn][maxn] ;
int ans[maxn];
int bottle[3];

struct node {
    int bottle[3], val;
    node() {}
    node(int a, int b, int c, int d) {
        bottle[0] = a;
        bottle[1] = b;
        bottle[2] = c;
        val = d;
    }
    bool operator < (const node &a) const {
        return val > a.val;
    }
};

void update(node u) {
    for(int i = 0; i < 3; i ++) {
        if(ans[ u.bottle[i] ] < 0 || ans[ u.bottle[i] ] > u.val)
            ans[ u.bottle[i] ] = u.val ;
    }
}

void solve(int a, int b, int c, int d) {
    memset(vis, 0, sizeof vis);
    memset(ans, -1, sizeof ans);
    bottle[0] = a; bottle[1] = b; bottle[2] = c;

    priority_queue<node> pq;
    node start = node(0, 0, c, 0);
    pq.push(start);
    vis[0][0] = true;
    
    while(! pq.empty()) {
        node u = pq.top(); pq.pop();
        update(u);
        if(ans[d] >= 0) break;
        for(int i = 0; i < 3; i ++) {
            for(int j = 0; j < 3; j ++) {
                if(i == j) continue;
                /// i poor into j
                if(u.bottle[i] <= 0 || u.bottle[j] > bottle[j]) continue;
                int cap = min(bottle[j], u.bottle[i] + u.bottle[j]) - u.bottle[j];
                node v;
                memcpy(&v, &u, sizeof u);
                v.bottle[i] -= cap;
                v.bottle[j] += cap;
                v.val += cap;
                if(! vis[ v.bottle[0] ][ v.bottle[1] ]) {
                    vis[ v.bottle[0] ][ v.bottle[1] ] = true;
                    pq.push(v);
                }
            }
        }
    }
    while(d >= 0) {
        if(ans[d] >= 0) {
            printf("%d %d\n" , ans[d], d);
            return;
        }
        d --;
    }
}

int main() {
    int a, b, c, d;
    int kase; scanf("%d" , &kase);
    while(kase --) {
        scanf("%d %d %d %d" , &a, &b, &c, &d);
        solve(a, b, c, d);
    }
    return 0 ;
}
