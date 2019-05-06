/// 考虑到学生都是可以同时移动的
/// F的值要么为M，可以考虑前面全为M的情况
/// 如果前面为F，那么为dp[i-1]+1
/// 全部的最大值即为答案

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


const int N = 1e6 + 5;
char arr[N];

int main () {
    scanf("%s", arr);
    int len = strlen(arr);
    LL ans = 0, tmp = 0;
    for (int i = 0; i < len; ++i) {
        if (arr[i] == 'M')
            tmp++;
        else
            ans = max(ans + 1, tmp);
    }
    printf("%lld\n", ans);
    return 0;
}
