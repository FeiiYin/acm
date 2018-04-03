/*
 * @Samaritan_infi
 */
/// 220ms 只进行分块查询
#include<bits/stdc++.h>
#include <cstdio>
#include <cmath>
#define test cout<<" test "<<endl;
using namespace std;
typedef long long ll;

const int maxn = 3e4 + 5;
const int max_q = 200000 + 5;
const int max_num = 1e6 + 5;

int block;
int read[maxn];
int num[max_num] = {0};
struct node {
    int l, r, block_pos, id;
    node() {}
    node(int a, int b, int i) {l = a, r = b, block_pos = l / block, id = i; }
    bool operator < (const node & k) const {
        if(block_pos == k.block_pos)
            return r < k.r;
        return block_pos < k.block_pos;
    }
};
node query[max_q];

int mo_ans;
void add(int n) {
    num[n] ++;
    if(num[n] == 1) mo_ans ++;
}
void del(int n) {
    num[n] --;
    if(! num[n]) mo_ans --;
}

int ans[max_q];
void Mo(int op) {
    sort(query, query + op);
    int cur_left = 1;
    int cur_right = 0;

    for(int i = 0; i < op; i ++) {
        int l = query[i].l, r = query[i].r;
        while(cur_right < r) add(read[++ cur_right]);
        while(cur_left  > l) add(read[--  cur_left]);
        while(cur_right > r) del(read[cur_right --]);
        while(cur_left  < l) del(read[cur_left  ++]);
        ans[ query[i].id ] = mo_ans;
    }
    for(int i = 0; i < op; i ++) printf("%d\n", ans[i]);
}

int main() {
    int n; scanf("%d", &n);
    block = sqrt(n);
    for(int i = 1; i <= n; i ++) scanf("%d", &read[i]);
    int op; scanf("%d", &op);
    int a, b;
    for(int i = 0; i < op; i ++) {
        scanf("%d %d", &a, &b);
        query[i] = node(a, b, i);
    }
    Mo(op);
    return 0;
}
