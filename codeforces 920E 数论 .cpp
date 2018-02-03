#include <bits/stdc++.h>
using namespace std;


typedef long long ll ;

inline int pow(int x , int n , int mod){
    ll ans = 1 , base = x ;
    while(n){
        if(n & 1) (ans *= base) %= mod ;
        (base *= base) %= mod ;
        n >>= 1 ;
    }
    return (int) ans ;
}

int  a , b , p ;
ll x ;

int main(){
    while(~ scanf("%d %d %d %lld" , &a , &b , &p , &x)){
        ll ans = 0 ;
        for(int i = 1 ; i <= p - 1; i ++){
            int now = (ll) b * pow( (ll)pow(a , i , p) , p-2 , p ) % p ;
            ll first = (ll)(p - 1) * ((i - now + p) % p) + i ;
            if(first > x) continue ;
            ans += (x - first) / ((ll)p * (p - 1)) + 1 ;

        }
        cout << ans << endl ;
    }
    return 0 ;
}
