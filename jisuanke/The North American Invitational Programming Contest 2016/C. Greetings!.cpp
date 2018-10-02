#include<bits/stdc++.h>
#define inf 1e16
#define mod 1000000007
#define For(i,m,n) for(int i=m;i<=n;i++)
#define Dor(i,m,n) for(int i=m;i>=n;i--)
#define LL long long
#define lan(a,b) memset(a,b,sizeof(a))
#define sqr(a) a*a
using namespace std;

LL dp[20][32800];
LL a[20],b[20],c[20];
int main()
{
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        for(int i=1;i<=n;i++)
            scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);

            for(int i=1;i<=k;i++)
                for(int j=0;j<1<<n;j++)
                    dp[i][j]=inf;
            dp[0][0]=0;

            for(int i=0;i<=(1<<n)-1;i++)
            {
                LL maxa=0,maxb=0;
                LL num=0,sum=0;
                int tem=i;
                int id=1;
                while(tem)
                {
                    if(tem&1)
                        maxa=max(maxa,a[id]),maxb=max(maxb,b[id]),num+=c[id],sum+=c[id]*a[id]*b[id];
                    tem>>=1;
                    id++;
                }
                dp[1][i]=num*maxa*maxb-sum;
            }
        for(int i=2;i<=k;i++)
        {
            for(int j=0;j<=(1<<n)-1;j++)
            {
                for(int x=j;x;x=(x-1)&j)
                        dp[i][j]=min(dp[i][j],dp[i-1][x]+dp[1][j-x]);//printf("dp %d %d=%lld\n",i,j,dp[i][j]);
            }
        }
        printf("%lld\n",dp[k][(1<<n)-1]);
    }
    return 0;

}
