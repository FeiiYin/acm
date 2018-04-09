/*
 * @Samaritan_infi
 */
 /// 更新的是每一个位置。
 /// 如果 前面出现过这个数，则将前面出现的位置减去1
 /// 查询的时候（l，r） 查的是root[r]  因为这样相当是维护的后缀,到r的所有区间才是正确的
 /// 然后相当于查询一颗线段树
 
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
const int max_tree = 2e6 + 5;

struct node {
    int l, r;
    int sum;
    node() {sum = 0;}
    node(int a, int b, int c) {l = a, r = b, sum = c;}
};
node tree[max_tree];
int cnt;
int root[maxn];

struct value {
    int x, id;
    value() {}
    value(int a, int b) {x = a, id = b;}
    bool operator < (const value &k) const {
        return x < k.x;
    }
} ;//Value[maxn];
int origin[maxn], after[maxn];
int hash_list[1000000 + 5], hash_pos;
int pre[maxn];

void init() {
    tree[0] = node(0, 0, 0);
    cnt = 1;
    root[0] = 0;
}

void update(int k, int pre_tree, int &now_tree, int l, int r, int val) {

    now_tree = cnt ++;
    tree[now_tree] = tree[pre_tree];
    tree[now_tree].sum += val;
    //cout << now_tree << " " << tree[now_tree].sum << " " << k << endl;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(k <= mid)    update(k, tree[pre_tree].l, tree[now_tree].l, l, mid, val);
    else        update(k, tree[pre_tree].r, tree[now_tree].r, mid + 1, r, val);
}

int query(int rt, int l, int r, int L, int R) {
    if(L <= l && r <= R) return tree[rt].sum;
    if(r < L || l > R) return 0;
    int mid = (l + r) >> 1;
    int res = 0;
    if(L <= mid ) res += query(tree[rt].l, l, mid, L, R);
    if(mid < R) res += query(tree[rt].r, mid + 1, r, L, R);
    return res;
}

int main() {
    int n; n = read();
    int x;
    for(int i = 1; i <= n; i ++) {
        x = read();
        origin[i] = x;
        after[i] = x;
    }
    
    sort(origin + 1, origin + 1 + n);
    int sz = unique(origin + 1, origin + 1 + n) - (origin + 1);
    hash_pos = 0;
    for(int i = 1; i <= sz; i ++) {
        hash_list[ origin[i] ] = i;
    }
    init();

    memset(pre, 0, sizeof pre);
    for(int i = 1; i <= n; i ++) {
        int pos = hash_list[ after[i] ];
        update(i, root[i - 1], root[i], 1, n, 1);
        if(pre[pos]) update(pre[pos], root[i], root[i], 1, n, -1);
        pre[pos] = i;
    }

    int op = read(), a, b;
    while(op --) {
        a = read(); b = read();
        printf("%d\n", query(root[b], 1, n, a, b));
    }
    return 0;
}
