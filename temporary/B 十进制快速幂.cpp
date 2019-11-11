/**
 * @Samaritan
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;


const int N = 1e6 + 5;
char arr[N];
//int cost[N];
//int dp[N];
//int que[N];
void show(int arr[], int n) {
    for (int i = 0; i < n; ++i) cout << arr[i] << " "; cout << "\n";
}

const int D = 2;
struct mat {
    LL m[D][D];
    mat() {
        memset(m, 0, sizeof m);
    }
    mat(LL a[D][D]) {
        for (int i = 0; i < D; ++i)
            for (int j = 0; j < D; ++j)
                m[i][j] = a[i][j];
    }
    void show() {
        for (int i = 0; i < D; ++i) {
            for (int j = 0; j < D; ++j)
                cout << m[i][j] << " ";
            cout << endl;
        }
    }
};

mat mul (mat a, mat b, LL mod) {
    mat temp;
    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < D; ++j) { // if (a[i][j]) {
            for (int k = 0; k < D; ++k) {
                (temp.m[i][j] += a.m[i][k] * b.m[k][j] % mod) %= mod;
            }
        }
    }
    return temp;
}

mat quick_pow(mat m, LL x, LL mod) {
    mat ans;
    ans.m[0][0] = ans.m[1][1] = 1;
    while (x) {
        if (x & 1) {
            ans = mul(ans, m, mod);
        }
        x >>= 1;
        m = mul(m, m, mod);
    }
    return ans;
}

LL do_mod(char str[], LL mod) {
    LL sum=0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        sum = (sum * 10 + str[i] - '0') % mod;
    }
    return sum;
}

LL tran_val(char str[]) {
    int len = strlen(str);
    if (len > 18) return 1e18;
    LL sum = 0;
    for (int i = 0; i < len; ++i) {
        sum = (sum * 10 + str[i] - '0');
    }
    return sum;
}

mat const_mat[10];

int main() {
    LL x0, x1, a, b, mod;
    scanf("%lld %lld %lld %lld", &x0, &x1, &a, &b);
    scanf("%s %lld", arr, &mod);
    mat k;
    memset(k.m, 0, sizeof k.m);
    k.m[0][0] = a;
    k.m[0][1] = b;
    k.m[1][0] = 1;

    for (int i = 0; i < 10; ++i) {
        const_mat[i] = quick_pow(k, i, mod);
    }
    int len = strlen(arr);
    mat transfer;
    transfer.m[0][0] = 1;
    transfer.m[1][1] = 1;
    for (int i = 0; i < len; ++i) {
        transfer = quick_pow(transfer, 10LL, mod);
        transfer = mul(transfer, const_mat[ arr[i] - '0' ], mod);
    }
//    transfer.show();
    mat ans;
    ans.m[0][0] = x1;
    ans.m[1][0] = x0;
    ans = mul(transfer, ans, mod);
//    ans.show();
    printf("%lld\n", ans.m[1][0]);
    return 0;
}
