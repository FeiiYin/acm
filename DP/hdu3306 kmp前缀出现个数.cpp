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

const int N = 2e5 + 5;
const int INF = 1e5 + 5;
const int mod = 1e9 + 7;

/// next 数组，每一个波峰表示前面匹配到这里，即表示前面的x个前缀各出现一次
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

int main () {
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        int n; scanf("%d", &n);
        scanf("%s", a);
        get_next(a, n);
        LL ans = n;
        for (int i = 1; i <= n+1; ++i) {
            if (nxt[i] + 1 != nxt[i+1]) {
                //printf("%d\n", i);
                ans += nxt[i];
            }
        }
        printf("%lld\n", ans%10007);
    }
    return 0;
}
