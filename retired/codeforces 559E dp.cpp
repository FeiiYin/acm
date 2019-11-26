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

const int N = 1e2 + 5;
const int mod = 1e9 + 7;

node arr[N];
/// first: 选取了前i个连续的灯
/// second: 第j个灯覆盖了最远
/// third: j灯的方向
int dp[N][N][2];

int main() {
    int n;
    scanf("%d", &n);
    arr[0].pos = -1e9;
    n++;
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &arr[i].pos, &arr[i].len);
    }
    sort(arr, arr + n);
    memset(dp, 0, sizeof dp);
    /// insert 1 to update 1
    int ans = 0;
    for (int mid_cur = 0; mid_cur < n; ++mid_cur) {
        for (int left_cur = 0; left_cur <= mid_cur; ++left_cur) for (int left_dir = 0; left_dir < 2; ++left_dir) {
            ans = max(ans, dp[mid_cur][left_cur][left_dir]);
            int left_can_reach = arr[left_cur].pos + left_dir * arr[left_cur].len;
            /// since we have sort via position,
            /// so the right interval is continuous
            int right_max_reach = -1e9;
            int right_max_id = -1;
            int right_max_dir = -1;
            for (int right_cur = mid_cur + 1; right_cur < n; ++right_cur) for (int right_dir = 0; right_dir < 2; ++right_dir) {
                int right_can_reach = arr[right_cur].pos + right_dir * arr[right_cur].len;
                if (right_can_reach > right_max_reach) {
                    right_max_reach = right_can_reach;
                    right_max_id = right_cur;
                    right_max_dir = right_dir;
                }
                dp[right_cur][right_max_id][right_max_dir] = max(dp[right_cur][right_max_id][right_max_dir],
                    dp[mid_cur][left_cur][left_dir] + min(arr[right_cur].len, right_can_reach - left_can_reach) + right_max_reach - right_can_reach);
            }
        }
    }
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << " (" << dp[i][j][0] << ", ";
//            cout << dp[i][j][1] << ") ";
//        }
//    }
    printf("%d\n", ans);
    return 0;
}
