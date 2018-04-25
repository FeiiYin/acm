/*
 * @Samaritan_infi
 */

/// 类欧函数
//#include<bits/stdc++.h>
#include <cstdio>
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

///f(a,b,c,n) = sum(0 to n-1)((a*i+b)/c) 取整
///推导，形是大于c的可以提取计算，小于c的建立坐标轴，然后翻转，转成新的，计算
///f(a,b,c,n) = n*m - f(c,c-b-1,a%c,m-1)
ll f(ll a, ll b, ll c, ll n) {
    if(! c) return 0;
    ll ans = (a/c)*(n-1)*n/2+(b/c)*(n);
    b %= c;
    a %= c;
    return ans + f(c, (a*n+b)%c, a, (a*n+b)/c) ;
}

int main() {
    ll x, y, z;
    while(~ scanf("%lld %lld %lld", &x, &y, &z)) {
        ll ans = 0;
        ll n = (y - x)/z;
        for(int i = 0; i < 32; i ++)
            ans |= (f(z, x, 1LL << i, n + 1) & 1) << i;
        printf("%lld\n", ans);
    }
    return 0;
}
