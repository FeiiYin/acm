/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e7 + 5;
ll ans[N];
int prime[N], pri;
bool vis[N];
ll low[N];
void work() {
    int n = 2e7, a;
    pri = 0;
    vis[1] = true; low[1] = 1;
    ans[1] = 1; ans[0] = 0;
    for (int i = 2; i <= n; i ++) {
        if (! vis[i]) prime[pri ++] = i, low[i] = i, ans[i] = 2;
        for (int j = 0; j < pri && prime[j] * i <= n; j ++) {
            a = prime[j] * i;
            vis[a] = true;
            if (i % prime[j]) {
                low[a] = prime[j];
                ans[a] = ans[i] * ans[ prime[j] ];
            } else {
                low[a] = low[i] * prime[j];
                if (low[a] == a) {
                    if (a == prime[j] * prime[j]) ans[a] = 1;
                    else ans[a] = 0;
                }
                else
                    ans[a] = ans[i / low[i]] * ans[ low[a] ];
                break;
            }
        }
    }

    for (int i = 1; i <= n; i ++)
        ans[i] += ans[i - 1];
}

int main() {
    work();
    int kase; scanf("%d", &kase);
    while (kase --) {
        int n; scanf("%d", &n);
        printf("%lld\n", ans[n]);
    }
    return 0;
}
