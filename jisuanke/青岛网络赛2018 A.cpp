/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
//        ll a, b, c, d, v, t;
//        scanf("%lld %lld", &a, &b);
//        for (int i = 1; i <= 50000000; i ++) a ++;
        //scanf("%lld %lld %lld %lld %lld %lld", &a, &b, &c, &d, &v, &t);
         int n, m;
        scanf("%d %d", &n, &m);
        int le = n - m + 1;
        int ans2;
        //if (le == 0) ans2 = m;
        //else
            ans2 = m / le;
        if (le * ans2 < m) ans2 ++;
        
        if (m > 0 && ans2 == 0) ans2 = 1;
        const int mm = 5e7;
        int test;
        for (int i = 1; i <= 50000000; i ++) test++;
        printf("%d %d\n", m, ans2);
    }
    return 0;
}
