#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        if(n==0)
        {
            printf("Austin\n");
            continue;
        }
        if(k>1)
            printf("Adrien\n");
        else if(k==1)
        {
            if(n&1)
                printf("Adrien\n");
            else 
                printf("Austin\n");
        }
    }
    return 0;
}
