/*
 * @Samaritan_infi
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e3 + 5;
const int mod = 1e9 + 7;

LL x[5], y[5], len[5], aa[5], bb[5], bet[5], cc[5], dd[5], bet2[5];

LL interval (LL a, LL b, LL c, LL d, LL &x, LL &y) {
    if (b < c || a > d) {
        x = 1, y = 0;
        return 0;
    }
    if (a <= c) {
        int xx = min(b, d);
        if (xx >= c) {
            x = c, y = xx;
            return xx - c + 1;
        } else {
            x = 1, y = 0;
            return 0;
        }
    }
    int xx = min(b, d);
    if (xx >= a) {
        x = a, y = xx;
        return xx - a + 1;
    } else {
        x = 1, y = 0;
        return 0;
    }
}

int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
        LL x1, y1, x2, y2, x3, y3, x4, y4;
        LL ans = 1;
        for (int i = 0; i < 4; ++i) {
            scanf("%lld %lld", &x[i], &y[i]);
            len[i] = y[i] - x[i] + 1;
        }
        //LL len1 = y1 - x1 + 1, len2 = y2 - x2 + 1, len3 = y3 - x3 + 1, len4 = y4 - x4 + 1;
        for (int i = 0; i < 4; ++i) ans = ans * len[i] % mod;
        //LL ans = (len[1]) * (len[2]) % mod * (len[3]) % mod * (len[4]) % mod;

        //LL a1, b1, a2, b2, a3, b3, a4, b4;
        for (int i = 0; i < 4; ++i) {
            bet[i] = interval(x[i], y[i], x[(i+1)%4], y[(i+1)%4], aa[i], bb[i]);
        }

//cout << ans << endl;
        for (int i = 0; i < 4; ++i) {
            //cout << bet[i] << " sd";
            ans = ans + mod - bet[i] * len[(i + 2) % 4] % mod * len[(i + 3) % 4] % mod;
            ans %= mod;
        }//cout << endl;

//cout << ans << endl;
        for (int i = 0; i < 4; ++i) {
            bet2[i] = interval(aa[i], bb[i], aa[(i+1)%4], bb[(i+1)%4], cc[i], dd[i]);
            //cout << bet2[i] << " sd ";
        }//cout << endl;
        for (int i = 0; i < 4; ++i) {
            (ans += bet2[i] * len[(i + 3) % 4] % mod) %= mod;
        }

        (ans += bet[0] * bet[2] % mod) %= mod;
        (ans += bet[1] * bet[3] % mod) %= mod;
        //(ans += bet[0] * bet[1] % mod + bet[2] * bet[3] % mod) %= mod;
//cout <<ans <<"sd sd" << endl;
        //LL x2 = interval(aa[0], bb[0], aa[1], bb[1], x1, y1);
//cout << ans << endl;
        (ans = ans + mod - 3 * interval(cc[0], dd[0], cc[1], dd[1], x1, y1) % mod) %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}

/*
4
1 3
1 3
1 3
1 3

1 4
1 4
1 4
1 4

1 3
2 4
3 5
1 5

2 10
3 5
3 10
3 10
*/
