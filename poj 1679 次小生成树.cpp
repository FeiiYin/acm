/*
 * @Samaritan_infi
 */
//easy
//#include<bits/stdc++.h>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 10005;
struct node{
    int u, v, w;
    node() {}
    node(int a, int b, int c) {u = a, v = b, w = c;}
    bool operator < (const node &k) const {
        return w < k.w;
    }
};
node save[maxn];
//vector<node> edge[maxn];
int par[maxn];
int find_par(int x) {
    if(par[x] == x) return x;
    return par[x] = find_par(par[x]);
}


void init(int n) {
    for(int i = 1; i <= n; i ++) par[i] = i;
}



void kruskal(int n, int m) {
    sort(save, save + m);
    int res = 0;
    int num = 0;
    int pos = 0, pos_val = 0;
    for(int i = 0; i < m; i ++) {
        int u = save[i].u, v = save[i].v;
        int u_par = find_par(u);
        int v_par = find_par(v);
        if(u_par == v_par) continue;
        num ++;
        if(num == n - 1) {
            pos = i + 1;
            pos_val = save[i].w;
            res += pos_val;
            break;
        }
        par[u_par] = v_par;
        res += save[i].w;
    }
    for(int i = pos; i < m; i ++) {
        int u = save[i].u, v = save[i].v;
        int u_par = find_par(u);
        int v_par = find_par(v);
        if(u_par == v_par) continue;
        if(save[i].w == pos_val) {
            printf("Not Unique!\n");
            return;
        }
        break;
    }
    printf("%d\n", res);
}

int main() {
    int kase; scanf("%d", &kase);
    while(kase --) {
        int n, m; scanf("%d %d", &n, &m);
        init(n);
        int a, b, v;
        for(int i = 0; i < m; i ++) {
            scanf("%d %d %d", &a, &b, &v);
//            edge[a].push_back(node(b, v));
//            edge[b].push_back(node(a, v));
            save[i] = node(a, b, v);
        }
        kruskal(n, m);
    }
    return 0;
}
