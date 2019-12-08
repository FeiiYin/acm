///
/**
 * @Sapicritan
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define pb emplace_back
#define fi first
#define se second
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define PLI pair<LL, int>

LL quick_pow (LL a, LL b, LL mod) {
    LL ans = 1, base = a;
    while (b) {
        if (b & 1) (ans *= base) %= mod;
        b >>= 1;
        (base *= base) %= mod;
    }
    return ans;
}
void gcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        d = a; x = 1; y = 0;
    } else {
        gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}
LL get_inv(LL a, LL n) {
    LL d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}
inline int log2(const float &x) {
    return ((unsigned &) x >> 23 & 255) - 127;
}
template <typename type>
void show(type arr[], int len) {
    for (int i = 0; i <= len; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
const int mod = 998244353;
const int N = 5e2 + 5;
const int M = 1e6 + 5;
const int logN = 20;
const int INF = 1e7;

int S[N][N];
int pic[N][N];

int main(){
    int n, m;
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &pic[i][j]);
            if (!pic[i][j])
                pic[i][j] = INF;
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = i + 1; j <= m; ++j) {
            int a = 0, b = 0;
            for (int k = 1; k <= n; ++k) {
                if (pic[k][i] < pic[k][j]) a++;
                else if (pic[k][i] > pic[k][j]) b++;
            }
            if (a > b) S[i][j] = a;
            else if (b > a) S[j][i] = b;
        }
    }
//    for (int i = 1; i <= m; ++i) {
//        for (int j = 1; j <= m; ++j) {
//            cout << S[i][j] << " ";
//        } cout << endl;
//    }
    for (int k = 1; k <= m; ++k) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (!S[i][k] || !S[k][j]) continue;
                S[i][j] = max(S[i][j], min(S[i][k], S[k][j]));
            }
        }
    }

    vector<int> ans;
    for (int i = 1; i <= m; ++i) {
        bool flag = true;
        for (int j = 1; j <= m; ++j) {
            if (i == j) continue;
            if (S[i][j] < S[j][i]) {
                flag = false;
                break;
            }
        }
        if (flag) ans.pb(i);
    }
    for (int i = 0; i < ans.size() - 1; ++i) {
        printf("%d ", ans[i]);
    }
    printf("%d\n", ans[ans.size() - 1]);
    return 0;
}
