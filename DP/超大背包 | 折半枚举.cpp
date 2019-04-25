//https://blog.csdn.net/qq_34649947/article/details/79824161

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <map>
using namespace std;
#define INF 0x3f3f3f3f
#define lowbit(x) ((x)&-(x))
typedef long long ll;
const int maxn = 40 + 10;
int n;
ll w[maxn], v[maxn];
ll W;
struct Node {
    int ww;
    int vv;
    Node(int _w = 0, int _v = 0):ww(_w), vv(_v){}
}ps[1 << (maxn/2+2)];
bool cmp(Node a, Node b) {
    if (a.vv == b.vv) return a.ww > b.ww;
    return a.vv < b.vv;
}
 
int fun(int l, int r, int key) {
    int mid = 0;
    while (l < r) {
        mid = (l+r)>>1;
        if (ps[mid].ww < key) l = mid+1;
        else r = mid;
    }
    return ps[l].vv;
}
void solve() {
    //枚举前半段
    int n2 = n/2;
    for (int i = 0; i < 1 << n2; i++) {
        ll sw = 0, sv = 0;
        for (int j = 0; j < n2; j++) {
            if (i >> j & 1) {
                sw += w[j];
                sv += v[j];
            }
        }
        ps[i] = Node(sw, sv);
    }
 
    //去除多余的元素
    sort(ps, ps + (1 << n2), cmp);
    int m = 0;
    for (int i = 1;  i < 1 << n2; i++) {
        if (ps[m].vv < ps[i].vv) {
            ps[++m] = ps[i];
        }
    }
 
    //枚举后半部分求解
    ll res = 0;
    for (int i = 0; i < 1 << (n - n2); i++) {
        ll sw = 0, sv = 0;
        for (int j = 0; j < n - n2; j++) {
            if (i >> j & 1) {
                sw += w[n2 + j];
                sv += v[n2 + j];
            }
        }
        if (sw <= W) {
            ll tv = fun(0, m, W - sw);
            res = max(res, sv + tv);
        }
    }
 
 
    cout << res << endl;
}
 
int main() {
 
	cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    cin >> W;
	solve();
 
	return 0;
}
