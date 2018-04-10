/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
const ll mod = 1e9 + 7;

int mu[maxn], prime[maxn];
bool vis[maxn];

void Mobius() {
    memset(prime, 0, sizeof prime);
    memset(mu, 0, sizeof mu);
    memset(vis, 0, sizeof vis);
    mu[1] = 1;
    int cnt = 0;
    for(int i = 2; i < maxn; i ++) {
        if(! vis[i]) {
            prime[cnt ++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < cnt && i * prime[j] < maxn; j ++) {
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}

ll quick_pow(ll a, ll x) {
    ll ans = 1;
    while(x) {
        if(x & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        x >>= 1;
    }
    return ans % mod;
}

ll fac[maxn] = {0};
ll inv[maxn] = {0};

void init() {
    inv[0] = fac[0] = inv[1] = 1;
    for(int i = 1; i < maxn; i ++)
        fac[i] = fac[i - 1] * i % mod;
    for(int i = 2; i < maxn; i ++)
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    inv[0] = 1;
    for(int i = 1; i < maxn; i ++)
        inv[i] = inv[i - 1] * inv[i] % mod;
}

ll C(ll n, ll k) {
    if(n < k)
        return 0;
    if(k > n - k)
        k = n - k;
    return fac[n] * inv[ fac[k] ] % mod * inv[ fac[n - k] ] % mod;
}

int num[maxn];


int main() {
    Mobius();
    init();
    int n, m, k, gcd;
    while(~ scanf("%d %d %d %d", &n, &m, &k, &gcd)) {
        int x;
        memset(num, 0, sizeof num);
        int min_x = 1e9, max_x = 0;
        for(int i = 0; i < n; i ++) {
            scanf("%d", &x);
            num[x] ++;
            min_x = min(x, min_x);
            max_x = max(x, max_x);
        }

        int tot = m / gcd;
        for(int i = 1; i <= tot; i ++) {
            for(int j = 2 * i * gcd; j <= m; j += i * gcd) {
                num[i * gcd] += num[j];
            }
        }
        //for(int i = 1; i <= n; i ++) cout << num[i] << " " ; cout << endl;
//        for(int i = min_x; i <= max_x; i ++)
//            num[i] += num[i - 1];
        ll ans = 0;
        for(int i = 1; i <= tot; i ++) {
            if(! mu[i]) continue;
            int now = i * gcd;
            int sum = n - num[now];
//            for(int j = min_x; j <= max_x; ) {
//                if(! (j % now)) {j ++; continue; }
//                int last = (j / now + 1) * now - 1;
//                sum += num[last] - num[j - 1];
//                j = last + 1;
//            }

            if(sum > k) continue;
            int now_val = (m / now);
            if(now_val <= 0) continue;
            if(sum == k) {
                ans = (ans + mu[i] * quick_pow(now_val, sum) ) % mod;
            } else {
                ans = (ans + mu[i] * quick_pow(now_val, sum) * quick_pow(now_val - 1, k - sum) % mod
                       * C(n - sum, k - sum) % mod + mod) % mod;
            }
        }
        printf("%lld\n", (ans + mod) % mod);
    }
    return 0;
}
