/// n个坐标点，找到一个排列，使相邻点汉密尔顿距离和最大
/**
 * @Samaritan
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define pb emplace_back
#define fi first
#define se second
#define PII pair<int, int>

LL quick_pow (LL a, LL b, LL mod) {
    LL ans = 1, base = a;
    while (b) {
        if (b & 1) (ans *= base) %= mod;
        b >>= 1;
        (base *= base) %= mod;
    }
    return ans;
}

struct node {
    int pos, len;
    bool operator < (const node& k) const {
        return pos < k.pos;
    }
};

const int N = 1e5 + 5;
int X[N],Y[N];
int A[N],B[N];

int main(){
    int n, m;
    scanf("%d",&n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d %d", &X[i], &Y[i]);
        A[i] = X[i];
        B[i] = Y[i];
    }
    sort(X + 1, X + n + 1);
    sort(Y + 1, Y + n + 1);

    m = (n + 1) >> 1;
    int mid_x = X[m], mid_y = Y[m];
    int dif_x = X[m + 1] - X[m], dif_y = Y[m + 1] - Y[m];
    if (n & 1) {
        dif_x = min(dif_x, X[m] - X[m - 1]);
        dif_y = min(dif_y, Y[m] - Y[m - 1]);
    }
    LL ans = 0;
    bool F0, F1, Tag;
    for (int i = 1; i <= n; ++i) {
        ans += abs(X[i] - X[m]) + abs(Y[i] - Y[m]);
        F0 |= A[i] > mid_x && B[i] > mid_y;
        F1 |= A[i] > mid_x && B[i] <= mid_y;
        Tag |= A[i] == mid_x && B[i] == mid_y;
    }
    if (F0 && F1 && (~n & 1 || Tag))
        ans -= min(dif_x, dif_y);
    printf("%I64d\n", ans << 1);
    return 0;
}
