/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b){
    return b ? gcd(b, a%b) : a;
}

int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
        ll a, b, c, d, v, t;
        scanf("%lld %lld %lld %lld %lld %lld", &a, &b, &c, &d, &v, &t);
        ll ans = 0;

        ll lcm = a * c / gcd(a, c);

        ll yu = t - t / lcm * lcm;
        ll yu_ans = 0;


        if (b > 1) ans += (lcm / a) * (b - 1);

        if (d > 1) ans += (lcm / c) * (d - 1);

        if (yu) yu_ans += (yu / a) * (b - 1) + (yu / c) * (d - 1);
        //ans ++; /// 0


        ll a_num = lcm / a;
        ll now, temp;
        for (ll i = 1; i <= a_num; i ++) {
            now = i * a;
            temp = now - now / c * c;
            //cout << now << " " << temp << endl;
            if (! temp) temp = min(c, a);
            temp = min(temp, a);
            if (temp <= v) {
                ans ++;
                if (now <= yu) yu_ans ++;
            }
        }
//cout << ans << endl;
        ll b_num = lcm / c;
        for (ll i = 1; i <= b_num; i ++) {
            now = i * c;
            temp = now - now / a * a;
            //cout << now << " " << temp << endl;
            //if (!temp) ;
            temp = min(temp, c);
            if (temp <= v) {
                ans ++;//, cout << now << " " << temp << endl;
                if (now <= yu) yu_ans ++;
            }
        }
        //cout << yu_ans << endl;
        //cout << ans << endl;
        ll ed = (t / lcm) * ans + yu_ans + b + d - 1;

        printf("%lld\n", ed);
    }
    return 0;
}
/*
2
1000000 1000000 1000000 1000000 1000000000000 1000000000000
1000000 1000000 100007 1000000 1000000000000 1000000000000
*/
