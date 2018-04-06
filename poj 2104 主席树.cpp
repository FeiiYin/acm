/*
 * @Samaritan_infi
 */
 /// 推荐阅读： http://www.cnblogs.com/zyf0163/p/4749042.html
 /// 主席树实际是维护了多颗线段树
 /// 解决静态区间第k小的问题
 
 /// 时间上，任意一颗线段树维护着（1，k）区间内各个数的位置，左孩子是在总共排序后前一半的数目多少
 /// 显然，如果要查询（1，k）的第i小，只要看左孩子是否比i大，如果大于等于，进入左孩子递归，否则进入右孩子递归
 /// 那么查询（l，r）的第i小，只要将（1，l-1）与（1，r）的两颗树的对应位置相减，维护前缀和，即可递归查询
 
 /// 空间上，由于线段树的每次修改，是从上往下改的，
 /// 也就是说，后一颗线段树和前一颗线段树之间的区别只有一条链的区别
 /// 所以可以利用之前线段树的存储进行优化
 
//#include<bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline bool scan(int &num)  
{
        char in; bool IsN = false;
        in = getchar();
        if(in == EOF) return false;
        while(in != '-' && (in < '0' || in > '9')) in = getchar();
        if(in == '-'){ IsN = true; num = 0;}
        else num = in - '0';
        while(in = getchar(), in >= '0' && in <= '9'){
            num *= 10, num += in - '0';
        }
        if(IsN) num = -num;
        return true;
}

const int maxn = 1e5 + 5;

struct node {
    int l, r;
    int sum;
    node() {sum = 0;}
    node(int a, int b, int c) {l = a, r = b, sum = c;}
};
node tree[maxn << 5];
int root[maxn];
int cnt;

struct value {
    int x, id;
    value() {};
    value(int a, int b) {x = a, id = b;}
    bool operator < (const value &k) const {
        return x < k.x;
    }
} Value[maxn];
int hash_list[maxn];

void init() {
    cnt = 1;
    root[0] = 0;
    tree[0] = node(0, 0, 0);
}
void update(int num, int &rt, int l, int r) {
    tree[cnt ++] = tree[rt];
    rt = cnt - 1;
    tree[rt].sum ++;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(num <= mid) update(num, tree[rt].l, l, mid);
    else update(num, tree[rt].r, mid + 1, r);
}

int query(int i, int j, int k, int l, int r) {
    if(l == r) return l;
    int d = tree[ tree[j].l ].sum - tree[ tree[i].l ].sum;
    int mid = (l + r) >> 1;
    if(k <= d) return query(tree[i].l, tree[j].l, k, l, mid);
    else return query(tree[i].r, tree[j].r, k - d, mid + 1, r);
}

int main() {
    int n, m;
    //scanf("%d %d", &n, &m);
    scan(n); scan(m);
    int x;
    for(int i = 1; i <= n; i ++) {
        //scanf("%d", &x);
        scan(x);
        Value[i] = value(x, i);
    }
    sort(Value + 1, Value + n + 1);
    for(int i = 1; i <= n; i ++) {
        hash_list[ Value[i].id ] = i;
    }
    init();
    for(int i = 1; i <= n; i++) {
        root[i] = root[i - 1];
        update(hash_list[i], root[i], 1, n);
    }
    int k, a, b;
    while(m --) {
        //scanf("%d %d %d", &a, &b, &k);
        scan(a); scan(b); scan(k);
        printf("%d\n", Value[ query(root[a - 1], root[b], k, 1, n) ].x);
    }
    return 0;
}
