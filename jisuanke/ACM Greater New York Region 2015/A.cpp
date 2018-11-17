#include<bits/stdc++.h>

using namespace std;
int main()
{
 int n;
    scanf("%d",&n);
    for(int p=1;p<=n;p++)
    {
        long long a,b;
        scanf("%lld%lld",&a,&b);
        printf("%lld %lld %lld %lld\n",a,(b+1)*b/2,b*b,b+b*b);
        
    }
    return 0;
}
