/*
 * @Samaritan_infi
 */
//#include<bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 2000000 + 5;

int tree[maxn];

int n;
int low_bit(int x) { return x & (-x); }
void add(int x, int val) {
    for( ; x <= n; x += low_bit(x)) tree[x] += val;
}
int query(int x) {
    int ans = 0;
    for( ; x > 0; x -= low_bit(x)) ans += tree[x];
    return ans;
}


///神奇的常数优化，不改会T ，等价于vector<int> edge[maxn]
typedef vector<int> INT;
vector< INT > edge(maxn);


int pos;
int in[maxn], out[maxn];
int val[maxn];
void dfs(int x, int pre) {
    in[x] = ++ pos;
    for(int i = 0; i < edge[x].size(); i ++) {
        int u = edge[x][i];
        if(u == pre) continue;
        dfs(u, x);
    }
    out[x] = pos;
}
void show(int a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}
void init(int n) {
    for(int i = 0; i <= n; i ++) edge[i].clear(), val[i] = 1;
    pos = 0;
    memset(tree, 0, sizeof tree);
    for(int i = 1; i <= n; i ++) add(i, 1);
}
int main() {
        scanf("%d", &n);
        init(n);
        int l, r;
        for(int i = 1; i < n; i ++) {
            scanf("%d %d", &l, &r);
            edge[l].push_back(r);
            edge[r].push_back(l);
        }
        dfs(1, 0);

        int op; scanf("%d", &op);
        char read[5];
        int x;
        while(op --) {
            scanf("%s %d", read, &x);
            if(read[0] == 'Q') {
//                cout << in[x] << " " << out[x] << endl;
//                cout << query(in[x] - 1) << " " << query(out[x]) << endl;
                printf("%d\n", query(out[x]) - query(in[x] - 1));
            } else {
                if(val[ in[x] ]) {
                    val[ in[x] ] = 0;
                    add(in[x], -1);
                } else {
                    val[ in[x] ] = 1;
                    add(in[x], 1);
                }
            }
        }

    return 0;
}
