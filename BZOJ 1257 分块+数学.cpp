/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int maxn = 1e5 + 5;

/// sum(1 to n)(k % i) = sum(1 to n) (k - i * (k/i))
///                    = n*k - sum(1 to n)(i * (k/i))
//6 3 2 1 1 1
/// 对（k/i）可以分块
int main() {
    ll n = read(), k = read();
    ll ans = n * k;
    n = min(n, k);
    
    for(ll l = 1, r = 1; l <= n; l = r + 1) {
        r = min(k / (k / l), n);
        ans = ans - ((l + r) * (r - l + 1) >> 1)*(k / l);
    }
    printf("%lld\n", ans);
    return 0;
}
