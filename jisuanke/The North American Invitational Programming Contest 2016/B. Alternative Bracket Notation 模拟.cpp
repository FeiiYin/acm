/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e4 + 5;
char arr[N];
int dp[N][2];
int ans[N][2];
#define PII pair<int, int>
#define fi first
#define se second
stack<PII> st;

int cal (int x) {
    int ans = 0;
    while (x) {
        ans ++;
        x /= 10;
    }
    return ans - 1;
}

map<int, int> pq, pp;
int pre[N];

int main () {
    scanf("%s", arr);
    int len = strlen(arr);
    int pos = 0;
    PII temp;
    for (int i = 0; i < len; ++i) {
        if (arr[i] == '(') {
            pos ++;
            st.push(PII(i, pos));
            dp[pos][0] = i;
        } else {
            temp = st.top(); st.pop();
            dp[temp.se][1] = i;
            int t = temp.se;
            pq[i] = pos;
            ans[t][0] = 4 * t;
            if (i == temp.fi + 1)
                ans[t][1] = 4 * t, pp[t] = t;
            else
                ans[t][1] = 4 * pq[i - 1], pp[t] = pos;
        }
    }
    int ex = 0;
//    for (int i = 1; i <= pos; ++i) {
//        printf("%d %d\n", dp[i][0], dp[i][1]);
////        dp[i][1] =
////        dp[i][0] = 4;
//    }
//    cout << endl;
//    for (int i = 1; i <= pos; ++i) {
//        printf("%d %d\n", ans[i][0], ans[i][1]);
//        cout << pp[i] << endl;
//    }
//    int a, pre;
//    for (int i = 1; i <= pos; ++i) {
//        pre = 0;
//        ans[i][0] += ex;
//        ans[i][1] += ex;
//        while (true) {
//            a = cal(ans[i][0]) + cal(ans[i][1]);
//            if (a - pre) {
//                ex += a - pre;
//                ans[i][0] += a - pre;
//                ans[i][1] += a - pre;
//            } else break;
//            pre = a;
//        }
//    }
    memset(pre, 0, sizeof pre);
    while (true) {
        int ex = 0;

        int a;
        for (int i = 1; i <= pos; ++i) {

            ans[i][0] += ex;
            ans[i][1] += ex;
            while (true) {
                a = cal(ans[i][0]) + cal(ans[i][1]);
                if (a - pre[i]) {
                    ex += a - pre[i];
                    ans[i][0] += a - pre[i];
                    ans[i][1] += a - pre[i];
                } else break;
                pre[i] = a;
            }
        }

        for (int i = 1; i <= pos; ++i) {
            ans[i][1] = ans[ pp[i] ][1];
        }

        if (! ex) break;
    }

    //cout << endl;
    for (int i = 1; i <= pos; ++i) {
        printf("%d,%d:", ans[i][0], ans[i][1]);
    }puts("");
    return 0;
}
/*
5,29:11,17:17,17:23,29:29,29:35,35:
5,29:11,17:17,17:23,29:29,29:35,35:
5 7
1 1 0
1 1 1
1 1 1
1 1 2
1 1 2
2 3 3
3 3 3
*/
