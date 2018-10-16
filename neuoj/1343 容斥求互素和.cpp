/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;


const int mod = 1e9 + 7 ;
int prime[20] , prime_pos ;

void ex_gcd(ll a , ll b , ll &d, ll &x, ll &y) {
    if(! b) {d = a; x = 1; y = 0; }
    else {
        ex_gcd(b , a % b, d, y, x);
        y -= x * (a / b);
    }
}
ll inverse(ll a , ll n) {
    ll d, x, y;
    ex_gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1 ;
}
ll inverse_2 , inverse_6 ;

void decompose(ll n) {
    prime_pos = 0 ;
    for(ll i = 2 ; i * i <= n ; i ++) {
        if(!(n % i)) {
            prime[prime_pos ++] = i ;
            while(!(n % i)) n /= i ;
        }
    }
    if(n > 1) prime[prime_pos ++] = n ;
}

///n * (n + 1) * (2 * n + 1) / 6
int work(ll n) {
    ll sum1 = 0 , sum2 = 0 ;
    for(int i = 1 ; i < (1 << prime_pos) ; i ++) {
        int bits = 0 ; ll now = 1 ;
        for(int j = 0 ; j < prime_pos ; j ++) {
            if(i & (1 << j)) {
                bits ++ ;
                now *= prime[j] ;
            }
        }
        ll num = n / now ;
        ll temp1 = now * (1 + num) % mod * num % mod * inverse_2 % mod ;
        ll temp2 = now * now % mod * num % mod * (num + 1) % mod * (2 * num + 1) % mod * inverse_6 % mod ;


        if(bits & 1) sum1 = (sum1 + temp1) % mod , sum2 = (sum2 + temp2) % mod ;
        else         sum1 = (sum1 - temp1) % mod , sum2 = (sum2 - temp2) % mod ;
    }
    ll ans1 = (1 + n) * n % mod * inverse_2 % mod ;
    ll ans2 = (1 + n) * n % mod * (2 * n + 1) % mod * inverse_6 % mod ;

    ///return (ans1 - sum1 + ans2 - sum2 + mod) % mod ; 会wa
    return ((ans1 - sum1 + ans2 - sum2) % mod + mod) % mod ;
}

int main() {
    inverse_2 = inverse(2 , mod) ;
    inverse_6 = inverse(6 , mod) ;
    //cout << inverse_2 << " " << inverse_6 << endl ;
    int n , m ;
    while(~ scanf("%d %d" , &n , &m)) {
        decompose(m) ;
        printf("%d\n" , work(n)) ;
    }
    return 0 ;
}
