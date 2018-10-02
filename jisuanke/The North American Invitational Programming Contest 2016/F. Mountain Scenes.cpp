#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;

long long   dp[110][10010];

int main()
{
    long long n,w,h;
    while(~scanf("%lld%lld%lld",&n,&w,&h))
    {
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=1;i<=w;i++)
            for(int j=0;j<=n;j++)if(dp[i-1][j])
            {
//                long long temp;
//                if(j<=h)
//                    temp=0;
//                else
//                    temp=dp[i-1][j-1];
//
//                dp[i][j]=(dp[i][j]+dp[i-1][j]-temp+mod)%mod;
//                if(j!=0)
//                    dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
                for(int k=0;k<=h;k++)
                {
                    if(j+k>n)
                        break;
                    dp[i][j+k]=(dp[i][j+k]+dp[i-1][j])%mod;
                }
            }
        long long tem=n/w+1;
            long long ans=0;
        for(int i=0;i<=n;i++) ans=(ans+dp[w][i])%mod;
        printf("%lld\n",(ans-min(tem,h+1)+mod)%mod);
    }
    return 0;
}
