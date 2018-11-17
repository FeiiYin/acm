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
int main () {
//    queue<PII> q;
//    q.push(mp(1, 1));
//
//    int level = 1, pre = 1;
//    while (! q.empty()) {
//        PII a = q.front(); q.pop();
//
//        printf(" %d/%d (%d) ", a.fi, a.se, a.fi+a.se);
//        level--;
//        if (! level) {
//            pre <<= 1;
//            level = pre;
//            printf("\n");
//        }
//        q.push(mp(a.fi, a.fi+a.se));
//        q.push(mp(a.fi+a.se, a.se));
//        if (a.fi > 20)break;
//    }
//    puts("");
    int kase; scanf("%d", &kase); while (kase--) {
        int n; int p, q;
        scanf("%d %d/%d", &n, &p, &q);
        //cout << n << p << q << endl;
        int level = 1, dif = 1;
        while (p > 1 || q > 1) {
            if (p > q) { /// right
                p -= q;
                dif += (1 << (level-1));
            } else { /// left
                q -= p;
            }
            level++;
        }
        int pre = (1<<(level-1))-1;
       // cout << dif << endl;
        printf("%d %d\n", n, dif + pre);
    }
    return 0;
}
