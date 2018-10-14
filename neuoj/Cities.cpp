/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;

int arr[N];

struct node {
    int id, val;
    node () {}
    node (int a, int b) : id(a), val(b) {}
    bool operator < (const node & k) const {
        return val > k.val;
    }
};

priority_queue<node> pq;
int par[N];

int find_par(int x) {
    if (x == par[x]) return x;
    return par[x] = find_par(par[x]);
}

bool unite (int x, int y) {
    int a = find_par(x), b = find_par(y);
    if (a == b) {
        return false;
    }
    par[a] = b;
    return true;
}

int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            par[i] = i;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);

        }
        sort (arr + 1, arr + 1 + n);
        LL ans = 0;
        for (int i = 2; i <= n; ++i) {
            ans += arr[i];
        }
        ans += arr[1] * (n - 1);
        printf("%lld\n", ans);
    }
    return 0;
}
