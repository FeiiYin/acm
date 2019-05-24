\sum \sum i * j * (i,j) == 1

/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e7 + 5;
const long long mod = 998244353LL;

int mu[N];
int prime[N], pcnt;
bool vis[N];
void Mobius () {
    mu[1] = 1;
    pcnt = 0;
    for (int i = 2; i < N; i++) {
        if (vis[i] == 0) {
            mu[i] = -1;
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] != 0)
                mu[i * prime[j]] = -mu[i];
            else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
    //for (int i = 2; i < N; i++) mu[i] += mu[i - 1];
}

ll sum[N];
void seive () {
    int n = 1e7, k;
//    for (int i = 1; i * i <= n; i ++) {
//        k = i * i;
//        for (int j = k; j <= n; j += k)
//            sum[j] += mu[j / k];
//    }
//    for (int i = 2; i <= n; i ++)
//        sum[i] += sum[i - 1];
//
    sum[0] = 0;
    for (ll i = 1; i <= n; ++i) {
        sum[i] = i * i * mu[i] % mod;
        sum[i] = (sum[i] + sum[i-1] + mod) % mod;
    }

}


long long solve(long long n,long long m){
       long long ans=0;
       for(long long i=1;i<=m;++i){
              for(long long j=1;j<=n;++j)
                     if(__gcd(i,j)==1) {
                            ans=(ans+i*j%mod)%mod;
                            // cout << i << " " << j << endl;
                     }
       }
       return ans*8%mod;
}


int main() {
    Mobius();
    seive();

//    for (int i = 1; i <= 6; ++i)
//        cout << sum[i] << " "; cout << endl;
    int kase; scanf("%d", &kase);
    while (kase--) {
        ll n, m; scanf("%lld %lld", &n, &m);
        if (n > m) swap(n, m);

        ll ans = 0, temp;
        ll x, y;
        for (ll l = 1, r, k; l <= n; l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            // r = min(r, n);

            //cout << l << " " << r << endl;
            x = n/l; y = m/l;
            // temp = n/l * (n/l+1) % mod * m/l
            temp = x * (x+1) % mod * y % mod * (y + 1) % mod;
            ans += (sum[r] - sum[l-1] + mod) % mod * temp % mod;
            ans %= mod;
//            cout << "l: " << l  << " r:" << r << endl;
//            cout << temp << " " << sum[r] - sum[l-1] << endl;
            // ans += 1LL * (n / l) * (m / l) * (sum[r] - sum[l - 1]);
//            cout << "-" << mod - ans << " +" << ans << endl;
        }
//         cout << solve(n, m) << endl;
        printf("%lld\n", (ans * 2 % mod + mod) % mod);
    }
    return 0;
}
