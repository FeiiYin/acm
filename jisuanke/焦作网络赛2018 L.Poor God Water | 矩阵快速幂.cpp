/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//01 cc mc fc
//02 cm mm fm
//03 cf mf ff

const int mod = 1e9 + 7;

const int N = 9;
struct Matrix {
    ll a[11][11];
    void init() {
        memset(a,0,sizeof(a));
    }
    void show() {
        for (int i = 1; i <= N; i ++) {
            for (int j = 1; j <= N; j ++)
                cout << a[i][j] << " "; cout << endl;
        }
    }
};
Matrix base;
#define rep(i,a,b) for(int i = (a); i <= (b); ++i)
Matrix mul(Matrix a, Matrix b) {
    Matrix ans; ans.init();
    rep(i,1,9) rep(j,1,9) rep(k,1,9) ans.a[i][j] = (ans.a[i][j]+a.a[i][k]*b.a[k][j])%mod;
    return ans;
}
Matrix powmod(Matrix a, ll n) {
    Matrix ans; ans.init();
    if(!n) return ans;
    rep(i,1,9) ans.a[i][i] = 1;
    while(n) {
        if(n&1) ans = mul(ans,a);
        n >>= 1;
        a = mul(a, a);
    }
    return ans;
}

//ll f[N], k[N];
//void cal(ll a, ll b, ll c, ll d, ll p, ll n) {
//    f[1] = a, f[2] = b;
//    k[0] = k[1] = k[2] = 0;
//    for(int i = 3; i <= n; i ++) {
//        f[i] = (f[i - 2]) * c + f[i - 1] * d + p / i;
//        cout << f[i] << " ";
//    }
//    cout << endl;
//    printf("correct : %lld\n", f[n]);
//}


int main () {
    base.init();
    base.a[4][1] = base.a[7][1] = base.a[1][2] = base.a[4][2] = base.a[1][3] = 1;
    base.a[7][3] = base.a[5][4] = base.a[8][4] = base.a[2][5] = base.a[8][5] = base.a[2][6] = 1;
    base.a[5][6] = base.a[8][6] = base.a[6][7] = base.a[9][7] = base.a[3][8] = base.a[6][8] = 1;
    base.a[9][8] = base.a[3][9] = base.a[6][9] = 1;
    //base.show();
    int kase; scanf("%d", &kase);
    while (kase --) {
        ll n; scanf("%lld", &n);
        if (n == 1) {
            printf("3\n");
            continue;
        }
        if (n == 2) {
            printf("9\n");
            continue;
        }
        n -= 2;
        Matrix a, t; a.init();
        for (int i = 1; i <= 9; i ++) a.a[i][1] = 1;

        t = powmod(base, n);
        //t.show();
        //cout << endl;
        ll ans = 0;
        a = mul(t, a);
        //a.show();
        for (int i = 1; i <= 9; i ++)
            ans += a.a[i][1];
        printf("%lld\n", ans % mod);
    }
    return 0;
}
