/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;

const int maxn = 1e6 + 5 ;
ll s[maxn] ;
ll c[maxn] ;
int main() {
    int n ;
    while( ~ scanf("%d" , &n)) {
        ll sum = 0 ;
        for(int i = 0 ; i < n ; i ++) {
            scanf("%lld" , &s[i]) ;
            sum += s[i] ;
        }
        ll a = sum / n ;
        /// s[i] - x(i) + x(i+1) = a ;
        /// x(i+1) = a + x(i) - s[i]
        /// c 为常数
        c[0] = 0 ;
        for(int i = 1 ; i < n ; i ++) {
            c[i] = c[i - 1] - a + s[i] ;
        }
        sort(c , c + n) ;
        ///中位数
        ll x0 = c[n / 2] ;
        ll ans = 0 ;
        for(int i = 0 ; i < n ; i ++) {
            ans += fabs(x0 - c[i]) ;
        }
        printf("%lld\n" , ans) ;
    }
    return 0 ;
}
