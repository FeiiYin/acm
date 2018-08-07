/// 将原数质因数分解 为 p1^a1 * p2^a2 * ... * pn^an
/// 因数个数为 (a1 + 1) * (a2 + 1) * ... * (an + 1)
/// 因数的因数和为  连乘 sum(1 到 ai + 1)
/// 因数的因数的立方和  连乘  sum(1 到 ai + 1)的立方和 即 连乘 sum( (1+ai)(1+ai+1)/2 )^2
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;
const int maxn=65536;
int prime[maxn+10];
ll ans =0;
int t,n;
vector<int>pricount;
int len=0;
void init()
{
    for(int i=2;i<=maxn;i++)
    {
        if(!prime[i])
            prime[++prime[0]]=i;
            for(int j=1;j<=prime[0] && prime[j]<=maxn/i;j++)
            {
                prime[prime[j]*i]=1;
                if(i%prime[j]==0)break;
            }
    }
}
void get_divisor(int n)
{
    for(int i=1;i<=prime[0] && prime[i] *prime[i]<=n;i++)
    {
        int cnt=0;
        while(n % prime[i]==0)
        {
            cnt++;
            n/=prime[i];
        }
        if(cnt) pricount.push_back(cnt);
    }
    if(n>1) pricount.push_back(1);
}
int main()
{
    init();
    cin>>t;
    while(t--)
    {
        pricount.clear();
        ans=1;
        cin>>n;
        get_divisor(n);
        len=pricount.size();
        //for(vector<int>::iterator it= pricount.begin();it!=pricount.end();it++)
        //cout<<*it<<endl;
        ll tmp;
        for(int i=0;i<len;i++)
        {
            tmp=(pricount[i]+1) *(pricount[i]+2)/2;
            ans*=tmp*tmp;
        }
        cout<<ans<<endl;

    }
    return 0;
}
