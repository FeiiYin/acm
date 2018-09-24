// 题意：k 维空间，求点到曼哈顿距离球的最短欧几里得距离。 
/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;
const double eps = 1e-6;

double center[N], plane[N], conv[N];
double ans[N];

int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
        int n, K, R; scanf("%d %d %d", &n, &K, &R);
        for (int i = 1; i <= K; i ++) scanf("%lf", &center[i]);
        while (n --) {
            for (int i = 1; i <= K; i ++) {
                scanf("%lf", &plane[i]);
                conv[i] = abs(plane[i] - center[i]);
            }
            double l = 0.0, r = 1e8;
            while (r - l > eps) {
                double mid = (l + r) / 2.0, sum = 0.0;
                for (int i = 1; i <= K; i ++)
                    sum += max(0.0, conv[i] - mid);
                if (sum <= R) r = mid;
                else l = mid;
            }

            for (int i = 1; i <= K; i ++) {
                if (conv[i] > r) conv[i] = r;
                if (plane[i] > center[i])
                    //conv[i] = center[i] + conv[i];
                    conv[i] = plane[i] - conv[i];
                else
                    //conv[i] = center[i] - conv[i];
                    conv[i] = plane[i] + conv[i];
                printf("%.5f ", conv[i]);
            }
            puts("");
        }
    }
    return 0;
}
