/**
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL ;
const int N = 2e5 + 5;

//int arr[N], ans[N], sta[N];
//void cal_lis() {
//    int l = 0, r = 1;
//    sta[l] = -1;
//    for (int i = 1; i < n; ++i) {
//        arr[i] = ;
//    }
//}

int arr[N], dp[N];

int cal_lis_n2 () {
    dp[1] = 1;
    int ans = 1;
    if (! n) return 0;
    for (int i = 2; i <= n; ++i) {
        dp[i] = 1;
        for (int j = 1; j < i; ++j) if (arr[i] > arr[j]) {
            dp[i] = max(dp[j] + 1, dp[i]);
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

int cal_lis_logn () {
    if (! n) return 0;
    int stk[10000], cur = 1, l, r, mid;
    for (int i = 2; i <= n; ++i) {
        if (arr[i] > stk[cur]) {
            stk[++cur] = arr[i];
        }
        else {
            l = 1, r = cur;
            int t;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (stk[mid] < arr[i]) l = mid+1, t = mid;
                else r = mid-1;
            }
            stk[t+1] = arr[i];
        }
    }
    return cur;
}

/// tree cannot do lis, ISB
//int tree[N];
//void build (int rt, int l, int r) {
//    if (l == r) {
//        tree[rt] = arr[l];
//        return;
//    }
//    int mid = (l + r) >> 1;
//    build(rt << 1, l, mid);
//    build(rt << 1|1, mid+1, r);
//    tree[rt] = max(tree[rt<<1], tree[rt<<1|1]);
//}
//void update (int rt, int l, int r, int x) {
//    if (l == r) return l;
//    if (tree[rt<<1] > x)
//}
//



//int cal_lis_tree () {
//    if (! n) return 0;
//    int tree[N];
//    int stk[10000], cur = 1, l, r, mid;
//    for (int i = 2; i <= n; ++i) {
//        if (arr[i] > stk[cur]) {
//            stk[++cur] = arr[i];
//        }
//        else {
//            l = 1, r = cur;
//            int t;
//            while (l <= r) {
//                mid = (l + r) >> 1;
//                if (stk[mid] < arr[i]) l = mid+1, t = mid;
//                else r = mid-1;
//            }
//            stk[t+1] = arr[i];
//        }
//    }
//    return cur;
//}

int main () {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    /// O(n2)
    printf("%d\n", cal_lis_n2());
    return 0;
}
