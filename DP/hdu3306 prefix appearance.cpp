/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long LL;

const int N = 2e6 + 5;


/// 题目数据有问题，直接取波峰会出错，应该区next的跳转 已有前缀求和dp得到答案

int nxt[N];
void get_next (char a[], int len) {
    int i = 0, j = -1;
    nxt[i] = j;
    while (i < len) {
        if (j == -1 || a[i] == a[j])
            i++, j++, nxt[i] = j;
        else
            j = nxt[j];
    }
//    for (int i = 0; i <= len; ++i)
//        printf("%d ", nxt[i]);
//    cout << endl;
}

char a[N];
int dp[N];
const int mod = 1000000007;

int main () {
    int n;
    while (~ scanf("%d", &n)) {
        scanf("%s", a);

        nxt[n+1] = 0;
        get_next(a, n);
        LL ans = 0;
        dp[0] = 0;
        /// dp[ nxt[i] ] means another prefix appear
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[ nxt[i] ] + 1;
            ans += dp[i];
//            cout << dp[i] << " ";
        }
        printf("%lld\n", ans % mod);
    }
    return 0;
}

