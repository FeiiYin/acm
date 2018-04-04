/*
 * @Samaritan_infi
 */
 /// 160ms 
 /// map里保存的是每一个数字最后出现的位置，
 /// bit里存的是从第1个位置到n的不同的数字的个数
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 30000 + 5;
const int max_q = 200000 + 5;
struct node {
    int l, r, id;
    node() {}
    node(int a, int b, int c) {l = a, r = b, id = c;}
    bool operator < (const node &k) const {
        return r < k.r;
    }
};
node query[max_q];

int tree[maxn] = {0};
int low_bit(int x) { return x & (- x); }
int sum(int x) {
    int ans = 0;
    for( ; x > 0; x -= low_bit(x)) ans += tree[x];
    return ans;
}
int n;
void update(int x, int val) {
    for( ; x <= n; x += low_bit(x)) tree[x] += val;
}

int read[maxn];
int ans[max_q];
map<int, int> pic;
int main() {
    pic.clear();
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%d", &read[i]);
    int op; scanf("%d", &op);
    int l, r;
    for(int i = 0; i < op; i ++) {
        scanf("%d %d", &l, &r);
        query[i] = node(l, r, i);
    }
    sort(query, query + op);
    int cur = 1;
    for(int i = 0; i < op; i ++) {
        l = query[i].l;
        r = query[i].r;
        for( ; cur <= r; cur ++) {
            if(pic.count(read[cur])) {
                update(pic[ read[cur] ], -1);
            }
            pic[ read[cur] ] = cur;
            update(cur, 1);
        }
        ans[ query[i].id ] = sum(r) - sum(l - 1);
    }
    for(int i = 0; i < op; i ++) printf("%d\n", ans[i]);
    return 0;
}

