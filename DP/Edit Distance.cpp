/**
 * @Samaritan
 */

/// 求两个字符串 允许插入删除替换一个字符为一个距离，求两个字符串的最短操作距离
/// 每一个操作可以由之前的两个子串变化
/// dp[0][...] 部分是代表一个字符串一直被删的表示，类推，可压缩空间
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int INF = 0x3f3f3f3f;
const int N = 1e3 + 5;
int dp[N][N];

void work (string arr, string brr) {
    memset(dp, INF, sizeof dp);
    int al = arr.size(), bl = brr.size();
    /* 如果word2为空，那么转换方式就是将word1每个字符删掉，次数就是word1的个数 */
    for (int i = 0; i <= al; ++i) dp[i][0] = i;
    for (int j = 0; j <= bl; ++j) dp[0][j] = j;

    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < brr.size(); ++j) {
            if (arr[i] == brr[j])
                dp[i+1][j+1] = dp[i][j];
            else {
                dp[i+1][j+1] = min(dp[i+1][j] + 1, dp[i][j+1] + 1);
                dp[i+1][j+1] = min(dp[i][j] + 1, dp[i+1][j+1]);
            }
        }
    }
//    for (int i = 0; i <= arr.size(); ++i) {
//        for (int j = 0; j <= brr.size(); ++j)
//            cout << dp[i][j] << " ";
//        cout <<endl;
//    }
    printf("%d\n", dp[arr.size()][brr.size()]);
}


int dp[N];
void work (string arr, string brr) {
    int al = arr.size(), bl = brr.size();
    /* 如果word2为空，那么转换方式就是将word1每个字符删掉，次数就是word1的个数 */
    for (int i = 0; i <= bl; ++i) dp[i] = i;

    for (int i = 0; i < arr.size(); ++i) {
        int pre = dp[0];
        dp[0] = i+1;
        for (int j = 0; j < brr.size(); ++j) {
            int temp = dp[j+1];
            if (arr[i] == brr[j])
                dp[j+1] = pre;
            else {
                dp[j+1] = min(dp[j+1] + 1, dp[j] + 1);
                dp[j+1] = min(pre + 1, dp[j+1]);
            }
            pre = temp;
        }
    }
    printf("%d\n", dp[brr.size()]);
}


int main(){
    string arr, brr;
    while (cin >> arr >> brr)
        work(arr, brr);
    return 0;
}
