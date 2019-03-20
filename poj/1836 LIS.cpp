/**
`* @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define fi  first
#define se second

const int N = 5e5 + 5;
double arr[N];

int stk[N];
int lis (int ar[], int n) {
    int l = 0, r = 1; /// stk[r] = null
    stk[l] = ar[1];
    for (int i = 2; i <= n; ++i) {
        int pos = upper_bound(stk, stk + r, ar[i]) - stk;
        stk[pos] = ar[i];
        if (pos == r) r++;
    }
    return r;
}

int dp[N];
void lis_dp (double ar[], int n) {
    dp[1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (ar[i] > ar[j]) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
    }
}

int dp_re[N];
int main(){
    int len;
    int kase = 1;
    while (~ scanf("%d", &len)) {
        for (int i = 1; i <= len; ++i) scanf("%lf", &arr[i]);
        dp[1] = 1;
        for (int i = 2; i <= len; ++i) {
            dp[i] = 1;
            for (int j = 1; j < i; ++j) {
                if (arr[i] > arr[j]) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }

        dp_re[len] = 1;
        for (int i = len-1; i >= 1; --i) {
            for (int j = len; j > i; --j) {
                if (arr[i] > arr[j])
                    dp_re[i] = max(dp_re[i], dp_re[j]+1);
            }
        }

        int ans = 0;
//        for (int i = 1; i <= len; ++i) cout << dp[i] << " "; cout << endl;
//        for (int i = 1; i <= len; ++i) cout << dp_re[i] << " "; cout << endl;
        for (int i = 1; i < len; ++i) {
            ans = max(ans, dp[i] + dp_re[i+1]);
        }
        printf("%d\n", len - ans);
    }
    return 0;
}
