#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define mod 1000000007
#define For(i,m,n) for(int i=m;i<=n;i++)
#define Dor(i,m,n) for(int i=m;i>=n;i--)
#define LL long long
#define lan(a,b) memset(a,b,sizeof(a))
using namespace std;

const LL N=100010;
LL pr[N/5],p[N+100],tot,phi[N+100];
void init()
{
    phi[1]=1;
    p[1]=1;
    For(i,2,N+1){
        if(!p[i])p[i]=i,pr[++tot]=i,phi[i]=p[i]-1;
        for(int j=1;j<=tot&&pr[j]*i<=N;j++){
            p[i*pr[j]]=pr[j];
            if(p[i]==pr[j]){
                phi[i*pr[j]]=phi[i]*pr[j];
                break;
            }else phi[i*pr[j]]=phi[i]*(pr[j]-1);
        }
    }
}

int main()
{
    init();
    for(int i=2;i<=10000;i++)
        phi[i]+=phi[i-1];
    int p;
    scanf("%d",&p);
    while(p--)
    {
        int k,n;
        scanf("%d%d",&k,&n);
        printf("%d %lld\n",k,phi[n]+1);
    }
    return 0;
}
