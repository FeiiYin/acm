/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

#define PII pair<int, int>
#define fi first
#define se second
#define mp make_pair

LL c[110][110];
void init() {
    memset(c,0,sizeof(c));
    c[0][0]=c[1][0]=c[1][1]=1LL;
    for(int i=2;i<=105;i++) {
        c[i][0]=c[i][i]=1;
        for(int j=1; j<i && j <= 105;j++)
            c[i][j]=  (c[i-1][j]+c[i-1][j-1]);
    }
}

int main () {
    init();
//    for (int i = 1; i <= 50; ++i)
//        printf("%lld \n", c[50][i]);
    int kase; scanf("%d", &kase); while (kase--) {
        int n; int p;
        scanf("%d %d", &n, &p);
        int k = p / 2;
        int g = k / 2;
        LL ans = 0;
        for (int i = 1; i <= g; ++i) {
            int j = k - 2*i;
            if (i < j) continue;
            ans += (c[(i+j)][i])*(c[(i+j)][i]);
            //for (int z = )
            //cout << " ans : " << ans << endl;
        }
        printf("%d %lld\n", n, ans);
    }
    return 0;
}
