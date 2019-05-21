/**
 * @Samaritan
 */
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;
const int M = 1e4 + 5;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

/// c(i, j) = c(i-1, j-1) + c(i-1, j);
LL C[100][100];
LL fac[100];
void init () {
    int n = 40;
    C[1][1] = C[2][1] = 1;
    fac[0] = fac[1] = 1;
    for (int i = 2; i <= n; ++i)
        fac[i] = fac[i-1] * i;
    for (int i = 0; i <= n; ++i)
        C[i][0] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
}

LL f[N][N];

int main () {
    init ();
    int n, m, k;
    while (~ scanf("%d %d %d", &n, &m, &k)) {
        if (!n && !m && !k)
            break;
        if (m * k > n) {
            printf("0\n");
            continue;
        }
        // wrong password
        // LL ans = 1LL * fac[m] * C[n][m*k] * C[l + m - 1][m - 1];
        memset(f, 0, sizeof f);
        for (int i = k; i <= n; ++i) {
            f[i][1] = C[n][i];
        }


//        for (int i = 2; i <= m; ++i) {
//            for (int j = k; j <= n; ++j) {
//                for (int t = (i-1)*k; t < j; ++t)
//                    f[j][i] += f[t][i-1] * C[n - t][j - t];
//            }
//        }

        for (int j = 2; j <= m; j++)
            for (int i = k*j; i <= n; i++)
                /// new box
                for (int l = k; l <= i; l++)
                    f[i][j] += f[i - l][j - 1] * C[n - (i-l)][l];

//        for (int i = 1; i <= n; ++i) {
//            for (int j = 1; j <= m; ++j)
//                cout << f[i][j] << " ";
//            cout << endl;
//        }
        printf("%lld\n", f[n][m]);
        //cout << C[n][m] << endl;
    }
    return 0;
}
