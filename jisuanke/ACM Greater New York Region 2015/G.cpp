#include<bits/stdc++.h>
using namespace std;

long long dp[40][40][40],sum[40][40],ans[40];

int main()
{
    int p;
    scanf("%d",&p);
    while(p--)
    {
        memset(dp,0,sizeof(dp));
        memset(sum,0,sizeof(sum));
        memset(ans,0,sizeof(ans));
        int K,n,m,k;
        scanf("%d%d%d%d",&K,&n,&m,&k);
        int a[40]={0};
        for(int i=m;i<=35;i+=k)
            a[i]=1;
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
                dp[0][j][k]=0;
        sum[0][0]=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=i;j++)
            {
                for(int k=1;k<=i;k++)
                {
                    if(a[k]==1)
                        continue;
                    dp[i][j][k]+=sum[i-k][j-1];
//            printf("dp[%d][%d][%d]=%lld\n",i,j,k,dp[i][j][k]);

                    sum[i][j]+=dp[i][j][k];

                }
            ans[i]+=sum[i][j];
//            printf("sum[%d][%d]=%lld\n",i,j,sum[i][j]);
            }
        }
        printf("%d %lld\n",K,ans[n]);
    }
    return 0;
}
