/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define PII pair<int, int>
#define fi first
#define se second
#define mp make_pair

const int N = 1e6 + 5;
int arr[N];
int last[N];

int pri[N],tot,zhi[N];//zhi[i]为1的表示不是质数
void sieve() {
    const int n = 1e6;
    zhi[1]=1;
    for (int i=2;i<=n;i++) {
        if (!zhi[i]) pri[++tot]=i;
        for (int j=1;j<=tot&&i*pri[j]<=n;j++) {
            zhi[i*pri[j]]=1;
            if (i%pri[j]==0) break;
        }
    }
}

int main () {
    sieve();
    int n, m, k, x, y;
    const int M = 1e6;
    while (~ scanf("%d", &n)) {
        //memset(last, 0, sizeof last);
        for (int i = 1; i <= M; ++i) last[i] = 1;
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
            x = arr[i];
            if (! zhi[x]) {
                ans += 1LL * (i - last[x] + 1) * (n - i + 1);
                last[x] = i + 1;
                continue;
            }
            for (int j = 2; j * j <= x; ++j) {
                if (x % j) continue;
                if (! zhi[j]) {
                    ans += 1LL * (i - last[j] + 1) * (n - i + 1);
                    //cout << "?? : " << (i - last[j] + 1) << " " << (n - i + 1) << endl;
                    last[j] = i + 1;
                    while (!(x % j)) x /= j;
                }
//                y = x/j;
//                if (y != j && !zhi[y]) {
//                    ans += 1LL * (i - last[y] + 1) * (n - i + 1);
//                    last[y] = i + 1;
//                }
//                cout << ans << endl;
            }
            if (x > 1) {
                ans += 1LL * (i - last[x] + 1) * (n - i + 1);
                last[x] = i + 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
