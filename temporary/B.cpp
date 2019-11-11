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
    LL m[2][2];
    void show() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j)
                cout << m[i][j] << " ";
            cout << endl;
        }
    }
};

LL temp[D][D];
LL mod;
void mul (LL a[D][D], LL b[D][D]) {
//    const LL& a[3][3] = amat.m;
//    const LL& b[3][3] = bmat.m;
    memset(temp, 0, sizeof temp);
    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < D; ++j) { // if (a[i][j]) {
            for (int k = 0; k < D; ++k) {
                (temp[i][j] += a[i][k] * b[k][j] % mod) %= mod;
            }
        }
    }
    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < D; ++j) {
            b[i][j] = temp[i][j];
        }
    }
}


LL phi(LL x){
    LL ans = x;
    for(LL i = 2; i*i <= x; i++){
        if (x % i == 0){
            ans = ans / i * (i-1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) ans = ans / x * (x-1);
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

int main() {
//    LL n;
//    while (~ scanf("%lld", &n)) {
//        string tt = "";
//        while (n) {
//            if (n & 1) tt += "1";
//            else tt += "0";
//            n >>= 1;
//        }
//        cout << tt << endl;
//    }
    LL x0, x1, a, b;
    scanf("%lld %lld %lld %lld", &x0, &x1, &a, &b);
    scanf("%s %lld", arr, &mod);
    /*ab0
    a00
    0b0*/
    mat k;
    memset(k.m, 0, sizeof k.m);
    k.m[0][0] = a;
    k.m[0][1] = b;
    k.m[1][0] = 1;
//    k.m[2][1] = 1;

    mat ans;
    memset(ans.m, 0, sizeof ans.m);
    ans.m[0][0] = x1;
    ans.m[1][0] = x0; // = ans.m[1][1] = ans.m[2][2] = 1;
//    k.show();
//    int len = strlen(arr);
    LL bit = 0;
    LL fai_mod = phi(mod);
//    LL fai_mod = mod;
    LL effi = do_mod(arr, fai_mod) + fai_mod;
    LL val = tran_val(arr);
    if (val < fai_mod)
        effi = val;
    while (effi) {
        if (effi & 1) {
            mul(k.m, ans.m);
        }
        mul(k.m, k.m);
        effi >>= 1;
//        ans.show();
    }
//    ans.show();
    printf("%lld\n", ans.m[1][0]);
//    bool borrow = false;

//    string temp = "";
//
//    for (int i = len - 1; i >= 1; --i) {
//        int now = arr[i] - '0';
//        if (borrow) {
//            if (now > 0) now--;
//            else {
//                now = 9;
//                borrow = true;
//            }
//        }
//        if (now >= 0 && now <= 5) {
//            now += 10;
//            borrow = true;
//        }
//        while (now) {
//            if (now & 1) {
//                mul(ans.m, k.m);
//                temp += "1";
//            } else {
//                temp += "0";
//            }
//            now >>= 1;
//            mul(k.m, k.m);
//        }
//    }
//    if (borrow) {
//        arr[0]--;
//    }
//    int now = arr[0] - '0';
//    if (now) {
//        while (now) {
//            if (now & 1) {
//                mul(ans.m, k.m);
//                temp += "1";
//            } else {
//                temp += "0";
//            }
//            now >>= 1;
//            mul(k.m, k.m);
//        }
//    }
//    cout << temp << endl;
//    ans.show();
    return 0;
}
